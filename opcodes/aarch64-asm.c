/* aarch64-asm.c -- AArch64 assembler support.
   Copyright (C) 2012-2017 Free Software Foundation, Inc.
   Contributed by ARM Ltd.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3. If not,
   see <http://www.gnu.org/licenses/>.  */

#include "sysdep.h"
#include <stdarg.h>
#include "libiberty.h"
#include "aarch64-asm.h"

/* Utilities.  */

/* The unnamed arguments consist of the number of fields and information about
   these fields where the VALUE will be inserted into CODE.  MASK can be zero or
   the base mask of the opcode.

   N.B. the fields are required to be in such an order than the least signficant
   field for VALUE comes the first, e.g. the <index> in
    SQDMLAL <Va><d>, <Vb><n>, <Vm>.<Ts>[<index>]
   is encoded in H:L:M in some cases, the fields H:L:M should be passed in
   the order of M, L, H.  */

static inline void
insert_fields (aarch64_insn *code, aarch64_insn value, aarch64_insn mask, ...)
{
  uint32_t num;
  const aarch64_field *field;
  enum aarch64_field_kind kind;
  va_list va;

  va_start (va, mask);
  num = va_arg (va, uint32_t);
  assert (num <= 5);
  while (num--)
    {
      kind = va_arg (va, enum aarch64_field_kind);
      field = &fields[kind];
      insert_field (kind, code, value, mask);
      value >>= field->width;
    }
  va_end (va);
}

/* Insert a raw field value VALUE into all fields in SELF->fields.
   The least significant bit goes in the final field.  */

static void
insert_all_fields (const aarch64_operand *self, aarch64_insn *code,
		   aarch64_insn value)
{
  unsigned int i;
  enum aarch64_field_kind kind;

  for (i = ARRAY_SIZE (self->fields); i-- > 0; )
    if (self->fields[i] != FLD_NIL)
      {
	kind = self->fields[i];
	insert_field (kind, code, value, 0);
	value >>= fields[kind].width;
      }
}

/* Operand inserters.  */

/* Insert register number.  */
const char *
aarch64_ins_regno (const aarch64_operand *self, const aarch64_opnd_info *info,
		   aarch64_insn *code,
		   const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_field (self->fields[0], code, info->reg.regno, 0);
  return NULL;
}

/* Insert register number, index and/or other data for SIMD register element
   operand, e.g. the last source operand in
     SQDMLAL <Va><d>, <Vb><n>, <Vm>.<Ts>[<index>].  */
const char *
aarch64_ins_reglane (const aarch64_operand *self, const aarch64_opnd_info *info,
		     aarch64_insn *code, const aarch64_inst *inst)
{
  /* regno */
  insert_field (self->fields[0], code, info->reglane.regno, inst->opcode->mask);
  /* index and/or type */
  if (inst->opcode->iclass == asisdone || inst->opcode->iclass == asimdins)
    {
      int pos = info->qualifier - AARCH64_OPND_QLF_S_B;
      if (info->type == AARCH64_OPND_En
	  && inst->opcode->operands[0] == AARCH64_OPND_Ed)
	{
	  /* index2 for e.g. INS <Vd>.<Ts>[<index1>], <Vn>.<Ts>[<index2>].  */
	  assert (info->idx == 1);	/* Vn */
	  aarch64_insn value = info->reglane.index << pos;
	  insert_field (FLD_imm4, code, value, 0);
	}
      else
	{
	  /* index and type for e.g. DUP <V><d>, <Vn>.<T>[<index>].
	     imm5<3:0>	<V>
	     0000	RESERVED
	     xxx1	B
	     xx10	H
	     x100	S
	     1000	D  */
	  aarch64_insn value = ((info->reglane.index << 1) | 1) << pos;
	  insert_field (FLD_imm5, code, value, 0);
	}
    }
  else if (inst->opcode->iclass == dotproduct)
    {
      unsigned reglane_index = info->reglane.index;
      switch (info->qualifier)
	{
	case AARCH64_OPND_QLF_S_4B:
	  /* L:H */
	  assert (reglane_index < 4);
	  insert_fields (code, reglane_index, 0, 2, FLD_L, FLD_H);
	  break;
	default:
	  assert (0);
	}
    }
  else if (inst->opcode->iclass == cryptosm3)
    {
      /* index for e.g. SM3TT2A <Vd>.4S, <Vn>.4S, <Vm>S[<imm2>].  */
      unsigned reglane_index = info->reglane.index;
      assert (reglane_index < 4);
      insert_field (FLD_SM3_imm2, code, reglane_index, 0);
    }
  else
    {
      /* index for e.g. SQDMLAL <Va><d>, <Vb><n>, <Vm>.<Ts>[<index>]
         or SQDMLAL <Va><d>, <Vb><n>, <Vm>.<Ts>[<index>].  */
      unsigned reglane_index = info->reglane.index;

      if (inst->opcode->op == OP_FCMLA_ELEM)
	/* Complex operand takes two elements.  */
	reglane_index *= 2;

      switch (info->qualifier)
	{
	case AARCH64_OPND_QLF_S_H:
	  /* H:L:M */
	  assert (reglane_index < 8);
	  insert_fields (code, reglane_index, 0, 3, FLD_M, FLD_L, FLD_H);
	  break;
	case AARCH64_OPND_QLF_S_S:
	  /* H:L */
	  assert (reglane_index < 4);
	  insert_fields (code, reglane_index, 0, 2, FLD_L, FLD_H);
	  break;
	case AARCH64_OPND_QLF_S_D:
	  /* H */
	  assert (reglane_index < 2);
	  insert_field (FLD_H, code, reglane_index, 0);
	  break;
	default:
	  assert (0);
	}
    }
  return NULL;
}

/* Insert regno and len field of a register list operand, e.g. Vn in TBL.  */
const char *
aarch64_ins_reglist (const aarch64_operand *self, const aarch64_opnd_info *info,
		     aarch64_insn *code,
		     const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* R */
  insert_field (self->fields[0], code, info->reglist.first_regno, 0);
  /* len */
  insert_field (FLD_len, code, info->reglist.num_regs - 1, 0);
  return NULL;
}

/* Insert Rt and opcode fields for a register list operand, e.g. Vt
   in AdvSIMD load/store instructions.  */
const char *
aarch64_ins_ldst_reglist (const aarch64_operand *self ATTRIBUTE_UNUSED,
			  const aarch64_opnd_info *info, aarch64_insn *code,
			  const aarch64_inst *inst)
{
  aarch64_insn value = 0;
  /* Number of elements in each structure to be loaded/stored.  */
  unsigned num = get_opcode_dependent_value (inst->opcode);

  /* Rt */
  insert_field (FLD_Rt, code, info->reglist.first_regno, 0);
  /* opcode */
  switch (num)
    {
    case 1:
      switch (info->reglist.num_regs)
	{
	case 1: value = 0x7; break;
	case 2: value = 0xa; break;
	case 3: value = 0x6; break;
	case 4: value = 0x2; break;
	default: assert (0);
	}
      break;
    case 2:
      value = info->reglist.num_regs == 4 ? 0x3 : 0x8;
      break;
    case 3:
      value = 0x4;
      break;
    case 4:
      value = 0x0;
      break;
    default:
      assert (0);
    }
  insert_field (FLD_opcode, code, value, 0);

  return NULL;
}

/* Insert Rt and S fields for a register list operand, e.g. Vt in AdvSIMD load
   single structure to all lanes instructions.  */
const char *
aarch64_ins_ldst_reglist_r (const aarch64_operand *self ATTRIBUTE_UNUSED,
			    const aarch64_opnd_info *info, aarch64_insn *code,
			    const aarch64_inst *inst)
{
  aarch64_insn value;
  /* The opcode dependent area stores the number of elements in
     each structure to be loaded/stored.  */
  int is_ld1r = get_opcode_dependent_value (inst->opcode) == 1;

  /* Rt */
  insert_field (FLD_Rt, code, info->reglist.first_regno, 0);
  /* S */
  value = (aarch64_insn) 0;
  if (is_ld1r && info->reglist.num_regs == 2)
    /* OP_LD1R does not have alternating variant, but have "two consecutive"
       instead.  */
    value = (aarch64_insn) 1;
  insert_field (FLD_S, code, value, 0);

  return NULL;
}

/* Insert Q, opcode<2:1>, S, size and Rt fields for a register element list
   operand e.g. Vt in AdvSIMD load/store single element instructions.  */
