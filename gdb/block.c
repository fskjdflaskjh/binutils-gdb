/* Block-related functions for the GNU debugger, GDB.

   Copyright 2003 Free Software Foundation, Inc.

   This file is part of GDB.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include "defs.h"
#include "block.h"
#include "gdb_obstack.h"
#include "cp-support.h"

/* This is used by struct block to store namespace-related info for
   C++ files, namely using declarations and the current namespace in
   scope.  */

struct namespace_info
{
  const char *scope;
  struct using_direct *using;
};

static struct using_direct *block_using (const struct block *);

static void block_initialize_namespace (struct block *block,
					struct obstack *obstack);

/* Return Nonzero if block a is lexically nested within block b,
   or if a and b have the same pc range.
   Return zero otherwise. */

int
contained_in (const struct block *a, const struct block *b)
{
  if (!a || !b)
    return 0;
  return BLOCK_START (a) >= BLOCK_START (b)
    && BLOCK_END (a) <= BLOCK_END (b);
}


/* Return the symbol for the function which contains a specified
   lexical block, described by a struct block BL.  */

struct symbol *
block_function (const struct block *bl)
{
  while (BLOCK_FUNCTION (bl) == 0 && BLOCK_SUPERBLOCK (bl) != 0)
    bl = BLOCK_SUPERBLOCK (bl);

  return BLOCK_FUNCTION (bl);
}

/* Now come some functions designed to deal with C++ namespace issues.
   The accessors are safe to use even in the non-C++ case.  */

/* This returns the using directives associated to BLOCK (but _not_
   its parents), if any.  */

static struct using_direct *
block_using (const struct block *block)
{
  if (BLOCK_NAMESPACE (block) == NULL)
    return NULL;
  else
    return BLOCK_NAMESPACE (block)->using;
}

/* Set block_using (BLOCK) to USING; if needed, allocate memory via
   OBSTACK.  */

void
block_set_using (struct block *block, struct using_direct *using,
		 struct obstack *obstack)
{
  block_initialize_namespace (block, obstack);

  BLOCK_NAMESPACE (block)->using = using;
}

/* This returns the namespace that BLOCK is enclosed in, or "" if it
   isn't enclosed in a namespace at all.  This travels the chain of
   superblocks looking for a scope, if necessary.  */

const char *
block_scope (const struct block *block)
{
  for (; block != NULL; block = BLOCK_SUPERBLOCK (block))
    {
      if (BLOCK_NAMESPACE (block) != NULL
	  && BLOCK_NAMESPACE (block)->scope != NULL)
	return BLOCK_NAMESPACE (block)->scope;
    }

  return "";
}

/* Set block_scope (BLOCK) to SCOPE; if needed, allocate memory via
   OBSTACK.  (It won't make a copy of SCOPE, however, so that already
   has to be allocated correctly.)  */

void
block_set_scope (struct block *block, const char *scope,
		 struct obstack *obstack)
{
  block_initialize_namespace (block, obstack);

  BLOCK_NAMESPACE (block)->scope = scope;
}

/* If BLOCK_NAMESPACE (block) is NULL, allocate it via OBSTACK and
   ititialize its members to zero.  */

static void
block_initialize_namespace (struct block *block, struct obstack *obstack)
{
  if (BLOCK_NAMESPACE (block) == NULL)
    {
      BLOCK_NAMESPACE (block)
	= obstack_alloc (obstack, sizeof (struct namespace_info));
      BLOCK_NAMESPACE (block)->scope = NULL;
      BLOCK_NAMESPACE (block)->using = NULL;
    }
}

/* Return the static block associated to BLOCK.  Return NULL if block
   is NULL or if block is a global block.  */

const struct block *
block_static_block (const struct block *block)
{
  if (block == NULL || BLOCK_SUPERBLOCK (block) == NULL)
    return NULL;

  while (BLOCK_SUPERBLOCK (BLOCK_SUPERBLOCK (block)) != NULL)
    block = BLOCK_SUPERBLOCK (block);

  return block;
}

/* Initialize ITERATOR to point at the first using directive valid for
   BLOCK, and return that using directive, or NULL if there aren't
   any.  */

const struct using_direct *
block_using_iterator_first (const struct block *block,
			    struct block_using_iterator *iterator)
{
  if (block == NULL)
    return NULL;
  
  iterator->current_block = block;
  iterator->next_directive = block_using (block);

  return block_using_iterator_next (iterator);
}

/* Advance ITERATOR, and return the next using directive, or NULL if
   there aren't any more.  Don't call this if you've previously
   received NULL from block_using_iterator_first or
   block_using_iterator_next during this iteration.  */

const struct using_direct *
block_using_iterator_next (struct block_using_iterator *iterator)
{
  if (iterator->next_directive != NULL)
    {
      const struct using_direct *retval = iterator->next_directive;
      iterator->next_directive = retval->next;
      return retval;
    }
  else
    {
      while (BLOCK_SUPERBLOCK (iterator->current_block) != NULL)
	{
	  iterator->current_block
	    = BLOCK_SUPERBLOCK (iterator->current_block);
	  iterator->next_directive = block_using (iterator->current_block); 
	  if (iterator->next_directive != NULL)
	    {
	      const struct using_direct *retval = iterator->next_directive;
	      iterator->next_directive = retval->next;
	      return retval;
	    }
	}

      /* We didn't find any superblocks with using directives.  */
      return NULL;
    }
}

/* This allocates a block on OBSTACK, and initializes its elements to
   zero/NULL.  This is useful for creating "dummy" blocks that don't
   correspond to actual source files.

   Warning: it sets the block's BLOCK_DICT to NULL, which isn't a
   valid value.  If you don't want the block to have a dictiionary,
   then you should subsequently set its BLOCK_DICT to
   dict_create_linear (obstack, NULL).  */

struct block *
allocate_block (struct obstack *obstack)
{
  struct block *bl = obstack_alloc (obstack, sizeof (struct block));

  BLOCK_START (bl) = 0;
  BLOCK_END (bl) = 0;
  BLOCK_FUNCTION (bl) = NULL;
  BLOCK_SUPERBLOCK (bl) = NULL;
  BLOCK_DICT (bl) = NULL;
  BLOCK_NAMESPACE (bl) = NULL;
  BLOCK_GCC_COMPILED (bl) = 0;

  return bl;
}

