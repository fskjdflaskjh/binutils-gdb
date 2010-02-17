/* Alpha VMS external format of Extended Program Section Definition.

   Copyright 2010 Free Software Foundation, Inc.
   Written by Tristan Gingold <gingold@adacore.com>, AdaCore.

   This file is part of BFD, the Binary File Descriptor library.

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

#ifndef _VMS_EGPS_H
#define _VMS_EGPS_H

struct vms_egps
{
  /* Entry type.  */
  unsigned char gsdtyp[2];

  /* Length of the entry.  */
  unsigned char gsdsiz[2];

  /* Psect alignment.  */
  unsigned char align;

  /* Pad for alignment.  */
  unsigned char temp;

  unsigned char flags[2];

  /* Length of this contribution.  */
  unsigned char alloc[4];

  /* Name.  */
  unsigned char namlng;
  unsigned char name[31];
};

#endif /* _VMS_EGPS_H */