const char *
aarch64_ins_ldst_elemlist (const aarch64_operand *self ATTRIBUTE_UNUSED,
			   const aarch64_opnd_info *info, aarch64_insn *code,
			   const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  aarch64_field field = {0, 0};
  aarch64_insn QSsize = 0;	/* fields Q:S:size.  */
  aarch64_insn opcodeh2 = 0;	/* opcode<2:1> */

  assert (info->reglist.has_index);

  /* Rt */
  insert_field (FLD_Rt, code, info->reglist.first_regno, 0);
  /* Encode the index, opcode<2:1> and size.  */
  switch (info->qualifier)
    {
    case AARCH64_OPND_QLF_S_B:
      /* Index encoded in "Q:S:size".  */
      QSsize = info->reglist.index;
      opcodeh2 = 0x0;
      break;
    case AARCH64_OPND_QLF_S_H:
      /* Index encoded in "Q:S:size<1>".  */
      QSsize = info->reglist.index << 1;
      opcodeh2 = 0x1;
      break;
    case AARCH64_OPND_QLF_S_S:
      /* Index encoded in "Q:S".  */
      QSsize = info->reglist.index << 2;
      opcodeh2 = 0x2;
      break;
    case AARCH64_OPND_QLF_S_D:
      /* Index encoded in "Q".  */
      QSsize = info->reglist.index << 3 | 0x1;
      opcodeh2 = 0x2;
      break;
    default:
      assert (0);
    }
  insert_fields (code, QSsize, 0, 3, FLD_vldst_size, FLD_S, FLD_Q);
  gen_sub_field (FLD_asisdlso_opcode, 1, 2, &field);
  insert_field_2 (&field, code, opcodeh2, 0);

  return NULL;
}

/* Insert fields immh:immb and/or Q for e.g. the shift immediate in
   SSHR <Vd>.<T>, <Vn>.<T>, #<shift>
   or SSHR <V><d>, <V><n>, #<shift>.  */
const char *
aarch64_ins_advsimd_imm_shift (const aarch64_operand *self ATTRIBUTE_UNUSED,
			       const aarch64_opnd_info *info,
			       aarch64_insn *code, const aarch64_inst *inst)
{
  unsigned val = aarch64_get_qualifier_standard_value (info->qualifier);
  aarch64_insn Q, imm;

  if (inst->opcode->iclass == asimdshf)
    {
      /* Q
	 immh	Q	<T>
	 0000	x	SEE AdvSIMD modified immediate
	 0001	0	8B
	 0001	1	16B
	 001x	0	4H
	 001x	1	8H
	 01xx	0	2S
	 01xx	1	4S
	 1xxx	0	RESERVED
	 1xxx	1	2D  */
      Q = (val & 0x1) ? 1 : 0;
      insert_field (FLD_Q, code, Q, inst->opcode->mask);
      val >>= 1;
    }

  assert (info->type == AARCH64_OPND_IMM_VLSR
	  || info->type == AARCH64_OPND_IMM_VLSL);

  if (info->type == AARCH64_OPND_IMM_VLSR)
    /* immh:immb
       immh	<shift>
       0000	SEE AdvSIMD modified immediate
       0001	(16-UInt(immh:immb))
       001x	(32-UInt(immh:immb))
       01xx	(64-UInt(immh:immb))
       1xxx	(128-UInt(immh:immb))  */
    imm = (16 << (unsigned)val) - info->imm.value;
  else
    /* immh:immb
       immh	<shift>
       0000	SEE AdvSIMD modified immediate
       0001	(UInt(immh:immb)-8)
       001x	(UInt(immh:immb)-16)
       01xx	(UInt(immh:immb)-32)
       1xxx	(UInt(immh:immb)-64)  */
    imm = info->imm.value + (8 << (unsigned)val);
  insert_fields (code, imm, 0, 2, FLD_immb, FLD_immh);

  return NULL;
}

/* Insert fields for e.g. the immediate operands in
   BFM <Wd>, <Wn>, #<immr>, #<imms>.  */
const char *
aarch64_ins_imm (const aarch64_operand *self, const aarch64_opnd_info *info,
		 aarch64_insn *code,
		 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int64_t imm;

  imm = info->imm.value;
  if (operand_need_shift_by_two (self))
    imm >>= 2;
  insert_all_fields (self, code, imm);
  return NULL;
}

/* Insert immediate and its shift amount for e.g. the last operand in
     MOVZ <Wd>, #<imm16>{, LSL #<shift>}.  */
const char *
aarch64_ins_imm_half (const aarch64_operand *self, const aarch64_opnd_info *info,
		      aarch64_insn *code, const aarch64_inst *inst)
{
  /* imm16 */
  aarch64_ins_imm (self, info, code, inst);
  /* hw */
  insert_field (FLD_hw, code, info->shifter.amount >> 4, 0);
  return NULL;
}

/* Insert cmode and "a:b:c:d:e:f:g:h" fields for e.g. the last operand in
     MOVI <Vd>.<T>, #<imm8> {, LSL #<amount>}.  */
const char *
aarch64_ins_advsimd_imm_modified (const aarch64_operand *self ATTRIBUTE_UNUSED,
				  const aarch64_opnd_info *info,
				  aarch64_insn *code,
				  const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  enum aarch64_opnd_qualifier opnd0_qualifier = inst->operands[0].qualifier;
  uint64_t imm = info->imm.value;
  enum aarch64_modifier_kind kind = info->shifter.kind;
  int amount = info->shifter.amount;
  aarch64_field field = {0, 0};

  /* a:b:c:d:e:f:g:h */
  if (!info->imm.is_fp && aarch64_get_qualifier_esize (opnd0_qualifier) == 8)
    {
      /* Either MOVI <Dd>, #<imm>
	 or     MOVI <Vd>.2D, #<imm>.
	 <imm> is a 64-bit immediate
	 "aaaaaaaabbbbbbbbccccccccddddddddeeeeeeeeffffffffgggggggghhhhhhhh",
	 encoded in "a:b:c:d:e:f:g:h".	*/
      imm = aarch64_shrink_expanded_imm8 (imm);
      assert ((int)imm >= 0);
    }
  insert_fields (code, imm, 0, 2, FLD_defgh, FLD_abc);

  if (kind == AARCH64_MOD_NONE)
    return NULL;

  /* shift amount partially in cmode */
  assert (kind == AARCH64_MOD_LSL || kind == AARCH64_MOD_MSL);
  if (kind == AARCH64_MOD_LSL)
    {
      /* AARCH64_MOD_LSL: shift zeros.  */
      int esize = aarch64_get_qualifier_esize (opnd0_qualifier);
      assert (esize == 4 || esize == 2 || esize == 1);
      /* For 8-bit move immediate, the optional LSL #0 does not require
	 encoding.  */
      if (esize == 1)
	return NULL;
      amount >>= 3;
      if (esize == 4)
	gen_sub_field (FLD_cmode, 1, 2, &field);	/* per word */
      else
	gen_sub_field (FLD_cmode, 1, 1, &field);	/* per halfword */
    }
  else
    {
      /* AARCH64_MOD_MSL: shift ones.  */
      amount >>= 4;
      gen_sub_field (FLD_cmode, 0, 1, &field);		/* per word */
    }
  insert_field_2 (&field, code, amount, 0);

  return NULL;
}

/* Insert fields for an 8-bit floating-point immediate.  */
const char *
aarch64_ins_fpimm (const aarch64_operand *self, const aarch64_opnd_info *info,
		   aarch64_insn *code,
		   const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_all_fields (self, code, info->imm.value);
  return NULL;
}

/* Insert 1-bit rotation immediate (#90 or #270).  */
const char *
aarch64_ins_imm_rotate1 (const aarch64_operand *self,
			 const aarch64_opnd_info *info,
			 aarch64_insn *code, const aarch64_inst *inst)
{
  uint64_t rot = (info->imm.value - 90) / 180;
  assert (rot < 2U);
  insert_field (self->fields[0], code, rot, inst->opcode->mask);
  return NULL;
}

/* Insert 2-bit rotation immediate (#0, #90, #180 or #270).  */
const char *
aarch64_ins_imm_rotate2 (const aarch64_operand *self,
			 const aarch64_opnd_info *info,
			 aarch64_insn *code, const aarch64_inst *inst)
{
  uint64_t rot = info->imm.value / 90;
  assert (rot < 4U);
  insert_field (self->fields[0], code, rot, inst->opcode->mask);
  return NULL;
}

/* Insert #<fbits> for the immediate operand in fp fix-point instructions,
   e.g.  SCVTF <Dd>, <Wn>, #<fbits>.  */
const char *
aarch64_ins_fbits (const aarch64_operand *self, const aarch64_opnd_info *info,
		   aarch64_insn *code,
		   const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_field (self->fields[0], code, 64 - info->imm.value, 0);
  return NULL;
}

/* Insert arithmetic immediate for e.g. the last operand in
     SUBS <Wd>, <Wn|WSP>, #<imm> {, <shift>}.  */
