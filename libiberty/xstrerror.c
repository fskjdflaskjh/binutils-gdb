/* xstrerror.c -- jacket routine for more robust strerror() usage.
   Fri Jun 16 18:30:00 1995  Pat Rankin  <rankin@eql.caltech.edu>
   This code is in the public domain.  */

/*

@deftypefn Replacement char* xstrerror (int @var{errnum})

Behaves exactly like the standard @code{strerror} function, but
will never return a NULL pointer.

@end deftypefn

*/

#include <stdio.h>

#include "libiberty.h"
#include "config.h"

#ifdef VMS
#include <errno.h>
#if !defined (__STRICT_ANSI__) && !defined (__HIDE_FORBIDDEN_NAMES)
extern char *strerror PARAMS ((int,...));
#define DONT_DECLARE_STRERROR
#endif
#endif	/* VMS */

#ifndef DONT_DECLARE_STRERROR
extern char *strerror PARAMS ((int));
#endif

/* If strerror returns NULL, we'll format the number into a static buffer.  */

#define ERRSTR_FMT "undocumented error #%d"
static char xstrerror_buf[sizeof ERRSTR_FMT + 20];

/* Like strerror, but result is never a null pointer.  */

char *
xstrerror (errnum)
     int errnum;
{
  char *errstr;
#ifdef VMS
  char *(*vmslib_strerror) PARAMS ((int,...));

  /* Override any possibly-conflicting declaration from system header.  */
  vmslib_strerror = (char *(*) PARAMS ((int,...))) strerror;
  /* Second argument matters iff first is EVMSERR, but it's simpler to
     pass it unconditionally.  `vaxc$errno' is declared in <errno.h>
     and maintained by the run-time library in parallel to `errno'.
     We assume that `errnum' corresponds to the last value assigned to
     errno by the run-time library, hence vaxc$errno will be relevant.  */
  errstr = (*vmslib_strerror) (errnum, vaxc$errno);
#else
  errstr = strerror (errnum);
#endif

  /* If `errnum' is out of range, result might be NULL.  We'll fix that.  */
  if (!errstr)
    {
      sprintf (xstrerror_buf, ERRSTR_FMT, errnum);
      errstr = xstrerror_buf;
    }
  return errstr;
}
