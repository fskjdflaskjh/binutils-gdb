/* This file defines the interface between the Arm simulator and GDB.

   Copyright 2002, 2003, 2007, 2008 Free Software Foundation, Inc.

   Contributed by Red Hat.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#if !defined (SIM_ARM_H)
#define SIM_ARM_H

#ifdef __cplusplus
extern "C" { // }
#endif

enum sim_arm_regs
{
  SIM_ARM_R0_REGNUM,
  SIM_ARM_R1_REGNUM,
  SIM_ARM_R2_REGNUM,
  SIM_ARM_R3_REGNUM,
  SIM_ARM_R4_REGNUM,
  SIM_ARM_R5_REGNUM,
  SIM_ARM_R6_REGNUM,
  SIM_ARM_R7_REGNUM,
  SIM_ARM_R8_REGNUM,
  SIM_ARM_R9_REGNUM,
  SIM_ARM_R10_REGNUM,
  SIM_ARM_R11_REGNUM,
  SIM_ARM_R12_REGNUM,
  SIM_ARM_R13_REGNUM,
  SIM_ARM_R14_REGNUM,
  SIM_ARM_R15_REGNUM, /* PC */
  SIM_ARM_FP0_REGNUM,
  SIM_ARM_FP1_REGNUM,
  SIM_ARM_FP2_REGNUM,
  SIM_ARM_FP3_REGNUM,
  SIM_ARM_FP4_REGNUM,
  SIM_ARM_FP5_REGNUM,
  SIM_ARM_FP6_REGNUM,
  SIM_ARM_FP7_REGNUM,
  SIM_ARM_FPS_REGNUM,
  SIM_ARM_PS_REGNUM,
  SIM_ARM_MAVERIC_COP0R0_REGNUM,
  SIM_ARM_MAVERIC_COP0R1_REGNUM,
  SIM_ARM_MAVERIC_COP0R2_REGNUM,
  SIM_ARM_MAVERIC_COP0R3_REGNUM,
  SIM_ARM_MAVERIC_COP0R4_REGNUM,
  SIM_ARM_MAVERIC_COP0R5_REGNUM,
  SIM_ARM_MAVERIC_COP0R6_REGNUM,
  SIM_ARM_MAVERIC_COP0R7_REGNUM,
  SIM_ARM_MAVERIC_COP0R8_REGNUM,
  SIM_ARM_MAVERIC_COP0R9_REGNUM,
  SIM_ARM_MAVERIC_COP0R10_REGNUM,
  SIM_ARM_MAVERIC_COP0R11_REGNUM,
  SIM_ARM_MAVERIC_COP0R12_REGNUM,
  SIM_ARM_MAVERIC_COP0R13_REGNUM,
  SIM_ARM_MAVERIC_COP0R14_REGNUM,
  SIM_ARM_MAVERIC_COP0R15_REGNUM,
  SIM_ARM_MAVERIC_DSPSC_REGNUM,
  SIM_ARM_IWMMXT_COP0R0_REGNUM,
  SIM_ARM_IWMMXT_COP0R1_REGNUM,
  SIM_ARM_IWMMXT_COP0R2_REGNUM,
  SIM_ARM_IWMMXT_COP0R3_REGNUM,
  SIM_ARM_IWMMXT_COP0R4_REGNUM,
  SIM_ARM_IWMMXT_COP0R5_REGNUM,
  SIM_ARM_IWMMXT_COP0R6_REGNUM,
  SIM_ARM_IWMMXT_COP0R7_REGNUM,
  SIM_ARM_IWMMXT_COP0R8_REGNUM,
  SIM_ARM_IWMMXT_COP0R9_REGNUM,
  SIM_ARM_IWMMXT_COP0R10_REGNUM,
  SIM_ARM_IWMMXT_COP0R11_REGNUM,
  SIM_ARM_IWMMXT_COP0R12_REGNUM,
  SIM_ARM_IWMMXT_COP0R13_REGNUM,
  SIM_ARM_IWMMXT_COP0R14_REGNUM,
  SIM_ARM_IWMMXT_COP0R15_REGNUM,
  SIM_ARM_IWMMXT_COP1R0_REGNUM,
  SIM_ARM_IWMMXT_COP1R1_REGNUM,
  SIM_ARM_IWMMXT_COP1R2_REGNUM,
  SIM_ARM_IWMMXT_COP1R3_REGNUM,
  SIM_ARM_IWMMXT_COP1R4_REGNUM,
  SIM_ARM_IWMMXT_COP1R5_REGNUM,
  SIM_ARM_IWMMXT_COP1R6_REGNUM,
  SIM_ARM_IWMMXT_COP1R7_REGNUM,
  SIM_ARM_IWMMXT_COP1R8_REGNUM,
  SIM_ARM_IWMMXT_COP1R9_REGNUM,
  SIM_ARM_IWMMXT_COP1R10_REGNUM,
  SIM_ARM_IWMMXT_COP1R11_REGNUM,
  SIM_ARM_IWMMXT_COP1R12_REGNUM,
  SIM_ARM_IWMMXT_COP1R13_REGNUM,
  SIM_ARM_IWMMXT_COP1R14_REGNUM,
  SIM_ARM_IWMMXT_COP1R15_REGNUM
};

#ifdef __cplusplus
}
#endif

#endif