const char *
aarch64_ins_aimm (const aarch64_operand *self, const aarch64_opnd_info *info,
		  aarch64_insn *code, const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* shift */
  aarch64_insn value = info->shifter.amount ? 1 : 0;
  insert_field (self->fields[0], code, value, 0);
  /* imm12 (unsigned) */
  insert_field (self->fields[1], code, info->imm.value, 0);
  return NULL;
}

/* Common routine shared by aarch64_ins{,_inv}_limm.  INVERT_P says whether
   the operand should be inverted before encoding.  */
static const char *
aarch64_ins_limm_1 (const aarch64_operand *self,
		    const aarch64_opnd_info *info, aarch64_insn *code,
		    const aarch64_inst *inst, bfd_boolean invert_p)
{
  aarch64_insn value;
  uint64_t imm = info->imm.value;
  int esize = aarch64_get_qualifier_esize (inst->operands[0].qualifier);

  if (invert_p)
    imm = ~imm;
  /* The constraint check should have guaranteed this wouldn't happen.  */
  assert (aarch64_logical_immediate_p (imm, esize, &value));

  insert_fields (code, value, 0, 3, self->fields[2], self->fields[1],
		 self->fields[0]);
  return NULL;
}

/* Insert logical/bitmask immediate for e.g. the last operand in
     ORR <Wd|WSP>, <Wn>, #<imm>.  */
const char *
aarch64_ins_limm (const aarch64_operand *self, const aarch64_opnd_info *info,
		  aarch64_insn *code, const aarch64_inst *inst)
{
  return aarch64_ins_limm_1 (self, info, code, inst,
			     inst->opcode->op == OP_BIC);
}

/* Insert a logical/bitmask immediate for the BIC alias of AND (etc.).  */
const char *
aarch64_ins_inv_limm (const aarch64_operand *self,
		      const aarch64_opnd_info *info, aarch64_insn *code,
		      const aarch64_inst *inst)
{
  return aarch64_ins_limm_1 (self, info, code, inst, TRUE);
}

/* Encode Ft for e.g. STR <Qt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}]
   or LDP <Qt1>, <Qt2>, [<Xn|SP>], #<imm>.  */
const char *
aarch64_ins_ft (const aarch64_operand *self, const aarch64_opnd_info *info,
		aarch64_insn *code, const aarch64_inst *inst)
{
  aarch64_insn value = 0;

  assert (info->idx == 0);

  /* Rt */
  aarch64_ins_regno (self, info, code, inst);
  if (inst->opcode->iclass == ldstpair_indexed
      || inst->opcode->iclass == ldstnapair_offs
      || inst->opcode->iclass == ldstpair_off
      || inst->opcode->iclass == loadlit)
    {
      /* size */
      switch (info->qualifier)
	{
	case AARCH64_OPND_QLF_S_S: value = 0; break;
	case AARCH64_OPND_QLF_S_D: value = 1; break;
	case AARCH64_OPND_QLF_S_Q: value = 2; break;
	default: assert (0);
	}
      insert_field (FLD_ldst_size, code, value, 0);
    }
  else
    {
      /* opc[1]:size */
      value = aarch64_get_qualifier_standard_value (info->qualifier);
      insert_fields (code, value, 0, 2, FLD_ldst_size, FLD_opc1);
    }

  return NULL;
}

/* Encode the address operand for e.g. STXRB <Ws>, <Wt>, [<Xn|SP>{,#0}].  */
const char *
aarch64_ins_addr_simple (const aarch64_operand *self ATTRIBUTE_UNUSED,
			 const aarch64_opnd_info *info, aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* Rn */
  insert_field (FLD_Rn, code, info->addr.base_regno, 0);
  return NULL;
}

/* Encode the address operand for e.g.
     STR <Qt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
const char *
aarch64_ins_addr_regoff (const aarch64_operand *self ATTRIBUTE_UNUSED,
			 const aarch64_opnd_info *info, aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  aarch64_insn S;
  enum aarch64_modifier_kind kind = info->shifter.kind;

  /* Rn */
  insert_field (FLD_Rn, code, info->addr.base_regno, 0);
  /* Rm */
  insert_field (FLD_Rm, code, info->addr.offset.regno, 0);
  /* option */
  if (kind == AARCH64_MOD_LSL)
    kind = AARCH64_MOD_UXTX;	/* Trick to enable the table-driven.  */
  insert_field (FLD_option, code, aarch64_get_operand_modifier_value (kind), 0);
  /* S */
  if (info->qualifier != AARCH64_OPND_QLF_S_B)
    S = info->shifter.amount != 0;
  else
    /* For STR <Bt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}},
       S	<amount>
       0	[absent]
       1	#0
       Must be #0 if <extend> is explicitly LSL.  */
    S = info->shifter.operator_present && info->shifter.amount_present;
  insert_field (FLD_S, code, S, 0);

  return NULL;
}

/* Encode the address operand for e.g.
     stlur <Xt>, [<Xn|SP>{, <amount>}].  */
const char *
aarch64_ins_addr_offset (const aarch64_operand *self ATTRIBUTE_UNUSED,
			 const aarch64_opnd_info *info, aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* Rn */
  insert_field (self->fields[0], code, info->addr.base_regno, 0);

  /* simm9 */
  int imm = info->addr.offset.imm;
  insert_field (self->fields[1], code, imm, 0);

  /* writeback */
  if (info->addr.writeback)
    {
      assert (info->addr.preind == 1 && info->addr.postind == 0);
      insert_field (self->fields[2], code, 1, 0);
    }
  return NULL;
}

/* Encode the address operand for e.g. LDRSW <Xt>, [<Xn|SP>, #<simm>]!.  */
const char *
aarch64_ins_addr_simm (const aarch64_operand *self,
		       const aarch64_opnd_info *info,
		       aarch64_insn *code,
		       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int imm;

  /* Rn */
  insert_field (FLD_Rn, code, info->addr.base_regno, 0);
  /* simm (imm9 or imm7) */
  imm = info->addr.offset.imm;
  if (self->fields[0] == FLD_imm7)
    /* scaled immediate in ld/st pair instructions..  */
    imm >>= get_logsz (aarch64_get_qualifier_esize (info->qualifier));
  insert_field (self->fields[0], code, imm, 0);
  /* pre/post- index */
  if (info->addr.writeback)
    {
      assert (inst->opcode->iclass != ldst_unscaled
	      && inst->opcode->iclass != ldstnapair_offs
	      && inst->opcode->iclass != ldstpair_off
	      && inst->opcode->iclass != ldst_unpriv);
      assert (info->addr.preind != info->addr.postind);
      if (info->addr.preind)
	insert_field (self->fields[1], code, 1, 0);
    }

  return NULL;
}

/* Encode the address operand for e.g. LDRAA <Xt>, [<Xn|SP>{, #<simm>}].  */
const char *
aarch64_ins_addr_simm10 (const aarch64_operand *self,
			 const aarch64_opnd_info *info,
			 aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int imm;

  /* Rn */
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  /* simm10 */
  imm = info->addr.offset.imm >> 3;
  insert_field (self->fields[1], code, imm >> 9, 0);
  insert_field (self->fields[2], code, imm, 0);
  /* writeback */
  if (info->addr.writeback)
    {
      assert (info->addr.preind == 1 && info->addr.postind == 0);
      insert_field (self->fields[3], code, 1, 0);
    }
  return NULL;
}

/* Encode the address operand for e.g. LDRSW <Xt>, [<Xn|SP>{, #<pimm>}].  */
const char *
aarch64_ins_addr_uimm12 (const aarch64_operand *self,
			 const aarch64_opnd_info *info,
			 aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int shift = get_logsz (aarch64_get_qualifier_esize (info->qualifier));

  /* Rn */
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  /* uimm12 */
  insert_field (self->fields[1], code,info->addr.offset.imm >> shift, 0);
  return NULL;
}

/* Encode the address operand for e.g.
     LD1 {<Vt>.<T>, <Vt2>.<T>, <Vt3>.<T>}, [<Xn|SP>], <Xm|#<amount>>.  */
const char *
aarch64_ins_simd_addr_post (const aarch64_operand *self ATTRIBUTE_UNUSED,
			    const aarch64_opnd_info *info, aarch64_insn *code,
			    const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* Rn */
  insert_field (FLD_Rn, code, info->addr.base_regno, 0);
  /* Rm | #<amount>  */
  if (info->addr.offset.is_reg)
    insert_field (FLD_Rm, code, info->addr.offset.regno, 0);
  else
    insert_field (FLD_Rm, code, 0x1f, 0);
  return NULL;
}

