/* plugin-api.h -- External linker plugin API.  */

/* Copyright 2008 Free Software Foundation, Inc.
   Written by Cary Coutant <ccoutant@google.com>.

   This file is part of binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

/* This file defines the interface for writing a linker plugin, which is
   described at < http://gcc.gnu.org/wiki/whopr/driver >.  */

#ifndef PLUGIN_API_H
#define PLUGIN_API_H

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Status code returned by most API routines.  */

enum ld_plugin_status
{
  LDPS_OK = 0,
  LDPS_NO_SYMS,         /* Attempt to get symbols that haven't been added. */
  LDPS_ERR
  /* Additional Error codes TBD.  */
};

/* The version of the API specification.  */

enum ld_plugin_api_version
{
  LD_PLUGIN_API_VERSION = 1
};

/* The type of output file being generated by the linker.  */

enum ld_plugin_output_file_type
{
  LDPO_REL,
  LDPO_EXEC,
  LDPO_DYN
};

/* An input file managed by the plugin library.  */

struct ld_plugin_input_file
{
  const char *name;
  int fd;
  off_t offset;
  off_t filesize;
  void *handle;
};

/* A symbol belonging to an input file managed by the plugin library.  */

struct ld_plugin_symbol
{
  char *name;
  char *version;
  int def;
  int visibility;
  uint64_t size;
  char *comdat_key;
  int resolution;
};

/* Whether the symbol is a definition, reference, or common, weak or not.  */

enum ld_plugin_symbol_kind
{
  LDPK_DEF,
  LDPK_WEAKDEF,
  LDPK_UNDEF,
  LDPK_WEAKUNDEF,
  LDPK_COMMON
};

/* The visibility of the symbol.  */

enum ld_plugin_symbol_visibility
{
  LDPV_DEFAULT,
  LDPV_PROTECTED,
  LDPV_INTERNAL,
  LDPV_HIDDEN
};

/* How a symbol is resolved.  */

enum ld_plugin_symbol_resolution
{
  LDPR_UNKNOWN = 0,
  LDPR_UNDEF,
  LDPR_PREVAILING_DEF,
  LDPR_PREVAILING_DEF_IRONLY,
  LDPR_PREEMPTED_REG,
  LDPR_PREEMPTED_IR,
  LDPR_RESOLVED_IR,
  LDPR_RESOLVED_EXEC,
  LDPR_RESOLVED_DYN
};

/* The plugin library's "claim file" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_claim_file_handler) (
  const struct ld_plugin_input_file *file, int *claimed);

/* The plugin library's "all symbols read" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_all_symbols_read_handler) (void);

/* The plugin library's cleanup handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_cleanup_handler) (void);

/* The linker's interface for registering the "claim file" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_register_claim_file) (ld_plugin_claim_file_handler handler);

/* The linker's interface for registering the "all symbols read" handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_register_all_symbols_read) (
  ld_plugin_all_symbols_read_handler handler);

/* The linker's interface for registering the cleanup handler.  */

typedef
enum ld_plugin_status
(*ld_plugin_register_cleanup) (ld_plugin_cleanup_handler handler);

/* The linker's interface for adding symbols from a claimed input file.  */

typedef
enum ld_plugin_status
(*ld_plugin_add_symbols) (void *handle, int nsyms,
                          const struct ld_plugin_symbol *syms);

/* The linker's interface for retrieving symbol resolution information.  */

typedef
enum ld_plugin_status
(*ld_plugin_get_symbols) (const void *handle, int nsyms,
                          struct ld_plugin_symbol *syms);

/* The linker's interface for adding a compiled input file.  */

typedef
enum ld_plugin_status
(*ld_plugin_add_input_file) (char *pathname);

/* The linker's interface for issuing a warning or error message.  */

typedef
enum ld_plugin_status
(*ld_plugin_message) (int level, const char *format, ...);

enum ld_plugin_level
{
  LDPL_INFO,
  LDPL_WARNING,
  LDPL_ERROR,
  LDPL_FATAL
};

/* Values for the tv_tag field of the transfer vector.  */

enum ld_plugin_tag
{
  LDPT_NULL = 0,
  LDPT_API_VERSION,
  LDPT_GOLD_VERSION,
  LDPT_LINKER_OUTPUT,
  LDPT_OPTION,
  LDPT_REGISTER_CLAIM_FILE_HOOK,
  LDPT_REGISTER_ALL_SYMBOLS_READ_HOOK,
  LDPT_REGISTER_CLEANUP_HOOK,
  LDPT_ADD_SYMBOLS,
  LDPT_GET_SYMBOLS,
  LDPT_ADD_INPUT_FILE,
  LDPT_MESSAGE
};

/* The plugin transfer vector.  */

struct ld_plugin_tv
{
  enum ld_plugin_tag tv_tag;
  union
  {
    int tv_val;
    const char *tv_string;
    ld_plugin_register_claim_file tv_register_claim_file;
    ld_plugin_register_all_symbols_read tv_register_all_symbols_read;
    ld_plugin_register_cleanup tv_register_cleanup;
    ld_plugin_add_symbols tv_add_symbols;
    ld_plugin_get_symbols tv_get_symbols;
    ld_plugin_add_input_file tv_add_input_file;
    ld_plugin_message tv_message;
  } tv_u;
};

/* The plugin library's "onload" entry point.  */

typedef
enum ld_plugin_status
(*ld_plugin_onload) (struct ld_plugin_tv *tv);

#ifdef __cplusplus
}
#endif

#endif /* !defined(PLUGIN_API_H) */
