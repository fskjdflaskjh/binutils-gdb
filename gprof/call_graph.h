/* call_graph.h
   
   Copyright 2000 Free Software Foundation, Inc.

This file is part of GNU Binutils.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef call_graph_h
#define call_graph_h

#include <stdio.h>
#include "gprof.h"
#include "symtab.h"

extern void cg_tally      PARAMS ((bfd_vma, bfd_vma, unsigned long));
extern void cg_read_rec   PARAMS ((FILE *, const char *));
extern void cg_write_arcs PARAMS ((FILE *, const char *));

#endif /* call_graph_h */