/* Encode the condition operand for e.g. CSEL <Xd>, <Xn>, <Xm>, <cond>.  */
const char *
aarch64_ins_cond (const aarch64_operand *self ATTRIBUTE_UNUSED,
		  const aarch64_opnd_info *info, aarch64_insn *code,
		  const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* cond */
  insert_field (FLD_cond, code, info->cond->value, 0);
  return NULL;
}

/* Encode the system register operand for e.g. MRS <Xt>, <systemreg>.  */
const char *
aarch64_ins_sysreg (const aarch64_operand *self ATTRIBUTE_UNUSED,
		    const aarch64_opnd_info *info, aarch64_insn *code,
		    const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* op0:op1:CRn:CRm:op2 */
  insert_fields (code, info->sysreg, inst->opcode->mask, 5,
		 FLD_op2, FLD_CRm, FLD_CRn, FLD_op1, FLD_op0);
  return NULL;
}

/* Encode the PSTATE field operand for e.g. MSR <pstatefield>, #<imm>.  */
const char *
aarch64_ins_pstatefield (const aarch64_operand *self ATTRIBUTE_UNUSED,
			 const aarch64_opnd_info *info, aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* op1:op2 */
  insert_fields (code, info->pstatefield, inst->opcode->mask, 2,
		 FLD_op2, FLD_op1);
  return NULL;
}

/* Encode the system instruction op operand for e.g. AT <at_op>, <Xt>.  */
const char *
aarch64_ins_sysins_op (const aarch64_operand *self ATTRIBUTE_UNUSED,
		       const aarch64_opnd_info *info, aarch64_insn *code,
		       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* op1:CRn:CRm:op2 */
  insert_fields (code, info->sysins_op->value, inst->opcode->mask, 4,
		 FLD_op2, FLD_CRm, FLD_CRn, FLD_op1);
  return NULL;
}

/* Encode the memory barrier option operand for e.g. DMB <option>|#<imm>.  */

const char *
aarch64_ins_barrier (const aarch64_operand *self ATTRIBUTE_UNUSED,
		     const aarch64_opnd_info *info, aarch64_insn *code,
		     const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* CRm */
  insert_field (FLD_CRm, code, info->barrier->value, 0);
  return NULL;
}

/* Encode the prefetch operation option operand for e.g.
     PRFM <prfop>, [<Xn|SP>{, #<pimm>}].  */

const char *
aarch64_ins_prfop (const aarch64_operand *self ATTRIBUTE_UNUSED,
		   const aarch64_opnd_info *info, aarch64_insn *code,
		   const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* prfop in Rt */
  insert_field (FLD_Rt, code, info->prfop->value, 0);
  return NULL;
}

/* Encode the hint number for instructions that alias HINT but take an
   operand.  */

const char *
aarch64_ins_hint (const aarch64_operand *self ATTRIBUTE_UNUSED,
		  const aarch64_opnd_info *info, aarch64_insn *code,
		  const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* CRm:op2.  */
  insert_fields (code, info->hint_option->value, 0, 2, FLD_op2, FLD_CRm);
  return NULL;
}

/* Encode the extended register operand for e.g.
     STR <Qt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
const char *
aarch64_ins_reg_extended (const aarch64_operand *self ATTRIBUTE_UNUSED,
			  const aarch64_opnd_info *info, aarch64_insn *code,
			  const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  enum aarch64_modifier_kind kind;

  /* Rm */
  insert_field (FLD_Rm, code, info->reg.regno, 0);
  /* option */
  kind = info->shifter.kind;
  if (kind == AARCH64_MOD_LSL)
    kind = info->qualifier == AARCH64_OPND_QLF_W
      ? AARCH64_MOD_UXTW : AARCH64_MOD_UXTX;
  insert_field (FLD_option, code, aarch64_get_operand_modifier_value (kind), 0);
  /* imm3 */
  insert_field (FLD_imm3, code, info->shifter.amount, 0);

  return NULL;
}

/* Encode the shifted register operand for e.g.
     SUBS <Xd>, <Xn>, <Xm> {, <shift> #<amount>}.  */
const char *
aarch64_ins_reg_shifted (const aarch64_operand *self ATTRIBUTE_UNUSED,
			 const aarch64_opnd_info *info, aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  /* Rm */
  insert_field (FLD_Rm, code, info->reg.regno, 0);
  /* shift */
  insert_field (FLD_shift, code,
		aarch64_get_operand_modifier_value (info->shifter.kind), 0);
  /* imm6 */
  insert_field (FLD_imm6, code, info->shifter.amount, 0);

  return NULL;
}

/* Encode an SVE address [<base>, #<simm4>*<factor>, MUL VL],
   where <simm4> is a 4-bit signed value and where <factor> is 1 plus
   SELF's operand-dependent value.  fields[0] specifies the field that
   holds <base>.  <simm4> is encoded in the SVE_imm4 field.  */
const char *
aarch64_ins_sve_addr_ri_s4xvl (const aarch64_operand *self,
			       const aarch64_opnd_info *info,
			       aarch64_insn *code,
			       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int factor = 1 + get_operand_specific_data (self);
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (FLD_SVE_imm4, code, info->addr.offset.imm / factor, 0);
  return NULL;
}

/* Encode an SVE address [<base>, #<simm6>*<factor>, MUL VL],
   where <simm6> is a 6-bit signed value and where <factor> is 1 plus
   SELF's operand-dependent value.  fields[0] specifies the field that
   holds <base>.  <simm6> is encoded in the SVE_imm6 field.  */
const char *
aarch64_ins_sve_addr_ri_s6xvl (const aarch64_operand *self,
			       const aarch64_opnd_info *info,
			       aarch64_insn *code,
			       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int factor = 1 + get_operand_specific_data (self);
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (FLD_SVE_imm6, code, info->addr.offset.imm / factor, 0);
  return NULL;
}

/* Encode an SVE address [<base>, #<simm9>*<factor>, MUL VL],
   where <simm9> is a 9-bit signed value and where <factor> is 1 plus
   SELF's operand-dependent value.  fields[0] specifies the field that
   holds <base>.  <simm9> is encoded in the concatenation of the SVE_imm6
   and imm3 fields, with imm3 being the less-significant part.  */
const char *
aarch64_ins_sve_addr_ri_s9xvl (const aarch64_operand *self,
			       const aarch64_opnd_info *info,
			       aarch64_insn *code,
			       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int factor = 1 + get_operand_specific_data (self);
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_fields (code, info->addr.offset.imm / factor, 0,
		 2, FLD_imm3, FLD_SVE_imm6);
  return NULL;
}

/* Encode an SVE address [X<n>, #<SVE_imm4> << <shift>], where <SVE_imm4>
   is a 4-bit signed number and where <shift> is SELF's operand-dependent
   value.  fields[0] specifies the base register field.  */
const char *
aarch64_ins_sve_addr_ri_s4 (const aarch64_operand *self,
			    const aarch64_opnd_info *info, aarch64_insn *code,
			    const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int factor = 1 << get_operand_specific_data (self);
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (FLD_SVE_imm4, code, info->addr.offset.imm / factor, 0);
  return NULL;
}

/* Encode an SVE address [X<n>, #<SVE_imm6> << <shift>], where <SVE_imm6>
   is a 6-bit unsigned number and where <shift> is SELF's operand-dependent
   value.  fields[0] specifies the base register field.  */
const char *
aarch64_ins_sve_addr_ri_u6 (const aarch64_operand *self,
			    const aarch64_opnd_info *info, aarch64_insn *code,
			    const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int factor = 1 << get_operand_specific_data (self);
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (FLD_SVE_imm6, code, info->addr.offset.imm / factor, 0);
  return NULL;
}

/* Encode an SVE address [X<n>, X<m>{, LSL #<shift>}], where <shift>
   is SELF's operand-dependent value.  fields[0] specifies the base
   register field and fields[1] specifies the offset register field.  */
const char *
aarch64_ins_sve_addr_rr_lsl (const aarch64_operand *self,
			     const aarch64_opnd_info *info, aarch64_insn *code,
			     const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (self->fields[1], code, info->addr.offset.regno, 0);
  return NULL;
}

/* Encode an SVE address [X<n>, Z<m>.<T>, (S|U)XTW {#<shift>}], where
   <shift> is SELF's operand-dependent value.  fields[0] specifies the
   base register field, fields[1] specifies the offset register field and
   fields[2] is a single-bit field that selects SXTW over UXTW.  */
const char *
aarch64_ins_sve_addr_rz_xtw (const aarch64_operand *self,
			     const aarch64_opnd_info *info, aarch64_insn *code,
			     const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (self->fields[1], code, info->addr.offset.regno, 0);
  if (info->shifter.kind == AARCH64_MOD_UXTW)
    insert_field (self->fields[2], code, 0, 0);
  else
    insert_field (self->fields[2], code, 1, 0);
  return NULL;
}

