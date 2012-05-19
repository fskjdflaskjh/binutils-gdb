/* Generate targ-vals.h and targ-map.c.  */

#include <stdio.h>
#include <stdlib.h>

struct tdefs {
  char *symbol;
  int value;
};

static struct tdefs sys_tdefs[] = {
#define sys_defs
#include "targ-vals.def"
#undef sys_defs
  { 0, 0 }
};

static struct tdefs errno_tdefs[] =  {
#define errno_defs
#include "targ-vals.def"
#undef errno_defs
  { 0, 0 }
};

static struct tdefs open_tdefs[] = {
#define open_defs
#include "targ-vals.def"
#undef open_defs
  { 0, 0 }
};

static void
gen_targ_vals_h ()
{
  struct tdefs *t;

  printf ("/* Target header values needed by the simulator and gdb.  */\n");
  printf ("/* This file is machine generated by gentmap.c.  */\n\n");

  printf ("#ifndef TARG_VALS_H\n");
  printf ("#define TARG_VALS_H\n\n");

  printf ("/* syscall values */\n");
  for (t = &sys_tdefs[0]; t->symbol; ++t)
    printf ("#define TARGET_%s %d\n", t->symbol, t->value);
  printf ("\n");

  printf ("/* errno values */\n");
  for (t = &errno_tdefs[0]; t->symbol; ++t)
    printf ("#define TARGET_%s %d\n", t->symbol, t->value);
  printf ("\n");

  printf ("/* open flag values */\n");
  for (t = &open_tdefs[0]; t->symbol; ++t)
    printf ("#define TARGET_%s 0x%x\n", t->symbol, t->value);
  printf ("\n");

  printf ("#endif /* TARG_VALS_H */\n");
}

static void
gen_targ_map_c ()
{
  struct tdefs *t;

  printf ("/* Target value mapping utilities needed by the simulator and gdb.  */\n");
  printf ("/* This file is machine generated by gentmap.c.  */\n\n");

  printf ("#include \"config.h\"\n");
  printf ("#include <errno.h>\n");
  printf ("#include <fcntl.h>\n");
  printf ("#include \"ansidecl.h\"\n");
  printf ("#include \"gdb/callback.h\"\n");
  printf ("#include \"targ-vals.h\"\n");
  printf ("\n");

  printf ("/* syscall mapping table */\n");
  printf ("CB_TARGET_DEFS_MAP cb_init_syscall_map[] = {\n");
  for (t = &sys_tdefs[0]; t->symbol; ++t)
    {
      printf ("#ifdef CB_%s\n", t->symbol);
      printf ("  { CB_%s, TARGET_%s },\n", t->symbol, t->symbol);
      printf ("#endif\n");
    }
  printf ("  { -1, -1 }\n");
  printf ("};\n\n");

  printf ("/* errno mapping table */\n");
  printf ("CB_TARGET_DEFS_MAP cb_init_errno_map[] = {\n");
  for (t = &errno_tdefs[0]; t->symbol; ++t)
    {
      printf ("#ifdef %s\n", t->symbol);
      printf ("  { %s, TARGET_%s },\n", t->symbol, t->symbol);
      printf ("#endif\n");
    }
  printf ("  { 0, 0 }\n");
  printf ("};\n\n");

  printf ("/* open flags mapping table */\n");
  printf ("CB_TARGET_DEFS_MAP cb_init_open_map[] = {\n");
  for (t = &open_tdefs[0]; t->symbol; ++t)
    {
      printf ("#ifdef %s\n", t->symbol);
      printf ("  { %s, TARGET_%s },\n", t->symbol, t->symbol);
      printf ("#endif\n");
    }
  printf ("  { -1, -1 }\n");
  printf ("};\n\n");
}

int
main (argc, argv)
     int argc;
     char *argv[];
{
  if (argc != 2)
    abort ();

  if (strcmp (argv[1], "-h") == 0)
    gen_targ_vals_h ();
  else if (strcmp (argv[1], "-c") == 0)
    gen_targ_map_c ();
  else
    abort ();

  exit (0);
}
