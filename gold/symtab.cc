// symtab.cc -- the gold symbol table

// Copyright 2006, 2007, 2008 Free Software Foundation, Inc.
// Written by Ian Lance Taylor <iant@google.com>.

// This file is part of gold.

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
// MA 02110-1301, USA.

#include "gold.h"

#include <stdint.h>
#include <set>
#include <string>
#include <utility>
#include "demangle.h"

#include "object.h"
#include "dwarf_reader.h"
#include "dynobj.h"
#include "output.h"
#include "target.h"
#include "workqueue.h"
#include "symtab.h"

namespace gold
{

// Class Symbol.

// Initialize fields in Symbol.  This initializes everything except u_
// and source_.

void
Symbol::init_fields(const char* name, const char* version,
		    elfcpp::STT type, elfcpp::STB binding,
		    elfcpp::STV visibility, unsigned char nonvis)
{
  this->name_ = name;
  this->version_ = version;
  this->symtab_index_ = 0;
  this->dynsym_index_ = 0;
  this->got_offset_ = 0;
  this->plt_offset_ = 0;
  this->type_ = type;
  this->binding_ = binding;
  this->visibility_ = visibility;
  this->nonvis_ = nonvis;
  this->is_target_special_ = false;
  this->is_def_ = false;
  this->is_forwarder_ = false;
  this->has_alias_ = false;
  this->needs_dynsym_entry_ = false;
  this->in_reg_ = false;
  this->in_dyn_ = false;
  this->has_got_offset_ = false;
  this->has_plt_offset_ = false;
  this->has_warning_ = false;
  this->is_copied_from_dynobj_ = false;
  this->is_forced_local_ = false;
}

// Return the demangled version of the symbol's name, but only
// if the --demangle flag was set.

static std::string
demangle(const char* name)
{
  if (!parameters->demangle())
    return name;

  // cplus_demangle allocates memory for the result it returns,
  // and returns NULL if the name is already demangled.
  char* demangled_name = cplus_demangle(name, DMGL_ANSI | DMGL_PARAMS);
  if (demangled_name == NULL)
    return name;

  std::string retval(demangled_name);
  free(demangled_name);
  return retval;
}

std::string
Symbol::demangled_name() const
{
  return demangle(this->name());
}

// Initialize the fields in the base class Symbol for SYM in OBJECT.

template<int size, bool big_endian>
void
Symbol::init_base(const char* name, const char* version, Object* object,
		  const elfcpp::Sym<size, big_endian>& sym)
{
  this->init_fields(name, version, sym.get_st_type(), sym.get_st_bind(),
		    sym.get_st_visibility(), sym.get_st_nonvis());
  this->u_.from_object.object = object;
  // FIXME: Handle SHN_XINDEX.
  this->u_.from_object.shndx = sym.get_st_shndx();
  this->source_ = FROM_OBJECT;
  this->in_reg_ = !object->is_dynamic();
  this->in_dyn_ = object->is_dynamic();
}

// Initialize the fields in the base class Symbol for a symbol defined
// in an Output_data.

void
Symbol::init_base(const char* name, Output_data* od, elfcpp::STT type,
		  elfcpp::STB binding, elfcpp::STV visibility,
		  unsigned char nonvis, bool offset_is_from_end)
{
  this->init_fields(name, NULL, type, binding, visibility, nonvis);
  this->u_.in_output_data.output_data = od;
  this->u_.in_output_data.offset_is_from_end = offset_is_from_end;
  this->source_ = IN_OUTPUT_DATA;
  this->in_reg_ = true;
}

// Initialize the fields in the base class Symbol for a symbol defined
// in an Output_segment.

void
Symbol::init_base(const char* name, Output_segment* os, elfcpp::STT type,
		  elfcpp::STB binding, elfcpp::STV visibility,
		  unsigned char nonvis, Segment_offset_base offset_base)
{
  this->init_fields(name, NULL, type, binding, visibility, nonvis);
  this->u_.in_output_segment.output_segment = os;
  this->u_.in_output_segment.offset_base = offset_base;
  this->source_ = IN_OUTPUT_SEGMENT;
  this->in_reg_ = true;
}

// Initialize the fields in the base class Symbol for a symbol defined
// as a constant.

void
Symbol::init_base(const char* name, elfcpp::STT type,
		  elfcpp::STB binding, elfcpp::STV visibility,
		  unsigned char nonvis)
{
  this->init_fields(name, NULL, type, binding, visibility, nonvis);
  this->source_ = CONSTANT;
  this->in_reg_ = true;
}

// Allocate a common symbol in the base.

void
Symbol::allocate_base_common(Output_data* od)
{
  gold_assert(this->is_common());
  this->source_ = IN_OUTPUT_DATA;
  this->u_.in_output_data.output_data = od;
  this->u_.in_output_data.offset_is_from_end = false;
}

// Initialize the fields in Sized_symbol for SYM in OBJECT.

template<int size>
template<bool big_endian>
void
Sized_symbol<size>::init(const char* name, const char* version, Object* object,
			 const elfcpp::Sym<size, big_endian>& sym)
{
  this->init_base(name, version, object, sym);
  this->value_ = sym.get_st_value();
  this->symsize_ = sym.get_st_size();
}

// Initialize the fields in Sized_symbol for a symbol defined in an
// Output_data.

template<int size>
void
Sized_symbol<size>::init(const char* name, Output_data* od,
			 Value_type value, Size_type symsize,
			 elfcpp::STT type, elfcpp::STB binding,
			 elfcpp::STV visibility, unsigned char nonvis,
			 bool offset_is_from_end)
{
  this->init_base(name, od, type, binding, visibility, nonvis,
		  offset_is_from_end);
  this->value_ = value;
  this->symsize_ = symsize;
}

// Initialize the fields in Sized_symbol for a symbol defined in an
// Output_segment.

template<int size>
void
Sized_symbol<size>::init(const char* name, Output_segment* os,
			 Value_type value, Size_type symsize,
			 elfcpp::STT type, elfcpp::STB binding,
			 elfcpp::STV visibility, unsigned char nonvis,
			 Segment_offset_base offset_base)
{
  this->init_base(name, os, type, binding, visibility, nonvis, offset_base);
  this->value_ = value;
  this->symsize_ = symsize;
}

// Initialize the fields in Sized_symbol for a symbol defined as a
// constant.

template<int size>
void
Sized_symbol<size>::init(const char* name, Value_type value, Size_type symsize,
			 elfcpp::STT type, elfcpp::STB binding,
			 elfcpp::STV visibility, unsigned char nonvis)
{
  this->init_base(name, type, binding, visibility, nonvis);
  this->value_ = value;
  this->symsize_ = symsize;
}

// Allocate a common symbol.

template<int size>
void
Sized_symbol<size>::allocate_common(Output_data* od, Value_type value)
{
  this->allocate_base_common(od);
  this->value_ = value;
}

// Return true if this symbol should be added to the dynamic symbol
// table.

inline bool
Symbol::should_add_dynsym_entry() const
{
  // If the symbol is used by a dynamic relocation, we need to add it.
  if (this->needs_dynsym_entry())
    return true;

  // If the symbol was forced local in a version script, do not add it.
  if (this->is_forced_local())
    return false;

  // If exporting all symbols or building a shared library,
  // and the symbol is defined in a regular object and is
  // externally visible, we need to add it.
  if ((parameters->export_dynamic() || parameters->output_is_shared())
      && !this->is_from_dynobj()
      && this->is_externally_visible())
    return true;

  return false;
}

// Return true if the final value of this symbol is known at link
// time.

bool
Symbol::final_value_is_known() const
{
  // If we are not generating an executable, then no final values are
  // known, since they will change at runtime.
  if (!parameters->output_is_executable())
    return false;

  // If the symbol is not from an object file, then it is defined, and
  // known.
  if (this->source_ != FROM_OBJECT)
    return true;

  // If the symbol is from a dynamic object, then the final value is
  // not known.
  if (this->object()->is_dynamic())
    return false;

  // If the symbol is not undefined (it is defined or common), then
  // the final value is known.
  if (!this->is_undefined())
    return true;

  // If the symbol is undefined, then whether the final value is known
  // depends on whether we are doing a static link.  If we are doing a
  // dynamic link, then the final value could be filled in at runtime.
  // This could reasonably be the case for a weak undefined symbol.
  return parameters->doing_static_link();
}

// Return whether the symbol has an absolute value.

bool
Symbol::value_is_absolute() const
{
  switch (this->source_)
    {
    case FROM_OBJECT:
      return this->u_.from_object.shndx == elfcpp::SHN_ABS;
    case IN_OUTPUT_DATA:
    case IN_OUTPUT_SEGMENT:
      return false;
    case CONSTANT:
      return true;
    default:
      gold_unreachable();
    }
}

// Class Symbol_table.

Symbol_table::Symbol_table(unsigned int count,
                           const Version_script_info& version_script)
  : saw_undefined_(0), offset_(0), table_(count), namepool_(),
    forwarders_(), commons_(), forced_locals_(), warnings_(),
    version_script_(version_script)
{
  namepool_.reserve(count);
}

Symbol_table::~Symbol_table()
{
}

// The hash function.  The key values are Stringpool keys.

inline size_t
Symbol_table::Symbol_table_hash::operator()(const Symbol_table_key& key) const
{
  return key.first ^ key.second;
}

// The symbol table key equality function.  This is called with
// Stringpool keys.

inline bool
Symbol_table::Symbol_table_eq::operator()(const Symbol_table_key& k1,
					  const Symbol_table_key& k2) const
{
  return k1.first == k2.first && k1.second == k2.second;
}

// Make TO a symbol which forwards to FROM.

void
Symbol_table::make_forwarder(Symbol* from, Symbol* to)
{
  gold_assert(from != to);
  gold_assert(!from->is_forwarder() && !to->is_forwarder());
  this->forwarders_[from] = to;
  from->set_forwarder();
}

// Resolve the forwards from FROM, returning the real symbol.

Symbol*
Symbol_table::resolve_forwards(const Symbol* from) const
{
  gold_assert(from->is_forwarder());
  Unordered_map<const Symbol*, Symbol*>::const_iterator p =
    this->forwarders_.find(from);
  gold_assert(p != this->forwarders_.end());
  return p->second;
}

// Look up a symbol by name.

Symbol*
Symbol_table::lookup(const char* name, const char* version) const
{
  Stringpool::Key name_key;
  name = this->namepool_.find(name, &name_key);
  if (name == NULL)
    return NULL;

  Stringpool::Key version_key = 0;
  if (version != NULL)
    {
      version = this->namepool_.find(version, &version_key);
      if (version == NULL)
	return NULL;
    }

  Symbol_table_key key(name_key, version_key);
  Symbol_table::Symbol_table_type::const_iterator p = this->table_.find(key);
  if (p == this->table_.end())
    return NULL;
  return p->second;
}

// Resolve a Symbol with another Symbol.  This is only used in the
// unusual case where there are references to both an unversioned
// symbol and a symbol with a version, and we then discover that that
// version is the default version.  Because this is unusual, we do
// this the slow way, by converting back to an ELF symbol.

template<int size, bool big_endian>
void
Symbol_table::resolve(Sized_symbol<size>* to, const Sized_symbol<size>* from,
		      const char* version ACCEPT_SIZE_ENDIAN)
{
  unsigned char buf[elfcpp::Elf_sizes<size>::sym_size];
  elfcpp::Sym_write<size, big_endian> esym(buf);
  // We don't bother to set the st_name field.
  esym.put_st_value(from->value());
  esym.put_st_size(from->symsize());
  esym.put_st_info(from->binding(), from->type());
  esym.put_st_other(from->visibility(), from->nonvis());
  esym.put_st_shndx(from->shndx());
  this->resolve(to, esym.sym(), esym.sym(), from->object(), version);
  if (from->in_reg())
    to->set_in_reg();
  if (from->in_dyn())
    to->set_in_dyn();
}

// Record that a symbol is forced to be local by a version script.

void
Symbol_table::force_local(Symbol* sym)
{
  if (!sym->is_defined() && !sym->is_common())
    return;
  if (sym->is_forced_local())
    {
      // We already got this one.
      return;
    }
  sym->set_is_forced_local();
  this->forced_locals_.push_back(sym);
}

// Add one symbol from OBJECT to the symbol table.  NAME is symbol
// name and VERSION is the version; both are canonicalized.  DEF is
// whether this is the default version.

// If DEF is true, then this is the definition of a default version of
// a symbol.  That means that any lookup of NAME/NULL and any lookup
// of NAME/VERSION should always return the same symbol.  This is
// obvious for references, but in particular we want to do this for
// definitions: overriding NAME/NULL should also override
// NAME/VERSION.  If we don't do that, it would be very hard to
// override functions in a shared library which uses versioning.

// We implement this by simply making both entries in the hash table
// point to the same Symbol structure.  That is easy enough if this is
// the first time we see NAME/NULL or NAME/VERSION, but it is possible
// that we have seen both already, in which case they will both have
// independent entries in the symbol table.  We can't simply change
// the symbol table entry, because we have pointers to the entries
// attached to the object files.  So we mark the entry attached to the
// object file as a forwarder, and record it in the forwarders_ map.
// Note that entries in the hash table will never be marked as
// forwarders.
//
// SYM and ORIG_SYM are almost always the same.  ORIG_SYM is the
// symbol exactly as it existed in the input file.  SYM is usually
// that as well, but can be modified, for instance if we determine
// it's in a to-be-discarded section.

template<int size, bool big_endian>
Sized_symbol<size>*
Symbol_table::add_from_object(Object* object,
			      const char *name,
			      Stringpool::Key name_key,
			      const char *version,
			      Stringpool::Key version_key,
			      bool def,
			      const elfcpp::Sym<size, big_endian>& sym,
			      const elfcpp::Sym<size, big_endian>& orig_sym)
{
  Symbol* const snull = NULL;
  std::pair<typename Symbol_table_type::iterator, bool> ins =
    this->table_.insert(std::make_pair(std::make_pair(name_key, version_key),
				       snull));

  std::pair<typename Symbol_table_type::iterator, bool> insdef =
    std::make_pair(this->table_.end(), false);
  if (def)
    {
      const Stringpool::Key vnull_key = 0;
      insdef = this->table_.insert(std::make_pair(std::make_pair(name_key,
								 vnull_key),
						  snull));
    }

  // ins.first: an iterator, which is a pointer to a pair.
  // ins.first->first: the key (a pair of name and version).
  // ins.first->second: the value (Symbol*).
  // ins.second: true if new entry was inserted, false if not.

  Sized_symbol<size>* ret;
  bool was_undefined;
  bool was_common;
  if (!ins.second)
    {
      // We already have an entry for NAME/VERSION.
      ret = this->get_sized_symbol SELECT_SIZE_NAME(size) (ins.first->second
                                                           SELECT_SIZE(size));
      gold_assert(ret != NULL);

      was_undefined = ret->is_undefined();
      was_common = ret->is_common();

      this->resolve(ret, sym, orig_sym, object, version);

      if (def)
	{
	  if (insdef.second)
	    {
	      // This is the first time we have seen NAME/NULL.  Make
	      // NAME/NULL point to NAME/VERSION.
	      insdef.first->second = ret;
	    }
	  else if (insdef.first->second != ret
	           && insdef.first->second->is_undefined())
	    {
	      // This is the unfortunate case where we already have
	      // entries for both NAME/VERSION and NAME/NULL.  Note
	      // that we don't want to combine them if the existing
	      // symbol is going to override the new one.  FIXME: We
	      // currently just test is_undefined, but this may not do
	      // the right thing if the existing symbol is from a
	      // shared library and the new one is from a regular
	      // object.

	      const Sized_symbol<size>* sym2;
	      sym2 = this->get_sized_symbol SELECT_SIZE_NAME(size) (
		insdef.first->second
                SELECT_SIZE(size));
	      Symbol_table::resolve SELECT_SIZE_ENDIAN_NAME(size, big_endian) (
		ret, sym2, version SELECT_SIZE_ENDIAN(size, big_endian));
	      this->make_forwarder(insdef.first->second, ret);
	      insdef.first->second = ret;
	    }
	}
    }
  else
    {
      // This is the first time we have seen NAME/VERSION.
      gold_assert(ins.first->second == NULL);

      was_undefined = false;
      was_common = false;

      if (def && !insdef.second)
	{
	  // We already have an entry for NAME/NULL.  If we override
	  // it, then change it to NAME/VERSION.
	  ret = this->get_sized_symbol SELECT_SIZE_NAME(size) (
              insdef.first->second
              SELECT_SIZE(size));
	  this->resolve(ret, sym, orig_sym, object, version);
	  ins.first->second = ret;
	}
      else
	{
	  Sized_target<size, big_endian>* target =
	    object->sized_target SELECT_SIZE_ENDIAN_NAME(size, big_endian) (
		SELECT_SIZE_ENDIAN_ONLY(size, big_endian));
	  if (!target->has_make_symbol())
	    ret = new Sized_symbol<size>();
	  else
	    {
	      ret = target->make_symbol();
	      if (ret == NULL)
		{
		  // This means that we don't want a symbol table
		  // entry after all.
		  if (!def)
		    this->table_.erase(ins.first);
		  else
		    {
		      this->table_.erase(insdef.first);
		      // Inserting insdef invalidated ins.
		      this->table_.erase(std::make_pair(name_key,
							version_key));
		    }
		  return NULL;
		}
	    }

	  ret->init(name, version, object, sym);

	  ins.first->second = ret;
	  if (def)
	    {
	      // This is the first time we have seen NAME/NULL.  Point
	      // it at the new entry for NAME/VERSION.
	      gold_assert(insdef.second);
	      insdef.first->second = ret;
	    }
	}
    }

  // Record every time we see a new undefined symbol, to speed up
  // archive groups.
  if (!was_undefined && ret->is_undefined())
    ++this->saw_undefined_;

  // Keep track of common symbols, to speed up common symbol
  // allocation.
  if (!was_common && ret->is_common())
    this->commons_.push_back(ret);

  ret->set_is_default(def);
  return ret;
}

// Add all the symbols in a relocatable object to the hash table.

template<int size, bool big_endian>
void
Symbol_table::add_from_relobj(
    Sized_relobj<size, big_endian>* relobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    typename Sized_relobj<size, big_endian>::Symbols* sympointers)
{
  gold_assert(size == relobj->target()->get_size());
  gold_assert(size == parameters->get_size());

  const int sym_size = elfcpp::Elf_sizes<size>::sym_size;

  const bool just_symbols = relobj->just_symbols();

  const unsigned char* p = syms;
  for (size_t i = 0; i < count; ++i, p += sym_size)
    {
      elfcpp::Sym<size, big_endian> sym(p);
      elfcpp::Sym<size, big_endian>* psym = &sym;

      unsigned int st_name = psym->get_st_name();
      if (st_name >= sym_name_size)
	{
	  relobj->error(_("bad global symbol name offset %u at %zu"),
			st_name, i);
	  continue;
	}

      const char* name = sym_names + st_name;

      // A symbol defined in a section which we are not including must
      // be treated as an undefined symbol.
      unsigned char symbuf[sym_size];
      elfcpp::Sym<size, big_endian> sym2(symbuf);
      unsigned int st_shndx = psym->get_st_shndx();
      if (st_shndx != elfcpp::SHN_UNDEF
	  && st_shndx < elfcpp::SHN_LORESERVE
	  && !relobj->is_section_included(st_shndx))
	{
	  memcpy(symbuf, p, sym_size);
	  elfcpp::Sym_write<size, big_endian> sw(symbuf);
	  sw.put_st_shndx(elfcpp::SHN_UNDEF);
	  psym = &sym2;
	}

      // In an object file, an '@' in the name separates the symbol
      // name from the version name.  If there are two '@' characters,
      // this is the default version.
      const char* ver = strchr(name, '@');
      int namelen = 0;
      // DEF: is the version default?  LOCAL: is the symbol forced local?
      bool def = false;
      bool local = false;

      if (ver != NULL)
        {
          // The symbol name is of the form foo@VERSION or foo@@VERSION
          namelen = ver - name;
          ++ver;
	  if (*ver == '@')
	    {
	      def = true;
	      ++ver;
	    }
        }
      else if (!version_script_.empty())
        {
          // The symbol name did not have a version, but
          // the version script may assign a version anyway.
          namelen = strlen(name);
          def = true;
          // Check the global: entries from the version script.
          const std::string& version =
              version_script_.get_symbol_version(name);
          if (!version.empty())
            ver = version.c_str();
          // Check the local: entries from the version script
          if (version_script_.symbol_is_local(name))
            local = true;
        }

      if (just_symbols)
	{
	  if (psym != &sym2)
	    memcpy(symbuf, p, sym_size);
	  elfcpp::Sym_write<size, big_endian> sw(symbuf);
	  sw.put_st_shndx(elfcpp::SHN_ABS);
	  if (st_shndx != elfcpp::SHN_UNDEF
	      && st_shndx < elfcpp::SHN_LORESERVE)
	    {
	      // Symbol values in object files are section relative.
	      // This is normally what we want, but since here we are
	      // converting the symbol to absolute we need to add the
	      // section address.  The section address in an object
	      // file is normally zero, but people can use a linker
	      // script to change it.
	      sw.put_st_value(sym2.get_st_value()
			      + relobj->section_address(st_shndx));
	    }
	  psym = &sym2;
	}

      Sized_symbol<size>* res;
      if (ver == NULL)
	{
	  Stringpool::Key name_key;
	  name = this->namepool_.add(name, true, &name_key);
	  res = this->add_from_object(relobj, name, name_key, NULL, 0,
				      false, *psym, sym);
          if (local)
	    this->force_local(res);
	}
      else
	{
	  Stringpool::Key name_key;
	  name = this->namepool_.add_with_length(name, namelen, true,
						 &name_key);
	  Stringpool::Key ver_key;
	  ver = this->namepool_.add(ver, true, &ver_key);

	  res = this->add_from_object(relobj, name, name_key, ver, ver_key,
				      def, *psym, sym);
	}

      (*sympointers)[i] = res;
    }
}

// Add all the symbols in a dynamic object to the hash table.

template<int size, bool big_endian>
void
Symbol_table::add_from_dynobj(
    Sized_dynobj<size, big_endian>* dynobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    const unsigned char* versym,
    size_t versym_size,
    const std::vector<const char*>* version_map)
{
  gold_assert(size == dynobj->target()->get_size());
  gold_assert(size == parameters->get_size());

  if (dynobj->just_symbols())
    {
      gold_error(_("--just-symbols does not make sense with a shared object"));
      return;
    }

  if (versym != NULL && versym_size / 2 < count)
    {
      dynobj->error(_("too few symbol versions"));
      return;
    }

  const int sym_size = elfcpp::Elf_sizes<size>::sym_size;

  // We keep a list of all STT_OBJECT symbols, so that we can resolve
  // weak aliases.  This is necessary because if the dynamic object
  // provides the same variable under two names, one of which is a
  // weak definition, and the regular object refers to the weak
  // definition, we have to put both the weak definition and the
  // strong definition into the dynamic symbol table.  Given a weak
  // definition, the only way that we can find the corresponding
  // strong definition, if any, is to search the symbol table.
  std::vector<Sized_symbol<size>*> object_symbols;

  const unsigned char* p = syms;
  const unsigned char* vs = versym;
  for (size_t i = 0; i < count; ++i, p += sym_size, vs += 2)
    {
      elfcpp::Sym<size, big_endian> sym(p);

      // Ignore symbols with local binding or that have
      // internal or hidden visibility.
      if (sym.get_st_bind() == elfcpp::STB_LOCAL
          || sym.get_st_visibility() == elfcpp::STV_INTERNAL
          || sym.get_st_visibility() == elfcpp::STV_HIDDEN)
	continue;

      unsigned int st_name = sym.get_st_name();
      if (st_name >= sym_name_size)
	{
	  dynobj->error(_("bad symbol name offset %u at %zu"),
			st_name, i);
	  continue;
	}

      const char* name = sym_names + st_name;

      Sized_symbol<size>* res;

      if (versym == NULL)
	{
	  Stringpool::Key name_key;
	  name = this->namepool_.add(name, true, &name_key);
	  res = this->add_from_object(dynobj, name, name_key, NULL, 0,
				      false, sym, sym);
	}
      else
	{
	  // Read the version information.

	  unsigned int v = elfcpp::Swap<16, big_endian>::readval(vs);

	  bool hidden = (v & elfcpp::VERSYM_HIDDEN) != 0;
	  v &= elfcpp::VERSYM_VERSION;

	  // The Sun documentation says that V can be VER_NDX_LOCAL,
	  // or VER_NDX_GLOBAL, or a version index.  The meaning of
	  // VER_NDX_LOCAL is defined as "Symbol has local scope."
	  // The old GNU linker will happily generate VER_NDX_LOCAL
	  // for an undefined symbol.  I don't know what the Sun
	  // linker will generate.

	  if (v == static_cast<unsigned int>(elfcpp::VER_NDX_LOCAL)
	      && sym.get_st_shndx() != elfcpp::SHN_UNDEF)
	    {
	      // This symbol should not be visible outside the object.
	      continue;
	    }

	  // At this point we are definitely going to add this symbol.
	  Stringpool::Key name_key;
	  name = this->namepool_.add(name, true, &name_key);

	  if (v == static_cast<unsigned int>(elfcpp::VER_NDX_LOCAL)
	      || v == static_cast<unsigned int>(elfcpp::VER_NDX_GLOBAL))
	    {
	      // This symbol does not have a version.
	      res = this->add_from_object(dynobj, name, name_key, NULL, 0,
					  false, sym, sym);
	    }
	  else
	    {
	      if (v >= version_map->size())
		{
		  dynobj->error(_("versym for symbol %zu out of range: %u"),
				i, v);
		  continue;
		}

	      const char* version = (*version_map)[v];
	      if (version == NULL)
		{
		  dynobj->error(_("versym for symbol %zu has no name: %u"),
				i, v);
		  continue;
		}

	      Stringpool::Key version_key;
	      version = this->namepool_.add(version, true, &version_key);

	      // If this is an absolute symbol, and the version name
	      // and symbol name are the same, then this is the
	      // version definition symbol.  These symbols exist to
	      // support using -u to pull in particular versions.  We
	      // do not want to record a version for them.
	      if (sym.get_st_shndx() == elfcpp::SHN_ABS
		  && name_key == version_key)
		res = this->add_from_object(dynobj, name, name_key, NULL, 0,
					    false, sym, sym);
	      else
		{
		  const bool def = (!hidden
				    && (sym.get_st_shndx()
					!= elfcpp::SHN_UNDEF));
		  res = this->add_from_object(dynobj, name, name_key, version,
					      version_key, def, sym, sym);
		}
	    }
	}

      if (sym.get_st_shndx() != elfcpp::SHN_UNDEF
	  && sym.get_st_type() == elfcpp::STT_OBJECT)
	object_symbols.push_back(res);
    }

  this->record_weak_aliases(&object_symbols);
}

// This is used to sort weak aliases.  We sort them first by section
// index, then by offset, then by weak ahead of strong.

template<int size>
class Weak_alias_sorter
{
 public:
  bool operator()(const Sized_symbol<size>*, const Sized_symbol<size>*) const;
};

template<int size>
bool
Weak_alias_sorter<size>::operator()(const Sized_symbol<size>* s1,
				    const Sized_symbol<size>* s2) const
{
  if (s1->shndx() != s2->shndx())
    return s1->shndx() < s2->shndx();
  if (s1->value() != s2->value())
    return s1->value() < s2->value();
  if (s1->binding() != s2->binding())
    {
      if (s1->binding() == elfcpp::STB_WEAK)
	return true;
      if (s2->binding() == elfcpp::STB_WEAK)
	return false;
    }
  return std::string(s1->name()) < std::string(s2->name());
}

// SYMBOLS is a list of object symbols from a dynamic object.  Look
// for any weak aliases, and record them so that if we add the weak
// alias to the dynamic symbol table, we also add the corresponding
// strong symbol.

template<int size>
void
Symbol_table::record_weak_aliases(std::vector<Sized_symbol<size>*>* symbols)
{
  // Sort the vector by section index, then by offset, then by weak
  // ahead of strong.
  std::sort(symbols->begin(), symbols->end(), Weak_alias_sorter<size>());

  // Walk through the vector.  For each weak definition, record
  // aliases.
  for (typename std::vector<Sized_symbol<size>*>::const_iterator p =
	 symbols->begin();
       p != symbols->end();
       ++p)
    {
      if ((*p)->binding() != elfcpp::STB_WEAK)
	continue;

      // Build a circular list of weak aliases.  Each symbol points to
      // the next one in the circular list.

      Sized_symbol<size>* from_sym = *p;
      typename std::vector<Sized_symbol<size>*>::const_iterator q;
      for (q = p + 1; q != symbols->end(); ++q)
	{
	  if ((*q)->shndx() != from_sym->shndx()
	      || (*q)->value() != from_sym->value())
	    break;

	  this->weak_aliases_[from_sym] = *q;
	  from_sym->set_has_alias();
	  from_sym = *q;
	}

      if (from_sym != *p)
	{
	  this->weak_aliases_[from_sym] = *p;
	  from_sym->set_has_alias();
	}

      p = q - 1;
    }
}

// Create and return a specially defined symbol.  If ONLY_IF_REF is
// true, then only create the symbol if there is a reference to it.
// If this does not return NULL, it sets *POLDSYM to the existing
// symbol if there is one.  This canonicalizes *PNAME and *PVERSION.

template<int size, bool big_endian>
Sized_symbol<size>*
Symbol_table::define_special_symbol(const char** pname, const char** pversion,
				    bool only_if_ref,
                                    Sized_symbol<size>** poldsym
                                    ACCEPT_SIZE_ENDIAN)
{
  Symbol* oldsym;
  Sized_symbol<size>* sym;
  bool add_to_table = false;
  typename Symbol_table_type::iterator add_loc = this->table_.end();

  // If the caller didn't give us a version, see if we get one from
  // the version script.
  if (*pversion == NULL)
    {
      const std::string& v(this->version_script_.get_symbol_version(*pname));
      if (!v.empty())
	*pversion = v.c_str();
    }

  if (only_if_ref)
    {
      oldsym = this->lookup(*pname, *pversion);
      if (oldsym == NULL || !oldsym->is_undefined())
	return NULL;

      *pname = oldsym->name();
      *pversion = oldsym->version();
    }
  else
    {
      // Canonicalize NAME and VERSION.
      Stringpool::Key name_key;
      *pname = this->namepool_.add(*pname, true, &name_key);

      Stringpool::Key version_key = 0;
      if (*pversion != NULL)
	*pversion = this->namepool_.add(*pversion, true, &version_key);

      Symbol* const snull = NULL;
      std::pair<typename Symbol_table_type::iterator, bool> ins =
	this->table_.insert(std::make_pair(std::make_pair(name_key,
							  version_key),
					   snull));

      if (!ins.second)
	{
	  // We already have a symbol table entry for NAME/VERSION.
	  oldsym = ins.first->second;
	  gold_assert(oldsym != NULL);
	}
      else
	{
	  // We haven't seen this symbol before.
	  gold_assert(ins.first->second == NULL);
          add_to_table = true;
          add_loc = ins.first;
	  oldsym = NULL;
	}
    }

  const Target* target = parameters->target();
  if (!target->has_make_symbol())
    sym = new Sized_symbol<size>();
  else
    {
      gold_assert(target->get_size() == size);
      gold_assert(target->is_big_endian() ? big_endian : !big_endian);
      typedef Sized_target<size, big_endian> My_target;
      const My_target* sized_target =
          static_cast<const My_target*>(target);
      sym = sized_target->make_symbol();
      if (sym == NULL)
        return NULL;
    }

  if (add_to_table)
    add_loc->second = sym;
  else
    gold_assert(oldsym != NULL);

  *poldsym = this->get_sized_symbol SELECT_SIZE_NAME(size) (oldsym
                                                            SELECT_SIZE(size));

  return sym;
}

// Define a symbol based on an Output_data.

Symbol*
Symbol_table::define_in_output_data(const char* name,
				    const char* version,
				    Output_data* od,
				    uint64_t value,
				    uint64_t symsize,
				    elfcpp::STT type,
				    elfcpp::STB binding,
				    elfcpp::STV visibility,
				    unsigned char nonvis,
				    bool offset_is_from_end,
				    bool only_if_ref)
{
  if (parameters->get_size() == 32)
    {
#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_32_BIG)
      return this->do_define_in_output_data<32>(name, version, od,
                                                value, symsize, type, binding,
                                                visibility, nonvis,
                                                offset_is_from_end,
                                                only_if_ref);
#else
      gold_unreachable();
#endif
    }
  else if (parameters->get_size() == 64)
    {
#if defined(HAVE_TARGET_64_LITTLE) || defined(HAVE_TARGET_64_BIG)
      return this->do_define_in_output_data<64>(name, version, od,
                                                value, symsize, type, binding,
                                                visibility, nonvis,
                                                offset_is_from_end,
                                                only_if_ref);
#else
      gold_unreachable();
#endif
    }
  else
    gold_unreachable();
}

// Define a symbol in an Output_data, sized version.

template<int size>
Sized_symbol<size>*
Symbol_table::do_define_in_output_data(
    const char* name,
    const char* version,
    Output_data* od,
    typename elfcpp::Elf_types<size>::Elf_Addr value,
    typename elfcpp::Elf_types<size>::Elf_WXword symsize,
    elfcpp::STT type,
    elfcpp::STB binding,
    elfcpp::STV visibility,
    unsigned char nonvis,
    bool offset_is_from_end,
    bool only_if_ref)
{
  Sized_symbol<size>* sym;
  Sized_symbol<size>* oldsym;

  if (parameters->is_big_endian())
    {
#if defined(HAVE_TARGET_32_BIG) || defined(HAVE_TARGET_64_BIG)
      sym = this->define_special_symbol SELECT_SIZE_ENDIAN_NAME(size, true) (
          &name, &version, only_if_ref, &oldsym
          SELECT_SIZE_ENDIAN(size, true));
#else
      gold_unreachable();
#endif
    }
  else
    {
#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_64_LITTLE)
      sym = this->define_special_symbol SELECT_SIZE_ENDIAN_NAME(size, false) (
          &name, &version, only_if_ref, &oldsym
          SELECT_SIZE_ENDIAN(size, false));
#else
      gold_unreachable();
#endif
    }

  if (sym == NULL)
    return NULL;

  gold_assert(version == NULL || oldsym != NULL);
  sym->init(name, od, value, symsize, type, binding, visibility, nonvis,
	    offset_is_from_end);

  if (oldsym == NULL)
    {
      if (binding == elfcpp::STB_LOCAL
	  || this->version_script_.symbol_is_local(name))
	this->force_local(sym);
      return sym;
    }

  if (Symbol_table::should_override_with_special(oldsym))
    this->override_with_special(oldsym, sym);
  delete sym;
  return oldsym;
}

// Define a symbol based on an Output_segment.

Symbol*
Symbol_table::define_in_output_segment(const char* name,
				       const char* version, Output_segment* os,
				       uint64_t value,
				       uint64_t symsize,
				       elfcpp::STT type,
				       elfcpp::STB binding,
				       elfcpp::STV visibility,
				       unsigned char nonvis,
				       Symbol::Segment_offset_base offset_base,
				       bool only_if_ref)
{
  if (parameters->get_size() == 32)
    {
#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_32_BIG)
      return this->do_define_in_output_segment<32>(name, version, os,
                                                   value, symsize, type,
                                                   binding, visibility, nonvis,
                                                   offset_base, only_if_ref);
#else
      gold_unreachable();
#endif
    }
  else if (parameters->get_size() == 64)
    {
#if defined(HAVE_TARGET_64_LITTLE) || defined(HAVE_TARGET_64_BIG)
      return this->do_define_in_output_segment<64>(name, version, os,
                                                   value, symsize, type,
                                                   binding, visibility, nonvis,
                                                   offset_base, only_if_ref);
#else
      gold_unreachable();
#endif
    }
  else
    gold_unreachable();
}

// Define a symbol in an Output_segment, sized version.

template<int size>
Sized_symbol<size>*
Symbol_table::do_define_in_output_segment(
    const char* name,
    const char* version,
    Output_segment* os,
    typename elfcpp::Elf_types<size>::Elf_Addr value,
    typename elfcpp::Elf_types<size>::Elf_WXword symsize,
    elfcpp::STT type,
    elfcpp::STB binding,
    elfcpp::STV visibility,
    unsigned char nonvis,
    Symbol::Segment_offset_base offset_base,
    bool only_if_ref)
{
  Sized_symbol<size>* sym;
  Sized_symbol<size>* oldsym;

  if (parameters->is_big_endian())
    {
#if defined(HAVE_TARGET_32_BIG) || defined(HAVE_TARGET_64_BIG)
      sym = this->define_special_symbol SELECT_SIZE_ENDIAN_NAME(size, true) (
          &name, &version, only_if_ref, &oldsym
          SELECT_SIZE_ENDIAN(size, true));
#else
      gold_unreachable();
#endif
    }
  else
    {
#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_64_LITTLE)
      sym = this->define_special_symbol SELECT_SIZE_ENDIAN_NAME(size, false) (
          &name, &version, only_if_ref, &oldsym
          SELECT_SIZE_ENDIAN(size, false));
#else
      gold_unreachable();
#endif
    }

  if (sym == NULL)
    return NULL;

  gold_assert(version == NULL || oldsym != NULL);
  sym->init(name, os, value, symsize, type, binding, visibility, nonvis,
	    offset_base);

  if (oldsym == NULL)
    {
      if (binding == elfcpp::STB_LOCAL
	  || this->version_script_.symbol_is_local(name))
	this->force_local(sym);
      return sym;
    }

  if (Symbol_table::should_override_with_special(oldsym))
    this->override_with_special(oldsym, sym);
  delete sym;
  return oldsym;
}

// Define a special symbol with a constant value.  It is a multiple
// definition error if this symbol is already defined.

Symbol*
Symbol_table::define_as_constant(const char* name,
				 const char* version,
				 uint64_t value,
				 uint64_t symsize,
				 elfcpp::STT type,
				 elfcpp::STB binding,
				 elfcpp::STV visibility,
				 unsigned char nonvis,
				 bool only_if_ref)
{
  if (parameters->get_size() == 32)
    {
#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_32_BIG)
      return this->do_define_as_constant<32>(name, version, value,
                                             symsize, type, binding,
                                             visibility, nonvis, only_if_ref);
#else
      gold_unreachable();
#endif
    }
  else if (parameters->get_size() == 64)
    {
#if defined(HAVE_TARGET_64_LITTLE) || defined(HAVE_TARGET_64_BIG)
      return this->do_define_as_constant<64>(name, version, value,
                                             symsize, type, binding,
                                             visibility, nonvis, only_if_ref);
#else
      gold_unreachable();
#endif
    }
  else
    gold_unreachable();
}

// Define a symbol as a constant, sized version.

template<int size>
Sized_symbol<size>*
Symbol_table::do_define_as_constant(
    const char* name,
    const char* version,
    typename elfcpp::Elf_types<size>::Elf_Addr value,
    typename elfcpp::Elf_types<size>::Elf_WXword symsize,
    elfcpp::STT type,
    elfcpp::STB binding,
    elfcpp::STV visibility,
    unsigned char nonvis,
    bool only_if_ref)
{
  Sized_symbol<size>* sym;
  Sized_symbol<size>* oldsym;

  if (parameters->is_big_endian())
    {
#if defined(HAVE_TARGET_32_BIG) || defined(HAVE_TARGET_64_BIG)
      sym = this->define_special_symbol SELECT_SIZE_ENDIAN_NAME(size, true) (
          &name, &version, only_if_ref, &oldsym
          SELECT_SIZE_ENDIAN(size, true));
#else
      gold_unreachable();
#endif
    }
  else
    {
#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_64_LITTLE)
      sym = this->define_special_symbol SELECT_SIZE_ENDIAN_NAME(size, false) (
          &name, &version, only_if_ref, &oldsym
          SELECT_SIZE_ENDIAN(size, false));
#else
      gold_unreachable();
#endif
    }

  if (sym == NULL)
    return NULL;

  gold_assert(version == NULL || version == name || oldsym != NULL);
  sym->init(name, value, symsize, type, binding, visibility, nonvis);

  if (oldsym == NULL)
    {
      if (binding == elfcpp::STB_LOCAL
	  || this->version_script_.symbol_is_local(name))
	this->force_local(sym);
      return sym;
    }

  if (Symbol_table::should_override_with_special(oldsym))
    this->override_with_special(oldsym, sym);
  delete sym;
  return oldsym;
}

// Define a set of symbols in output sections.

void
Symbol_table::define_symbols(const Layout* layout, int count,
			     const Define_symbol_in_section* p,
			     bool only_if_ref)
{
  for (int i = 0; i < count; ++i, ++p)
    {
      Output_section* os = layout->find_output_section(p->output_section);
      if (os != NULL)
	this->define_in_output_data(p->name, NULL, os, p->value,
				    p->size, p->type, p->binding,
				    p->visibility, p->nonvis,
				    p->offset_is_from_end,
				    only_if_ref || p->only_if_ref);
      else
	this->define_as_constant(p->name, NULL, 0, p->size, p->type,
				 p->binding, p->visibility, p->nonvis,
				 only_if_ref || p->only_if_ref);
    }
}

// Define a set of symbols in output segments.

void
Symbol_table::define_symbols(const Layout* layout, int count,
			     const Define_symbol_in_segment* p,
			     bool only_if_ref)
{
  for (int i = 0; i < count; ++i, ++p)
    {
      Output_segment* os = layout->find_output_segment(p->segment_type,
						       p->segment_flags_set,
						       p->segment_flags_clear);
      if (os != NULL)
	this->define_in_output_segment(p->name, NULL, os, p->value,
				       p->size, p->type, p->binding,
				       p->visibility, p->nonvis,
				       p->offset_base,
				       only_if_ref || p->only_if_ref);
      else
	this->define_as_constant(p->name, NULL, 0, p->size, p->type,
				 p->binding, p->visibility, p->nonvis,
				 only_if_ref || p->only_if_ref);
    }
}

// Define CSYM using a COPY reloc.  POSD is the Output_data where the
// symbol should be defined--typically a .dyn.bss section.  VALUE is
// the offset within POSD.

template<int size>
void
Symbol_table::define_with_copy_reloc(
    Sized_symbol<size>* csym,
    Output_data* posd,
    typename elfcpp::Elf_types<size>::Elf_Addr value)
{
  gold_assert(csym->is_from_dynobj());
  gold_assert(!csym->is_copied_from_dynobj());
  Object* object = csym->object();
  gold_assert(object->is_dynamic());
  Dynobj* dynobj = static_cast<Dynobj*>(object);

  // Our copied variable has to override any variable in a shared
  // library.
  elfcpp::STB binding = csym->binding();
  if (binding == elfcpp::STB_WEAK)
    binding = elfcpp::STB_GLOBAL;

  this->define_in_output_data(csym->name(), csym->version(),
			      posd, value, csym->symsize(),
			      csym->type(), binding,
			      csym->visibility(), csym->nonvis(),
			      false, false);

  csym->set_is_copied_from_dynobj();
  csym->set_needs_dynsym_entry();

  this->copied_symbol_dynobjs_[csym] = dynobj;

  // We have now defined all aliases, but we have not entered them all
  // in the copied_symbol_dynobjs_ map.
  if (csym->has_alias())
    {
      Symbol* sym = csym;
      while (true)
	{
	  sym = this->weak_aliases_[sym];
	  if (sym == csym)
	    break;
	  gold_assert(sym->output_data() == posd);

	  sym->set_is_copied_from_dynobj();
	  this->copied_symbol_dynobjs_[sym] = dynobj;
	}
    }
}

// SYM is defined using a COPY reloc.  Return the dynamic object where
// the original definition was found.

Dynobj*
Symbol_table::get_copy_source(const Symbol* sym) const
{
  gold_assert(sym->is_copied_from_dynobj());
  Copied_symbol_dynobjs::const_iterator p =
    this->copied_symbol_dynobjs_.find(sym);
  gold_assert(p != this->copied_symbol_dynobjs_.end());
  return p->second;
}

// Set the dynamic symbol indexes.  INDEX is the index of the first
// global dynamic symbol.  Pointers to the symbols are stored into the
// vector SYMS.  The names are added to DYNPOOL.  This returns an
// updated dynamic symbol index.

unsigned int
Symbol_table::set_dynsym_indexes(unsigned int index,
				 std::vector<Symbol*>* syms,
				 Stringpool* dynpool,
				 Versions* versions)
{
  for (Symbol_table_type::iterator p = this->table_.begin();
       p != this->table_.end();
       ++p)
    {
      Symbol* sym = p->second;

      // Note that SYM may already have a dynamic symbol index, since
      // some symbols appear more than once in the symbol table, with
      // and without a version.

      if (!sym->should_add_dynsym_entry())
	sym->set_dynsym_index(-1U);
      else if (!sym->has_dynsym_index())
	{
	  sym->set_dynsym_index(index);
	  ++index;
	  syms->push_back(sym);
	  dynpool->add(sym->name(), false, NULL);

	  // Record any version information.
          if (sym->version() != NULL)
            versions->record_version(this, dynpool, sym);
	}
    }

  // Finish up the versions.  In some cases this may add new dynamic
  // symbols.
  index = versions->finalize(this, index, syms);

  return index;
}

// Set the final values for all the symbols.  The index of the first
// global symbol in the output file is *PLOCAL_SYMCOUNT.  Record the
// file offset OFF.  Add their names to POOL.  Return the new file
// offset.  Update *PLOCAL_SYMCOUNT if necessary.

off_t
Symbol_table::finalize(off_t off, off_t dynoff, size_t dyn_global_index,
		       size_t dyncount, Stringpool* pool,
		       unsigned int *plocal_symcount)
{
  off_t ret;

  gold_assert(*plocal_symcount != 0);
  this->first_global_index_ = *plocal_symcount;

  this->dynamic_offset_ = dynoff;
  this->first_dynamic_global_index_ = dyn_global_index;
  this->dynamic_count_ = dyncount;

  if (parameters->get_size() == 32)
    {
#if defined(HAVE_TARGET_32_BIG) || defined(HAVE_TARGET_32_LITTLE)
      ret = this->sized_finalize<32>(off, pool, plocal_symcount);
#else
      gold_unreachable();
#endif
    }
  else if (parameters->get_size() == 64)
    {
#if defined(HAVE_TARGET_64_BIG) || defined(HAVE_TARGET_64_LITTLE)
      ret = this->sized_finalize<64>(off, pool, plocal_symcount);
#else
      gold_unreachable();
#endif
    }
  else
    gold_unreachable();

  // Now that we have the final symbol table, we can reliably note
  // which symbols should get warnings.
  this->warnings_.note_warnings(this);

  return ret;
}

// SYM is going into the symbol table at *PINDEX.  Add the name to
// POOL, update *PINDEX and *POFF.

template<int size>
void
Symbol_table::add_to_final_symtab(Symbol* sym, Stringpool* pool,
				  unsigned int* pindex, off_t* poff)
{
  sym->set_symtab_index(*pindex);
  pool->add(sym->name(), false, NULL);
  ++*pindex;
  *poff += elfcpp::Elf_sizes<size>::sym_size;
}

// Set the final value for all the symbols.  This is called after
// Layout::finalize, so all the output sections have their final
// address.

template<int size>
off_t
Symbol_table::sized_finalize(off_t off, Stringpool* pool,
			     unsigned int* plocal_symcount)
{
  off = align_address(off, size >> 3);
  this->offset_ = off;

  unsigned int index = *plocal_symcount;
  const unsigned int orig_index = index;

  // First do all the symbols which have been forced to be local, as
  // they must appear before all global symbols.
  for (Forced_locals::iterator p = this->forced_locals_.begin();
       p != this->forced_locals_.end();
       ++p)
    {
      Symbol* sym = *p;
      gold_assert(sym->is_forced_local());
      if (this->sized_finalize_symbol<size>(sym))
	{
	  this->add_to_final_symtab<size>(sym, pool, &index, &off);
	  ++*plocal_symcount;
	}
    }

  // Now do all the remaining symbols.
  for (Symbol_table_type::iterator p = this->table_.begin();
       p != this->table_.end();
       ++p)
    {
      Symbol* sym = p->second;
      if (this->sized_finalize_symbol<size>(sym))
	this->add_to_final_symtab<size>(sym, pool, &index, &off);
    }

  this->output_count_ = index - orig_index;

  return off;
}

// Finalize the symbol SYM.  This returns true if the symbol should be
// added to the symbol table, false otherwise.

template<int size>
bool
Symbol_table::sized_finalize_symbol(Symbol* unsized_sym)
{
  Sized_symbol<size>* sym = static_cast<Sized_symbol<size>*>(unsized_sym);

  // The default version of a symbol may appear twice in the symbol
  // table.  We only need to finalize it once.
  if (sym->has_symtab_index())
    return false;

  if (!sym->in_reg())
    {
      gold_assert(!sym->has_symtab_index());
      sym->set_symtab_index(-1U);
      gold_assert(sym->dynsym_index() == -1U);
      return false;
    }

  typename Sized_symbol<size>::Value_type value;

  switch (sym->source())
    {
    case Symbol::FROM_OBJECT:
      {
	unsigned int shndx = sym->shndx();

	// FIXME: We need some target specific support here.
	if (shndx >= elfcpp::SHN_LORESERVE
	    && shndx != elfcpp::SHN_ABS)
	  {
	    gold_error(_("%s: unsupported symbol section 0x%x"),
		       sym->demangled_name().c_str(), shndx);
	    shndx = elfcpp::SHN_UNDEF;
	  }

	Object* symobj = sym->object();
	if (symobj->is_dynamic())
	  {
	    value = 0;
	    shndx = elfcpp::SHN_UNDEF;
	  }
	else if (shndx == elfcpp::SHN_UNDEF)
	  value = 0;
	else if (shndx == elfcpp::SHN_ABS)
	  value = sym->value();
	else
	  {
	    Relobj* relobj = static_cast<Relobj*>(symobj);
	    section_offset_type secoff;
	    Output_section* os = relobj->output_section(shndx, &secoff);

	    if (os == NULL)
	      {
		sym->set_symtab_index(-1U);
		gold_assert(sym->dynsym_index() == -1U);
		return false;
	      }

	    if (sym->type() == elfcpp::STT_TLS)
	      value = sym->value() + os->tls_offset() + secoff;
	    else
	      value = sym->value() + os->address() + secoff;
	  }
      }
      break;

    case Symbol::IN_OUTPUT_DATA:
      {
	Output_data* od = sym->output_data();
	value = sym->value() + od->address();
	if (sym->offset_is_from_end())
	  value += od->data_size();
      }
      break;

    case Symbol::IN_OUTPUT_SEGMENT:
      {
	Output_segment* os = sym->output_segment();
	value = sym->value() + os->vaddr();
	switch (sym->offset_base())
	  {
	  case Symbol::SEGMENT_START:
	    break;
	  case Symbol::SEGMENT_END:
	    value += os->memsz();
	    break;
	  case Symbol::SEGMENT_BSS:
	    value += os->filesz();
	    break;
	  default:
	    gold_unreachable();
	  }
      }
      break;

    case Symbol::CONSTANT:
      value = sym->value();
      break;

    default:
      gold_unreachable();
    }

  sym->set_value(value);

  if (parameters->strip_all())
    {
      sym->set_symtab_index(-1U);
      return false;
    }

  return true;
}

// Write out the global symbols.

void
Symbol_table::write_globals(const Input_objects* input_objects,
			    const Stringpool* sympool,
			    const Stringpool* dynpool, Output_file* of) const
{
  if (parameters->get_size() == 32)
    {
      if (parameters->is_big_endian())
	{
#ifdef HAVE_TARGET_32_BIG
	  this->sized_write_globals<32, true>(input_objects, sympool,
					      dynpool, of);
#else
	  gold_unreachable();
#endif
	}
      else
	{
#ifdef HAVE_TARGET_32_LITTLE
	  this->sized_write_globals<32, false>(input_objects, sympool,
					       dynpool, of);
#else
	  gold_unreachable();
#endif
	}
    }
  else if (parameters->get_size() == 64)
    {
      if (parameters->is_big_endian())
	{
#ifdef HAVE_TARGET_64_BIG
	  this->sized_write_globals<64, true>(input_objects, sympool,
					      dynpool, of);
#else
	  gold_unreachable();
#endif
	}
      else
	{
#ifdef HAVE_TARGET_64_LITTLE
	  this->sized_write_globals<64, false>(input_objects, sympool,
					       dynpool, of);
#else
	  gold_unreachable();
#endif
	}
    }
  else
    gold_unreachable();
}

// Write out the global symbols.

template<int size, bool big_endian>
void
Symbol_table::sized_write_globals(const Input_objects* input_objects,
				  const Stringpool* sympool,
				  const Stringpool* dynpool,
				  Output_file* of) const
{
  const Target* const target = parameters->target();

  const int sym_size = elfcpp::Elf_sizes<size>::sym_size;

  const unsigned int output_count = this->output_count_;
  const section_size_type oview_size = output_count * sym_size;
  const unsigned int first_global_index = this->first_global_index_;
  unsigned char* const psyms = of->get_output_view(this->offset_, oview_size);

  const unsigned int dynamic_count = this->dynamic_count_;
  const section_size_type dynamic_size = dynamic_count * sym_size;
  const unsigned int first_dynamic_global_index =
    this->first_dynamic_global_index_;
  unsigned char* dynamic_view;
  if (this->dynamic_offset_ == 0)
    dynamic_view = NULL;
  else
    dynamic_view = of->get_output_view(this->dynamic_offset_, dynamic_size);

  for (Symbol_table_type::const_iterator p = this->table_.begin();
       p != this->table_.end();
       ++p)
    {
      Sized_symbol<size>* sym = static_cast<Sized_symbol<size>*>(p->second);

      // Possibly warn about unresolved symbols in shared libraries.
      this->warn_about_undefined_dynobj_symbol(input_objects, sym);

      unsigned int sym_index = sym->symtab_index();
      unsigned int dynsym_index;
      if (dynamic_view == NULL)
	dynsym_index = -1U;
      else
	dynsym_index = sym->dynsym_index();

      if (sym_index == -1U && dynsym_index == -1U)
	{
	  // This symbol is not included in the output file.
	  continue;
	}

      unsigned int shndx;
      typename elfcpp::Elf_types<size>::Elf_Addr sym_value = sym->value();
      typename elfcpp::Elf_types<size>::Elf_Addr dynsym_value = sym_value;
      switch (sym->source())
	{
	case Symbol::FROM_OBJECT:
	  {
	    unsigned int in_shndx = sym->shndx();

	    // FIXME: We need some target specific support here.
	    if (in_shndx >= elfcpp::SHN_LORESERVE
		&& in_shndx != elfcpp::SHN_ABS)
	      {
		gold_error(_("%s: unsupported symbol section 0x%x"),
			   sym->demangled_name().c_str(), in_shndx);
		shndx = in_shndx;
	      }
	    else
	      {
		Object* symobj = sym->object();
		if (symobj->is_dynamic())
		  {
		    if (sym->needs_dynsym_value())
		      dynsym_value = target->dynsym_value(sym);
		    shndx = elfcpp::SHN_UNDEF;
		  }
		else if (in_shndx == elfcpp::SHN_UNDEF
			 || in_shndx == elfcpp::SHN_ABS)
		  shndx = in_shndx;
		else
		  {
		    Relobj* relobj = static_cast<Relobj*>(symobj);
		    section_offset_type secoff;
		    Output_section* os = relobj->output_section(in_shndx,
								&secoff);
		    gold_assert(os != NULL);
		    shndx = os->out_shndx();

		    // In object files symbol values are section
		    // relative.
		    if (parameters->output_is_object())
		      sym_value -= os->address();
		  }
	      }
	  }
	  break;

	case Symbol::IN_OUTPUT_DATA:
	  shndx = sym->output_data()->out_shndx();
	  break;

	case Symbol::IN_OUTPUT_SEGMENT:
	  shndx = elfcpp::SHN_ABS;
	  break;

	case Symbol::CONSTANT:
	  shndx = elfcpp::SHN_ABS;
	  break;

	default:
	  gold_unreachable();
	}

      if (sym_index != -1U)
	{
	  sym_index -= first_global_index;
	  gold_assert(sym_index < output_count);
	  unsigned char* ps = psyms + (sym_index * sym_size);
	  this->sized_write_symbol SELECT_SIZE_ENDIAN_NAME(size, big_endian) (
	      sym, sym_value, shndx, sympool, ps
              SELECT_SIZE_ENDIAN(size, big_endian));
	}

      if (dynsym_index != -1U)
	{
	  dynsym_index -= first_dynamic_global_index;
	  gold_assert(dynsym_index < dynamic_count);
	  unsigned char* pd = dynamic_view + (dynsym_index * sym_size);
	  this->sized_write_symbol SELECT_SIZE_ENDIAN_NAME(size, big_endian) (
	      sym, dynsym_value, shndx, dynpool, pd
              SELECT_SIZE_ENDIAN(size, big_endian));
	}
    }

  of->write_output_view(this->offset_, oview_size, psyms);
  if (dynamic_view != NULL)
    of->write_output_view(this->dynamic_offset_, dynamic_size, dynamic_view);
}

// Write out the symbol SYM, in section SHNDX, to P.  POOL is the
// strtab holding the name.

template<int size, bool big_endian>
void
Symbol_table::sized_write_symbol(
    Sized_symbol<size>* sym,
    typename elfcpp::Elf_types<size>::Elf_Addr value,
    unsigned int shndx,
    const Stringpool* pool,
    unsigned char* p
    ACCEPT_SIZE_ENDIAN) const
{
  elfcpp::Sym_write<size, big_endian> osym(p);
  osym.put_st_name(pool->get_offset(sym->name()));
  osym.put_st_value(value);
  osym.put_st_size(sym->symsize());
  // A version script may have overridden the default binding.
  if (sym->is_forced_local())
    osym.put_st_info(elfcpp::elf_st_info(elfcpp::STB_LOCAL, sym->type()));
  else
    osym.put_st_info(elfcpp::elf_st_info(sym->binding(), sym->type()));
  osym.put_st_other(elfcpp::elf_st_other(sym->visibility(), sym->nonvis()));
  osym.put_st_shndx(shndx);
}

// Check for unresolved symbols in shared libraries.  This is
// controlled by the --allow-shlib-undefined option.

// We only warn about libraries for which we have seen all the
// DT_NEEDED entries.  We don't try to track down DT_NEEDED entries
// which were not seen in this link.  If we didn't see a DT_NEEDED
// entry, we aren't going to be able to reliably report whether the
// symbol is undefined.

// We also don't warn about libraries found in the system library
// directory (the directory were we find libc.so); we assume that
// those libraries are OK.  This heuristic avoids problems in
// GNU/Linux, in which -ldl can have undefined references satisfied by
// ld-linux.so.

inline void
Symbol_table::warn_about_undefined_dynobj_symbol(
    const Input_objects* input_objects,
    Symbol* sym) const
{
  if (sym->source() == Symbol::FROM_OBJECT
      && sym->object()->is_dynamic()
      && sym->shndx() == elfcpp::SHN_UNDEF
      && sym->binding() != elfcpp::STB_WEAK
      && !parameters->allow_shlib_undefined()
      && !parameters->target()->is_defined_by_abi(sym)
      && !input_objects->found_in_system_library_directory(sym->object()))
    {
      // A very ugly cast.
      Dynobj* dynobj = static_cast<Dynobj*>(sym->object());
      if (!dynobj->has_unknown_needed_entries())
	gold_error(_("%s: undefined reference to '%s'"),
		   sym->object()->name().c_str(),
                   sym->demangled_name().c_str());
    }
}

// Write out a section symbol.  Return the update offset.

void
Symbol_table::write_section_symbol(const Output_section *os,
				   Output_file* of,
				   off_t offset) const
{
  if (parameters->get_size() == 32)
    {
      if (parameters->is_big_endian())
	{
#ifdef HAVE_TARGET_32_BIG
	  this->sized_write_section_symbol<32, true>(os, of, offset);
#else
	  gold_unreachable();
#endif
	}
      else
	{
#ifdef HAVE_TARGET_32_LITTLE
	  this->sized_write_section_symbol<32, false>(os, of, offset);
#else
	  gold_unreachable();
#endif
	}
    }
  else if (parameters->get_size() == 64)
    {
      if (parameters->is_big_endian())
	{
#ifdef HAVE_TARGET_64_BIG
	  this->sized_write_section_symbol<64, true>(os, of, offset);
#else
	  gold_unreachable();
#endif
	}
      else
	{
#ifdef HAVE_TARGET_64_LITTLE
	  this->sized_write_section_symbol<64, false>(os, of, offset);
#else
	  gold_unreachable();
#endif
	}
    }
  else
    gold_unreachable();
}

// Write out a section symbol, specialized for size and endianness.

template<int size, bool big_endian>
void
Symbol_table::sized_write_section_symbol(const Output_section* os,
					 Output_file* of,
					 off_t offset) const
{
  const int sym_size = elfcpp::Elf_sizes<size>::sym_size;

  unsigned char* pov = of->get_output_view(offset, sym_size);

  elfcpp::Sym_write<size, big_endian> osym(pov);
  osym.put_st_name(0);
  osym.put_st_value(os->address());
  osym.put_st_size(0);
  osym.put_st_info(elfcpp::elf_st_info(elfcpp::STB_LOCAL,
				       elfcpp::STT_SECTION));
  osym.put_st_other(elfcpp::elf_st_other(elfcpp::STV_DEFAULT, 0));
  osym.put_st_shndx(os->out_shndx());

  of->write_output_view(offset, sym_size, pov);
}

// Print statistical information to stderr.  This is used for --stats.

void
Symbol_table::print_stats() const
{
#if defined(HAVE_TR1_UNORDERED_MAP) || defined(HAVE_EXT_HASH_MAP)
  fprintf(stderr, _("%s: symbol table entries: %zu; buckets: %zu\n"),
	  program_name, this->table_.size(), this->table_.bucket_count());
#else
  fprintf(stderr, _("%s: symbol table entries: %zu\n"),
	  program_name, this->table_.size());
#endif
  this->namepool_.print_stats("symbol table stringpool");
}

// We check for ODR violations by looking for symbols with the same
// name for which the debugging information reports that they were
// defined in different source locations.  When comparing the source
// location, we consider instances with the same base filename and
// line number to be the same.  This is because different object
// files/shared libraries can include the same header file using
// different paths, and we don't want to report an ODR violation in
// that case.

// This struct is used to compare line information, as returned by
// Dwarf_line_info::one_addr2line.  It implements a < comparison
// operator used with std::set.

struct Odr_violation_compare
{
  bool
  operator()(const std::string& s1, const std::string& s2) const
  {
    std::string::size_type pos1 = s1.rfind('/');
    std::string::size_type pos2 = s2.rfind('/');
    if (pos1 == std::string::npos
	|| pos2 == std::string::npos)
      return s1 < s2;
    return s1.compare(pos1, std::string::npos,
		      s2, pos2, std::string::npos) < 0;
  }
};

// Check candidate_odr_violations_ to find symbols with the same name
// but apparently different definitions (different source-file/line-no).

void
Symbol_table::detect_odr_violations(const Task* task,
				    const char* output_file_name) const
{
  for (Odr_map::const_iterator it = candidate_odr_violations_.begin();
       it != candidate_odr_violations_.end();
       ++it)
    {
      const char* symbol_name = it->first;
      // We use a sorted set so the output is deterministic.
      std::set<std::string, Odr_violation_compare> line_nums;

      for (Unordered_set<Symbol_location, Symbol_location_hash>::const_iterator
               locs = it->second.begin();
           locs != it->second.end();
           ++locs)
        {
	  // We need to lock the object in order to read it.  This
	  // means that we have to run in a singleton Task.  If we
	  // want to run this in a general Task for better
	  // performance, we will need one Task for object, plus
	  // appropriate locking to ensure that we don't conflict with
	  // other uses of the object.
	  Task_lock_obj<Object> tl(task, locs->object);
          std::string lineno = Dwarf_line_info::one_addr2line(
              locs->object, locs->shndx, locs->offset);
          if (!lineno.empty())
            line_nums.insert(lineno);
        }

      if (line_nums.size() > 1)
        {
          gold_warning(_("while linking %s: symbol '%s' defined in multiple "
                         "places (possible ODR violation):"),
                       output_file_name, demangle(symbol_name).c_str());
          for (std::set<std::string>::const_iterator it2 = line_nums.begin();
               it2 != line_nums.end();
               ++it2)
            fprintf(stderr, "  %s\n", it2->c_str());
        }
    }
}

// Warnings functions.

// Add a new warning.

void
Warnings::add_warning(Symbol_table* symtab, const char* name, Object* obj,
		      const std::string& warning)
{
  name = symtab->canonicalize_name(name);
  this->warnings_[name].set(obj, warning);
}

// Look through the warnings and mark the symbols for which we should
// warn.  This is called during Layout::finalize when we know the
// sources for all the symbols.

void
Warnings::note_warnings(Symbol_table* symtab)
{
  for (Warning_table::iterator p = this->warnings_.begin();
       p != this->warnings_.end();
       ++p)
    {
      Symbol* sym = symtab->lookup(p->first, NULL);
      if (sym != NULL
	  && sym->source() == Symbol::FROM_OBJECT
	  && sym->object() == p->second.object)
	sym->set_has_warning();
    }
}

// Issue a warning.  This is called when we see a relocation against a
// symbol for which has a warning.

template<int size, bool big_endian>
void
Warnings::issue_warning(const Symbol* sym,
			const Relocate_info<size, big_endian>* relinfo,
			size_t relnum, off_t reloffset) const
{
  gold_assert(sym->has_warning());
  Warning_table::const_iterator p = this->warnings_.find(sym->name());
  gold_assert(p != this->warnings_.end());
  gold_warning_at_location(relinfo, relnum, reloffset,
			   "%s", p->second.text.c_str());
}

// Instantiate the templates we need.  We could use the configure
// script to restrict this to only the ones needed for implemented
// targets.

#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_32_BIG)
template
void
Sized_symbol<32>::allocate_common(Output_data*, Value_type);
#endif

#if defined(HAVE_TARGET_64_LITTLE) || defined(HAVE_TARGET_64_BIG)
template
void
Sized_symbol<64>::allocate_common(Output_data*, Value_type);
#endif

#ifdef HAVE_TARGET_32_LITTLE
template
void
Symbol_table::add_from_relobj<32, false>(
    Sized_relobj<32, false>* relobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    Sized_relobj<32, true>::Symbols* sympointers);
#endif

#ifdef HAVE_TARGET_32_BIG
template
void
Symbol_table::add_from_relobj<32, true>(
    Sized_relobj<32, true>* relobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    Sized_relobj<32, false>::Symbols* sympointers);
#endif

#ifdef HAVE_TARGET_64_LITTLE
template
void
Symbol_table::add_from_relobj<64, false>(
    Sized_relobj<64, false>* relobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    Sized_relobj<64, true>::Symbols* sympointers);
#endif

#ifdef HAVE_TARGET_64_BIG
template
void
Symbol_table::add_from_relobj<64, true>(
    Sized_relobj<64, true>* relobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    Sized_relobj<64, false>::Symbols* sympointers);
#endif

#ifdef HAVE_TARGET_32_LITTLE
template
void
Symbol_table::add_from_dynobj<32, false>(
    Sized_dynobj<32, false>* dynobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    const unsigned char* versym,
    size_t versym_size,
    const std::vector<const char*>* version_map);
#endif

#ifdef HAVE_TARGET_32_BIG
template
void
Symbol_table::add_from_dynobj<32, true>(
    Sized_dynobj<32, true>* dynobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    const unsigned char* versym,
    size_t versym_size,
    const std::vector<const char*>* version_map);
#endif

#ifdef HAVE_TARGET_64_LITTLE
template
void
Symbol_table::add_from_dynobj<64, false>(
    Sized_dynobj<64, false>* dynobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    const unsigned char* versym,
    size_t versym_size,
    const std::vector<const char*>* version_map);
#endif

#ifdef HAVE_TARGET_64_BIG
template
void
Symbol_table::add_from_dynobj<64, true>(
    Sized_dynobj<64, true>* dynobj,
    const unsigned char* syms,
    size_t count,
    const char* sym_names,
    size_t sym_name_size,
    const unsigned char* versym,
    size_t versym_size,
    const std::vector<const char*>* version_map);
#endif

#if defined(HAVE_TARGET_32_LITTLE) || defined(HAVE_TARGET_32_BIG)
template
void
Symbol_table::define_with_copy_reloc<32>(
    Sized_symbol<32>* sym,
    Output_data* posd,
    elfcpp::Elf_types<32>::Elf_Addr value);
#endif

#if defined(HAVE_TARGET_64_LITTLE) || defined(HAVE_TARGET_64_BIG)
template
void
Symbol_table::define_with_copy_reloc<64>(
    Sized_symbol<64>* sym,
    Output_data* posd,
    elfcpp::Elf_types<64>::Elf_Addr value);
#endif

#ifdef HAVE_TARGET_32_LITTLE
template
void
Warnings::issue_warning<32, false>(const Symbol* sym,
				   const Relocate_info<32, false>* relinfo,
				   size_t relnum, off_t reloffset) const;
#endif

#ifdef HAVE_TARGET_32_BIG
template
void
Warnings::issue_warning<32, true>(const Symbol* sym,
				  const Relocate_info<32, true>* relinfo,
				  size_t relnum, off_t reloffset) const;
#endif

#ifdef HAVE_TARGET_64_LITTLE
template
void
Warnings::issue_warning<64, false>(const Symbol* sym,
				   const Relocate_info<64, false>* relinfo,
				   size_t relnum, off_t reloffset) const;
#endif

#ifdef HAVE_TARGET_64_BIG
template
void
Warnings::issue_warning<64, true>(const Symbol* sym,
				  const Relocate_info<64, true>* relinfo,
				  size_t relnum, off_t reloffset) const;
#endif

} // End namespace gold.