/* Encode an SVE address [Z<n>.<T>, #<imm5> << <shift>], where <imm5> is a
   5-bit unsigned number and where <shift> is SELF's operand-dependent value.
   fields[0] specifies the base register field.  */
const char *
aarch64_ins_sve_addr_zi_u5 (const aarch64_operand *self,
			    const aarch64_opnd_info *info, aarch64_insn *code,
			    const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  int factor = 1 << get_operand_specific_data (self);
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (FLD_imm5, code, info->addr.offset.imm / factor, 0);
  return NULL;
}

/* Encode an SVE address [Z<n>.<T>, Z<m>.<T>{, <modifier> {#<msz>}}],
   where <modifier> is fixed by the instruction and where <msz> is a
   2-bit unsigned number.  fields[0] specifies the base register field
   and fields[1] specifies the offset register field.  */
static const char *
aarch64_ext_sve_addr_zz (const aarch64_operand *self,
			 const aarch64_opnd_info *info, aarch64_insn *code)
{
  insert_field (self->fields[0], code, info->addr.base_regno, 0);
  insert_field (self->fields[1], code, info->addr.offset.regno, 0);
  insert_field (FLD_SVE_msz, code, info->shifter.amount, 0);
  return NULL;
}

/* Encode an SVE address [Z<n>.<T>, Z<m>.<T>{, LSL #<msz>}], where
   <msz> is a 2-bit unsigned number.  fields[0] specifies the base register
   field and fields[1] specifies the offset register field.  */
const char *
aarch64_ins_sve_addr_zz_lsl (const aarch64_operand *self,
			     const aarch64_opnd_info *info, aarch64_insn *code,
			     const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  return aarch64_ext_sve_addr_zz (self, info, code);
}

/* Encode an SVE address [Z<n>.<T>, Z<m>.<T>, SXTW {#<msz>}], where
   <msz> is a 2-bit unsigned number.  fields[0] specifies the base register
   field and fields[1] specifies the offset register field.  */
const char *
aarch64_ins_sve_addr_zz_sxtw (const aarch64_operand *self,
			      const aarch64_opnd_info *info,
			      aarch64_insn *code,
			      const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  return aarch64_ext_sve_addr_zz (self, info, code);
}

/* Encode an SVE address [Z<n>.<T>, Z<m>.<T>, UXTW {#<msz>}], where
   <msz> is a 2-bit unsigned number.  fields[0] specifies the base register
   field and fields[1] specifies the offset register field.  */
const char *
aarch64_ins_sve_addr_zz_uxtw (const aarch64_operand *self,
			      const aarch64_opnd_info *info,
			      aarch64_insn *code,
			      const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  return aarch64_ext_sve_addr_zz (self, info, code);
}

/* Encode an SVE ADD/SUB immediate.  */
const char *
aarch64_ins_sve_aimm (const aarch64_operand *self,
		      const aarch64_opnd_info *info, aarch64_insn *code,
		      const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  if (info->shifter.amount == 8)
    insert_all_fields (self, code, (info->imm.value & 0xff) | 256);
  else if (info->imm.value != 0 && (info->imm.value & 0xff) == 0)
    insert_all_fields (self, code, ((info->imm.value / 256) & 0xff) | 256);
  else
    insert_all_fields (self, code, info->imm.value & 0xff);
  return NULL;
}

/* Encode an SVE CPY/DUP immediate.  */
const char *
aarch64_ins_sve_asimm (const aarch64_operand *self,
		       const aarch64_opnd_info *info, aarch64_insn *code,
		       const aarch64_inst *inst)
{
  return aarch64_ins_sve_aimm (self, info, code, inst);
}

/* Encode Zn[MM], where MM has a 7-bit triangular encoding.  The fields
   array specifies which field to use for Zn.  MM is encoded in the
   concatenation of imm5 and SVE_tszh, with imm5 being the less
   significant part.  */
const char *
aarch64_ins_sve_index (const aarch64_operand *self,
		       const aarch64_opnd_info *info, aarch64_insn *code,
		       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  unsigned int esize = aarch64_get_qualifier_esize (info->qualifier);
  insert_field (self->fields[0], code, info->reglane.regno, 0);
  insert_fields (code, (info->reglane.index * 2 + 1) * esize, 0,
		 2, FLD_imm5, FLD_SVE_tszh);
  return NULL;
}

/* Encode a logical/bitmask immediate for the MOV alias of SVE DUPM.  */
const char *
aarch64_ins_sve_limm_mov (const aarch64_operand *self,
			  const aarch64_opnd_info *info, aarch64_insn *code,
			  const aarch64_inst *inst)
{
  return aarch64_ins_limm (self, info, code, inst);
}

/* Encode Zn[MM], where Zn occupies the least-significant part of the field
   and where MM occupies the most-significant part.  The operand-dependent
   value specifies the number of bits in Zn.  */
const char *
aarch64_ins_sve_quad_index (const aarch64_operand *self,
			    const aarch64_opnd_info *info, aarch64_insn *code,
			    const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  unsigned int reg_bits = get_operand_specific_data (self);
  assert (info->reglane.regno < (1U << reg_bits));
  unsigned int val = (info->reglane.index << reg_bits) + info->reglane.regno;
  insert_all_fields (self, code, val);
  return NULL;
}

/* Encode {Zn.<T> - Zm.<T>}.  The fields array specifies which field
   to use for Zn.  */
const char *
aarch64_ins_sve_reglist (const aarch64_operand *self,
			 const aarch64_opnd_info *info, aarch64_insn *code,
			 const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_field (self->fields[0], code, info->reglist.first_regno, 0);
  return NULL;
}

/* Encode <pattern>{, MUL #<amount>}.  The fields array specifies which
   fields to use for <pattern>.  <amount> - 1 is encoded in the SVE_imm4
   field.  */
const char *
aarch64_ins_sve_scale (const aarch64_operand *self,
		       const aarch64_opnd_info *info, aarch64_insn *code,
		       const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  insert_all_fields (self, code, info->imm.value);
  insert_field (FLD_SVE_imm4, code, info->shifter.amount - 1, 0);
  return NULL;
}

/* Encode an SVE shift left immediate.  */
const char *
aarch64_ins_sve_shlimm (const aarch64_operand *self,
			const aarch64_opnd_info *info, aarch64_insn *code,
			const aarch64_inst *inst)
{
  const aarch64_opnd_info *prev_operand;
  unsigned int esize;

  assert (info->idx > 0);
  prev_operand = &inst->operands[info->idx - 1];
  esize = aarch64_get_qualifier_esize (prev_operand->qualifier);
  insert_all_fields (self, code, 8 * esize + info->imm.value);
  return NULL;
}

/* Encode an SVE shift right immediate.  */
const char *
aarch64_ins_sve_shrimm (const aarch64_operand *self,
			const aarch64_opnd_info *info, aarch64_insn *code,
			const aarch64_inst *inst)
{
  const aarch64_opnd_info *prev_operand;
  unsigned int esize;

  assert (info->idx > 0);
  prev_operand = &inst->operands[info->idx - 1];
  esize = aarch64_get_qualifier_esize (prev_operand->qualifier);
  insert_all_fields (self, code, 16 * esize - info->imm.value);
  return NULL;
}

/* Encode a single-bit immediate that selects between #0.5 and #1.0.
   The fields array specifies which field to use.  */
const char *
aarch64_ins_sve_float_half_one (const aarch64_operand *self,
				const aarch64_opnd_info *info,
				aarch64_insn *code,
				const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  if (info->imm.value == 0x3f000000)
    insert_field (self->fields[0], code, 0, 0);
  else
    insert_field (self->fields[0], code, 1, 0);
  return NULL;
}

/* Encode a single-bit immediate that selects between #0.5 and #2.0.
   The fields array specifies which field to use.  */
const char *
aarch64_ins_sve_float_half_two (const aarch64_operand *self,
				const aarch64_opnd_info *info,
				aarch64_insn *code,
				const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  if (info->imm.value == 0x3f000000)
    insert_field (self->fields[0], code, 0, 0);
  else
    insert_field (self->fields[0], code, 1, 0);
  return NULL;
}

/* Encode a single-bit immediate that selects between #0.0 and #1.0.
   The fields array specifies which field to use.  */
const char *
aarch64_ins_sve_float_zero_one (const aarch64_operand *self,
				const aarch64_opnd_info *info,
				aarch64_insn *code,
				const aarch64_inst *inst ATTRIBUTE_UNUSED)
{
  if (info->imm.value == 0)
    insert_field (self->fields[0], code, 0, 0);
  else
    insert_field (self->fields[0], code, 1, 0);
  return NULL;
}

/* Miscellaneous encoding functions.  */

/* Encode size[0], i.e. bit 22, for
     e.g. FCVTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */

