/* Portable version of strrchr().
   This function is in the public domain. */

/*

@deftypefn Supplemental char* strrchr (const char *@var{s}, int @var{c})

Returns a pointer to the last occurance of the character @var{c} in
the string @var{s}, or NULL if not found.  If @var{c} is itself the
null character, the results are undefined.

@end deftypefn

*/

#include <ansidecl.h>

char *
strrchr (s, c)
  register const char *s;
  int c;
{
  char *rtnval = 0;

  do {
    if (*s == c)
      rtnval = (char*) s;
  } while (*s++);
  return (rtnval);
}