static void
encode_asimd_fcvt (aarch64_inst *inst)
{
  aarch64_insn value;
  aarch64_field field = {0, 0};
  enum aarch64_opnd_qualifier qualifier;

  switch (inst->opcode->op)
    {
    case OP_FCVTN:
    case OP_FCVTN2:
      /* FCVTN<Q> <Vd>.<Tb>, <Vn>.<Ta>.  */
      qualifier = inst->operands[1].qualifier;
      break;
    case OP_FCVTL:
    case OP_FCVTL2:
      /* FCVTL<Q> <Vd>.<Ta>, <Vn>.<Tb>.  */
      qualifier = inst->operands[0].qualifier;
      break;
    default:
      assert (0);
    }
  assert (qualifier == AARCH64_OPND_QLF_V_4S
	  || qualifier == AARCH64_OPND_QLF_V_2D);
  value = (qualifier == AARCH64_OPND_QLF_V_4S) ? 0 : 1;
  gen_sub_field (FLD_size, 0, 1, &field);
  insert_field_2 (&field, &inst->value, value, 0);
}

/* Encode size[0], i.e. bit 22, for
     e.g. FCVTXN <Vb><d>, <Va><n>.  */

static void
encode_asisd_fcvtxn (aarch64_inst *inst)
{
  aarch64_insn val = 1;
  aarch64_field field = {0, 0};
  assert (inst->operands[0].qualifier == AARCH64_OPND_QLF_S_S);
  gen_sub_field (FLD_size, 0, 1, &field);
  insert_field_2 (&field, &inst->value, val, 0);
}

/* Encode the 'opc' field for e.g. FCVT <Dd>, <Sn>.  */
static void
encode_fcvt (aarch64_inst *inst)
{
  aarch64_insn val;
  const aarch64_field field = {15, 2};

  /* opc dstsize */
  switch (inst->operands[0].qualifier)
    {
    case AARCH64_OPND_QLF_S_S: val = 0; break;
    case AARCH64_OPND_QLF_S_D: val = 1; break;
    case AARCH64_OPND_QLF_S_H: val = 3; break;
    default: abort ();
    }
  insert_field_2 (&field, &inst->value, val, 0);

  return;
}

/* Return the index in qualifiers_list that INST is using.  Should only
   be called once the qualifiers are known to be valid.  */

static int
aarch64_get_variant (struct aarch64_inst *inst)
{
  int i, nops, variant;

  nops = aarch64_num_of_operands (inst->opcode);
  for (variant = 0; variant < AARCH64_MAX_QLF_SEQ_NUM; ++variant)
    {
      for (i = 0; i < nops; ++i)
	if (inst->opcode->qualifiers_list[variant][i]
	    != inst->operands[i].qualifier)
	  break;
      if (i == nops)
	return variant;
    }
  abort ();
}

/* Do miscellaneous encodings that are not common enough to be driven by
   flags.  */

static void
do_misc_encoding (aarch64_inst *inst)
{
  unsigned int value;

  switch (inst->opcode->op)
    {
    case OP_FCVT:
      encode_fcvt (inst);
      break;
    case OP_FCVTN:
    case OP_FCVTN2:
    case OP_FCVTL:
    case OP_FCVTL2:
      encode_asimd_fcvt (inst);
      break;
    case OP_FCVTXN_S:
      encode_asisd_fcvtxn (inst);
      break;
    case OP_MOV_P_P:
    case OP_MOVS_P_P:
      /* Copy Pn to Pm and Pg.  */
      value = extract_field (FLD_SVE_Pn, inst->value, 0);
      insert_field (FLD_SVE_Pm, &inst->value, value, 0);
      insert_field (FLD_SVE_Pg4_10, &inst->value, value, 0);
      break;
    case OP_MOV_Z_P_Z:
      /* Copy Zd to Zm.  */
      value = extract_field (FLD_SVE_Zd, inst->value, 0);
      insert_field (FLD_SVE_Zm_16, &inst->value, value, 0);
      break;
    case OP_MOV_Z_V:
      /* Fill in the zero immediate.  */
      insert_fields (&inst->value, 1 << aarch64_get_variant (inst), 0,
		     2, FLD_imm5, FLD_SVE_tszh);
      break;
    case OP_MOV_Z_Z:
      /* Copy Zn to Zm.  */
      value = extract_field (FLD_SVE_Zn, inst->value, 0);
      insert_field (FLD_SVE_Zm_16, &inst->value, value, 0);
      break;
    case OP_MOV_Z_Zi:
      break;
    case OP_MOVM_P_P_P:
      /* Copy Pd to Pm.  */
      value = extract_field (FLD_SVE_Pd, inst->value, 0);
      insert_field (FLD_SVE_Pm, &inst->value, value, 0);
      break;
    case OP_MOVZS_P_P_P:
    case OP_MOVZ_P_P_P:
      /* Copy Pn to Pm.  */
      value = extract_field (FLD_SVE_Pn, inst->value, 0);
      insert_field (FLD_SVE_Pm, &inst->value, value, 0);
      break;
    case OP_NOTS_P_P_P_Z:
    case OP_NOT_P_P_P_Z:
      /* Copy Pg to Pm.  */
      value = extract_field (FLD_SVE_Pg4_10, inst->value, 0);
      insert_field (FLD_SVE_Pm, &inst->value, value, 0);
      break;
    default: break;
    }
}

/* Encode the 'size' and 'Q' field for e.g. SHADD.  */
static void
encode_sizeq (aarch64_inst *inst)
{
  aarch64_insn sizeq;
  enum aarch64_field_kind kind;
  int idx;

  /* Get the index of the operand whose information we are going to use
     to encode the size and Q fields.
     This is deduced from the possible valid qualifier lists.  */
  idx = aarch64_select_operand_for_sizeq_field_coding (inst->opcode);
  DEBUG_TRACE ("idx: %d; qualifier: %s", idx,
	       aarch64_get_qualifier_name (inst->operands[idx].qualifier));
  sizeq = aarch64_get_qualifier_standard_value (inst->operands[idx].qualifier);
  /* Q */
  insert_field (FLD_Q, &inst->value, sizeq & 0x1, inst->opcode->mask);
  /* size */
  if (inst->opcode->iclass == asisdlse
     || inst->opcode->iclass == asisdlsep
     || inst->opcode->iclass == asisdlso
     || inst->opcode->iclass == asisdlsop)
    kind = FLD_vldst_size;
  else
    kind = FLD_size;
  insert_field (kind, &inst->value, (sizeq >> 1) & 0x3, inst->opcode->mask);
}

/* Opcodes that have fields shared by multiple operands are usually flagged
   with flags.  In this function, we detect such flags and use the
   information in one of the related operands to do the encoding.  The 'one'
   operand is not any operand but one of the operands that has the enough
   information for such an encoding.  */

static void
do_special_encoding (struct aarch64_inst *inst)
{
  int idx;
  aarch64_insn value = 0;

  DEBUG_TRACE ("enter with coding 0x%x", (uint32_t) inst->value);

  /* Condition for truly conditional executed instructions, e.g. b.cond.  */
  if (inst->opcode->flags & F_COND)
    {
      insert_field (FLD_cond2, &inst->value, inst->cond->value, 0);
    }
  if (inst->opcode->flags & F_SF)
    {
      idx = select_operand_for_sf_field_coding (inst->opcode);
      value = (inst->operands[idx].qualifier == AARCH64_OPND_QLF_X
	       || inst->operands[idx].qualifier == AARCH64_OPND_QLF_SP)
	? 1 : 0;
      insert_field (FLD_sf, &inst->value, value, 0);
      if (inst->opcode->flags & F_N)
	insert_field (FLD_N, &inst->value, value, inst->opcode->mask);
    }
  if (inst->opcode->flags & F_LSE_SZ)
    {
      idx = select_operand_for_sf_field_coding (inst->opcode);
      value = (inst->operands[idx].qualifier == AARCH64_OPND_QLF_X
	       || inst->operands[idx].qualifier == AARCH64_OPND_QLF_SP)
	? 1 : 0;
      insert_field (FLD_lse_sz, &inst->value, value, 0);
    }
  if (inst->opcode->flags & F_SIZEQ)
    encode_sizeq (inst);
  if (inst->opcode->flags & F_FPTYPE)
    {
      idx = select_operand_for_fptype_field_coding (inst->opcode);
      switch (inst->operands[idx].qualifier)
	{
	case AARCH64_OPND_QLF_S_S: value = 0; break;
	case AARCH64_OPND_QLF_S_D: value = 1; break;
	case AARCH64_OPND_QLF_S_H: value = 3; break;
	default: assert (0);
	}
      insert_field (FLD_type, &inst->value, value, 0);
    }
  if (inst->opcode->flags & F_SSIZE)
    {
      enum aarch64_opnd_qualifier qualifier;
      idx = select_operand_for_scalar_size_field_coding (inst->opcode);
      qualifier = inst->operands[idx].qualifier;
      assert (qualifier >= AARCH64_OPND_QLF_S_B
	      && qualifier <= AARCH64_OPND_QLF_S_Q);
      value = aarch64_get_qualifier_standard_value (qualifier);
      insert_field (FLD_size, &inst->value, value, inst->opcode->mask);
    }
  if (inst->opcode->flags & F_T)
    {
      int num;	/* num of consecutive '0's on the right side of imm5<3:0>.  */
      aarch64_field field = {0, 0};
      enum aarch64_opnd_qualifier qualifier;

      idx = 0;
      qualifier = inst->operands[idx].qualifier;
      assert (aarch64_get_operand_class (inst->opcode->operands[0])
	      == AARCH64_OPND_CLASS_SIMD_REG
	      && qualifier >= AARCH64_OPND_QLF_V_8B
	      && qualifier <= AARCH64_OPND_QLF_V_2D);
      /* imm5<3:0>	q	<t>
	 0000		x	reserved
	 xxx1		0	8b
	 xxx1		1	16b
	 xx10		0	4h
	 xx10		1	8h
	 x100		0	2s
	 x100		1	4s
	 1000		0	reserved
	 1000		1	2d  */
      value = aarch64_get_qualifier_standard_value (qualifier);
      insert_field (FLD_Q, &inst->value, value & 0x1, inst->opcode->mask);
      num = (int) value >> 1;
      assert (num >= 0 && num <= 3);
      gen_sub_field (FLD_imm5, 0, num + 1, &field);
      insert_field_2 (&field, &inst->value, 1 << num, inst->opcode->mask);
    }
  if (inst->opcode->flags & F_GPRSIZE_IN_Q)
    {
      /* Use Rt to encode in the case of e.g.
	 STXP <Ws>, <Xt1>, <Xt2>, [<Xn|SP>{,#0}].  */
      enum aarch64_opnd_qualifier qualifier;
      idx = aarch64_operand_index (inst->opcode->operands, AARCH64_OPND_Rt);
      if (idx == -1)
	/* Otherwise use the result operand, which has to be a integer
	   register.  */
	idx = 0;
      assert (idx == 0 || idx == 1);
      assert (aarch64_get_operand_class (inst->opcode->operands[idx])
	      == AARCH64_OPND_CLASS_INT_REG);
      qualifier = inst->operands[idx].qualifier;
      insert_field (FLD_Q, &inst->value,
		    aarch64_get_qualifier_standard_value (qualifier), 0);
    }
  if (inst->opcode->flags & F_LDS_SIZE)
    {
      /* e.g. LDRSB <Wt>, [<Xn|SP>, <R><m>{, <extend> {<amount>}}].  */
      enum aarch64_opnd_qualifier qualifier;
      aarch64_field field = {0, 0};
      assert (aarch64_get_operand_class (inst->opcode->operands[0])
	      == AARCH64_OPND_CLASS_INT_REG);
      gen_sub_field (FLD_opc, 0, 1, &field);
      qualifier = inst->operands[0].qualifier;
      insert_field_2 (&field, &inst->value,
		      1 - aarch64_get_qualifier_standard_value (qualifier), 0);
    }
  /* Miscellaneous encoding as the last step.  */
  if (inst->opcode->flags & F_MISC)
    do_misc_encoding (inst);

  DEBUG_TRACE ("exit with coding 0x%x", (uint32_t) inst->value);
}

/* Some instructions (including all SVE ones) use the instruction class
   to describe how a qualifiers_list index is represented in the instruction
   encoding.  If INST is such an instruction, encode the chosen qualifier
   variant.  */

static void
aarch64_encode_variant_using_iclass (struct aarch64_inst *inst)
{
  switch (inst->opcode->iclass)
    {
    case sve_cpy:
      insert_fields (&inst->value, aarch64_get_variant (inst),
		     0, 2, FLD_SVE_M_14, FLD_size);
      break;

    case sve_index:
    case sve_shift_pred:
    case sve_shift_unpred:
      /* For indices and shift amounts, the variant is encoded as
	 part of the immediate.  */
      break;

    case sve_limm:
      /* For sve_limm, the .B, .H, and .S forms are just a convenience
	 and depend on the immediate.  They don't have a separate
	 encoding.  */
      break;

    case sve_misc:
      /* sve_misc instructions have only a single variant.  */
      break;

    case sve_movprfx:
      insert_fields (&inst->value, aarch64_get_variant (inst),
		     0, 2, FLD_SVE_M_16, FLD_size);
      break;

    case sve_pred_zm:
      insert_field (FLD_SVE_M_4, &inst->value, aarch64_get_variant (inst), 0);
      break;

    case sve_size_bhs:
    case sve_size_bhsd:
      insert_field (FLD_size, &inst->value, aarch64_get_variant (inst), 0);
      break;

    case sve_size_hsd:
      insert_field (FLD_size, &inst->value, aarch64_get_variant (inst) + 1, 0);
      break;

    case sve_size_sd:
      insert_field (FLD_SVE_sz, &inst->value, aarch64_get_variant (inst), 0);
      break;

    default:
      break;
    }
}

/* Converters converting an alias opcode instruction to its real form.  */

/* ROR <Wd>, <Ws>, #<shift>
     is equivalent to:
   EXTR <Wd>, <Ws>, <Ws>, #<shift>.  */
static void
convert_ror_to_extr (aarch64_inst *inst)
{
  copy_operand_info (inst, 3, 2);
  copy_operand_info (inst, 2, 1);
}

/* UXTL<Q> <Vd>.<Ta>, <Vn>.<Tb>
     is equivalent to:
   USHLL<Q> <Vd>.<Ta>, <Vn>.<Tb>, #0.  */
static void
convert_xtl_to_shll (aarch64_inst *inst)
{
  inst->operands[2].qualifier = inst->operands[1].qualifier;
  inst->operands[2].imm.value = 0;
}

/* Convert
     LSR <Xd>, <Xn>, #<shift>
   to
     UBFM <Xd>, <Xn>, #<shift>, #63.  */
static void
convert_sr_to_bfm (aarch64_inst *inst)
{
  inst->operands[3].imm.value =
    inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31 ? 31 : 63;
}

/* Convert MOV to ORR.  */
static void
convert_mov_to_orr (aarch64_inst *inst)
{
  /* MOV <Vd>.<T>, <Vn>.<T>
     is equivalent to:
     ORR <Vd>.<T>, <Vn>.<T>, <Vn>.<T>.  */
  copy_operand_info (inst, 2, 1);
}

/* When <imms> >= <immr>, the instruction written:
     SBFX <Xd>, <Xn>, #<lsb>, #<width>
   is equivalent to:
     SBFM <Xd>, <Xn>, #<lsb>, #(<lsb>+<width>-1).  */

static void
convert_bfx_to_bfm (aarch64_inst *inst)
{
  int64_t lsb, width;

  /* Convert the operand.  */
  lsb = inst->operands[2].imm.value;
  width = inst->operands[3].imm.value;
  inst->operands[2].imm.value = lsb;
  inst->operands[3].imm.value = lsb + width - 1;
}

/* When <imms> < <immr>, the instruction written:
     SBFIZ <Xd>, <Xn>, #<lsb>, #<width>
   is equivalent to:
     SBFM <Xd>, <Xn>, #((64-<lsb>)&0x3f), #(<width>-1).  */

static void
convert_bfi_to_bfm (aarch64_inst *inst)
{
  int64_t lsb, width;

  /* Convert the operand.  */
  lsb = inst->operands[2].imm.value;
  width = inst->operands[3].imm.value;
  if (inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31)
    {
      inst->operands[2].imm.value = (32 - lsb) & 0x1f;
      inst->operands[3].imm.value = width - 1;
    }
  else
    {
      inst->operands[2].imm.value = (64 - lsb) & 0x3f;
      inst->operands[3].imm.value = width - 1;
    }
}

/* The instruction written:
     BFC <Xd>, #<lsb>, #<width>
   is equivalent to:
     BFM <Xd>, XZR, #((64-<lsb>)&0x3f), #(<width>-1).  */

static void
convert_bfc_to_bfm (aarch64_inst *inst)
{
  int64_t lsb, width;

  /* Insert XZR.  */
  copy_operand_info (inst, 3, 2);
  copy_operand_info (inst, 2, 1);
  copy_operand_info (inst, 1, 0);
  inst->operands[1].reg.regno = 0x1f;

  /* Convert the immediate operand.  */
  lsb = inst->operands[2].imm.value;
  width = inst->operands[3].imm.value;
  if (inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31)
    {
      inst->operands[2].imm.value = (32 - lsb) & 0x1f;
      inst->operands[3].imm.value = width - 1;
    }
  else
    {
      inst->operands[2].imm.value = (64 - lsb) & 0x3f;
      inst->operands[3].imm.value = width - 1;
    }
}

/* The instruction written:
     LSL <Xd>, <Xn>, #<shift>
   is equivalent to:
     UBFM <Xd>, <Xn>, #((64-<shift>)&0x3f), #(63-<shift>).  */

static void
convert_lsl_to_ubfm (aarch64_inst *inst)
{
  int64_t shift = inst->operands[2].imm.value;

  if (inst->operands[2].qualifier == AARCH64_OPND_QLF_imm_0_31)
    {
      inst->operands[2].imm.value = (32 - shift) & 0x1f;
      inst->operands[3].imm.value = 31 - shift;
    }
  else
    {
      inst->operands[2].imm.value = (64 - shift) & 0x3f;
      inst->operands[3].imm.value = 63 - shift;
    }
}

/* CINC <Wd>, <Wn>, <cond>
     is equivalent to:
   CSINC <Wd>, <Wn>, <Wn>, invert(<cond>).  */

static void
convert_to_csel (aarch64_inst *inst)
{
  copy_operand_info (inst, 3, 2);
  copy_operand_info (inst, 2, 1);
  inst->operands[3].cond = get_inverted_cond (inst->operands[3].cond);
}

/* CSET <Wd>, <cond>
     is equivalent to:
   CSINC <Wd>, WZR, WZR, invert(<cond>).  */

static void
convert_cset_to_csinc (aarch64_inst *inst)
{
  copy_operand_info (inst, 3, 1);
  copy_operand_info (inst, 2, 0);
  copy_operand_info (inst, 1, 0);
  inst->operands[1].reg.regno = 0x1f;
  inst->operands[2].reg.regno = 0x1f;
  inst->operands[3].cond = get_inverted_cond (inst->operands[3].cond);
}

/* MOV <Wd>, #<imm>
   is equivalent to:
   MOVZ <Wd>, #<imm16>, LSL #<shift>.  */

static void
convert_mov_to_movewide (aarch64_inst *inst)
{
  int is32;
  uint32_t shift_amount;
  uint64_t value;

  switch (inst->opcode->op)
    {
    case OP_MOV_IMM_WIDE:
      value = inst->operands[1].imm.value;
      break;
    case OP_MOV_IMM_WIDEN:
      value = ~inst->operands[1].imm.value;
      break;
    default:
      assert (0);
    }
  inst->operands[1].type = AARCH64_OPND_HALF;
  is32 = inst->operands[0].qualifier == AARCH64_OPND_QLF_W;
  if (! aarch64_wide_constant_p (value, is32, &shift_amount))
    /* The constraint check should have guaranteed this wouldn't happen.  */
    assert (0);
  value >>= shift_amount;
  value &= 0xffff;
  inst->operands[1].imm.value = value;
  inst->operands[1].shifter.kind = AARCH64_MOD_LSL;
  inst->operands[1].shifter.amount = shift_amount;
}

/* MOV <Wd>, #<imm>
     is equivalent to:
   ORR <Wd>, WZR, #<imm>.  */

static void
convert_mov_to_movebitmask (aarch64_inst *inst)
{
  copy_operand_info (inst, 2, 1);
  inst->operands[1].reg.regno = 0x1f;
  inst->operands[1].skip = 0;
}

/* Some alias opcodes are assembled by being converted to their real-form.  */

static void
convert_to_real (aarch64_inst *inst, const aarch64_opcode *real)
{
  const aarch64_opcode *alias = inst->opcode;

  if ((alias->flags & F_CONV) == 0)
    goto convert_to_real_return;

  switch (alias->op)
    {
    case OP_ASR_IMM:
    case OP_LSR_IMM:
      convert_sr_to_bfm (inst);
      break;
    case OP_LSL_IMM:
      convert_lsl_to_ubfm (inst);
      break;
    case OP_CINC:
    case OP_CINV:
    case OP_CNEG:
      convert_to_csel (inst);
      break;
    case OP_CSET:
    case OP_CSETM:
      convert_cset_to_csinc (inst);
      break;
    case OP_UBFX:
    case OP_BFXIL:
    case OP_SBFX:
      convert_bfx_to_bfm (inst);
      break;
    case OP_SBFIZ:
    case OP_BFI:
    case OP_UBFIZ:
      convert_bfi_to_bfm (inst);
      break;
    case OP_BFC:
      convert_bfc_to_bfm (inst);
      break;
    case OP_MOV_V:
      convert_mov_to_orr (inst);
      break;
    case OP_MOV_IMM_WIDE:
    case OP_MOV_IMM_WIDEN:
      convert_mov_to_movewide (inst);
      break;
    case OP_MOV_IMM_LOG:
      convert_mov_to_movebitmask (inst);
      break;
    case OP_ROR_IMM:
      convert_ror_to_extr (inst);
      break;
    case OP_SXTL:
    case OP_SXTL2:
    case OP_UXTL:
    case OP_UXTL2:
      convert_xtl_to_shll (inst);
      break;
    default:
      break;
    }

convert_to_real_return:
  aarch64_replace_opcode (inst, real);
}

/* Encode *INST_ORI of the opcode code OPCODE.
   Return the encoded result in *CODE and if QLF_SEQ is not NULL, return the
   matched operand qualifier sequence in *QLF_SEQ.  */

int
aarch64_opcode_encode (const aarch64_opcode *opcode,
		       const aarch64_inst *inst_ori, aarch64_insn *code,
		       aarch64_opnd_qualifier_t *qlf_seq,
		       aarch64_operand_error *mismatch_detail)
{
  int i;
  const aarch64_opcode *aliased;
  aarch64_inst copy, *inst;

  DEBUG_TRACE ("enter with %s", opcode->name);

  /* Create a copy of *INST_ORI, so that we can do any change we want.  */
  copy = *inst_ori;
  inst = &copy;

  assert (inst->opcode == NULL || inst->opcode == opcode);
  if (inst->opcode == NULL)
    inst->opcode = opcode;

  /* Constrain the operands.
     After passing this, the encoding is guaranteed to succeed.  */
  if (aarch64_match_operands_constraint (inst, mismatch_detail) == 0)
    {
      DEBUG_TRACE ("FAIL since operand constraint not met");
      return 0;
    }

  /* Get the base value.
     Note: this has to be before the aliasing handling below in order to
     get the base value from the alias opcode before we move on to the
     aliased opcode for encoding.  */
  inst->value = opcode->opcode;

  /* No need to do anything else if the opcode does not have any operand.  */
  if (aarch64_num_of_operands (opcode) == 0)
    goto encoding_exit;

  /* Assign operand indexes and check types.  Also put the matched
     operand qualifiers in *QLF_SEQ to return.  */
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i)
    {
      assert (opcode->operands[i] == inst->operands[i].type);
      inst->operands[i].idx = i;
      if (qlf_seq != NULL)
	*qlf_seq = inst->operands[i].qualifier;
    }

  aliased = aarch64_find_real_opcode (opcode);
  /* If the opcode is an alias and it does not ask for direct encoding by
     itself, the instruction will be transformed to the form of real opcode
     and the encoding will be carried out using the rules for the aliased
     opcode.  */
  if (aliased != NULL && (opcode->flags & F_CONV))
    {
      DEBUG_TRACE ("real opcode '%s' has been found for the alias  %s",
		   aliased->name, opcode->name);
      /* Convert the operands to the form of the real opcode.  */
      convert_to_real (inst, aliased);
      opcode = aliased;
    }

  aarch64_opnd_info *info = inst->operands;

  /* Call the inserter of each operand.  */
  for (i = 0; i < AARCH64_MAX_OPND_NUM; ++i, ++info)
    {
      const aarch64_operand *opnd;
      enum aarch64_opnd type = opcode->operands[i];
      if (type == AARCH64_OPND_NIL)
	break;
      if (info->skip)
	{
	  DEBUG_TRACE ("skip the incomplete operand %d", i);
	  continue;
	}
      opnd = &aarch64_operands[type];
      if (operand_has_inserter (opnd))
	aarch64_insert_operand (opnd, info, &inst->value, inst);
    }

  /* Call opcode encoders indicated by flags.  */
  if (opcode_has_special_coder (opcode))
    do_special_encoding (inst);

  /* Possibly use the instruction class to encode the chosen qualifier
     variant.  */
  aarch64_encode_variant_using_iclass (inst);

encoding_exit:
  DEBUG_TRACE ("exit with %s", opcode->name);

  *code = inst->value;

  return 1;
}
