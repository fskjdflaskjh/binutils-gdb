// options.c -- handle command line options for gold

#include <iostream>

#include "gold.h"
#include "options.h"

// The information we keep for a single command line option.

struct gold::options::One_option
{
  // The single character option name, or '\0' if this is only a long
  // option.
  char short_option;

  // The long option name, or NULL if this is only a short option.
  const char* long_option;

  // Description of the option for --help output, or NULL if there is none.
  const char* doc;

  // How to print the option name in --help output, or NULL to use the
  // default.
  const char* help_output;

  // Long option dash control.  This is ignored if long_option is
  // NULL.
  enum
    {
      // Long option normally takes one dash; two dashes are also
      // accepted.
      ONE_DASH,
      // Long option normally takes two dashes; one dash is also
      // accepted.
      TWO_DASHES,
      // Long option always takes two dashes.
      EXACTLY_TWO_DASHES
    } dash;

  // Function for special handling, or NULL.  Returns the number of
  // arguments to skip.  This will normally be at least 1, but it may
  // be 0 if this function changes *argv.  ARG points to the location
  // in *ARGV where the option starts, which may be helpful for a
  // short option.
  int (*special)(int argc, char** argv, char *arg, gold::Command_line*);

  // If this is a position independent option which does not take an
  // argument, this is the member function to call to record it.
  void (gold::General_options::*general_noarg)();

  // If this is a position independent function which takes an
  // argument, this is the member function to call to record it.
  void (gold::General_options::*general_arg)(const char*);

  // If this is a position dependent option which does not take an
  // argument, this is the member function to call to record it.
  void (gold::Position_dependent_options::*dependent_noarg)();

  // If this is a position dependent option which takes an argument,
  // this is the member function to record it.
  void (gold::Position_dependent_options::*dependent_arg)(const char*);

  // Return whether this option takes an argument.
  bool
  takes_argument() const
  { return this->general_arg != NULL || this->dependent_arg != NULL; }
};

class gold::options::Command_line_options
{
 public:
  static const One_option options[];
  static const int options_size;
};

namespace
{

// Report usage information for ld --help, and exit.

int
help(int, char**, char*, gold::Command_line*)
{
  printf(_("Usage: %s [options] file...\nOptions:\n"), gold::program_name);

  const int options_size = gold::options::Command_line_options::options_size;
  const gold::options::One_option* options =
    gold::options::Command_line_options::options;
  for (int i = 0; i < options_size; ++i)
    {
      if (options[i].doc == NULL)
	continue;

      printf("  ");
      int len = 2;
      bool comma = false;

      int j = i;
      do
	{
	  if (options[j].help_output != NULL)
	    {
	      if (comma)
		{
		  printf(", ");
		  len += 2;
		}
	      printf(options[j].help_output);
	      len += std::strlen(options[i].help_output);
	    }
	  else
	    {
	      if (options[j].short_option != '\0')
		{
		  if (comma)
		    {
		      printf(", ");
		      len += 2;
		    }
		  printf("-%c", options[j].short_option);
		  len += 2;
		}

	      if (options[j].long_option != NULL)
		{
		  if (comma)
		    {
		      printf(", ");
		      len += 2;
		    }
		  if (options[j].dash == gold::options::One_option::ONE_DASH)
		    {
		      printf("-");
		      ++len;
		    }
		  else
		    {
		      printf("--");
		      len += 2;
		    }
		  printf("%s", options[j].long_option);
		  len += std::strlen(options[j].long_option);
		}
	    }
	  ++j;
	}
      while (j < options_size && options[j].doc == NULL);

      if (len > 30)
	{
	  printf("\n");
	  len = 0;
	}
      for (; len < 30; ++len)
	std::putchar(' ');

      std::puts(options[i].doc);
    }

  gold::gold_exit(true);

  return 0;
}

} // End empty namespace.

// Helper macros used to specify the options.  We could also do this
// using constructors, but then g++ would generate code to initialize
// the array.  We want the array to be initialized statically so that
// we get better startup time.

#define GENERAL_NOARG(short_option, long_option, doc, help, dash, func)	\
  { short_option, long_option, doc, help, gold::options::One_option::dash, \
      NULL, func, NULL, NULL, NULL }
#define GENERAL_ARG(short_option, long_option, doc, help, dash, func)	\
  { short_option, long_option, doc, help, gold::options::One_option::dash, \
      NULL, NULL, func, NULL, NULL }
#define POSDEP_NOARG(short_option, long_option, doc, help, dash, func)	\
  { short_option, long_option, doc, help, gold::options::One_option::dash, \
      NULL,  NULL, NULL, func, NULL }
#define POSDEP_ARG(short_option, long_option, doc, help, dash, func)	\
  { short_option, long_option, doc, help, gold::options::One_option::dash, \
      NULL, NULL, NULL, NULL, func }
#define SPECIAL(short_option, long_option, doc, help, dash, func)	\
  { short_option, long_option, doc, help, gold::options::One_option::dash, \
      func, NULL, NULL, NULL, NULL }

// Here is the actual list of options which we accept.

const gold::options::One_option
gold::options::Command_line_options::options[] =
{
  GENERAL_ARG('L', "library-path", N_("Add directory to search path"),
	      N_("-L DIR, --library-path DIR"), TWO_DASHES,
	      &gold::General_options::add_to_search_path),
  GENERAL_NOARG('r', NULL, N_("Generate relocatable output"), NULL,
		ONE_DASH, &gold::General_options::set_relocatable),
  GENERAL_NOARG('\0', "static", N_("Do not link against shared libraries"),
		NULL, ONE_DASH, &gold::General_options::set_static),
  SPECIAL('\0', "help", N_("Report usage information"), NULL,
	  TWO_DASHES, &help)
};

const int gold::options::Command_line_options::options_size =
  sizeof (options) / sizeof (options[0]);

// The default values for the general options.

gold::General_options::General_options()
  : is_relocatable_(false)
{
}

// The default values for the position dependent options.

gold::Position_dependent_options::Position_dependent_options()
  : do_static_search_(false)
{
}

// Construct a Command_line.

gold::Command_line::Command_line()
{
}

// Process the command line options.

void
gold::Command_line::process(int argc, char** argv)
{
  const int options_size = gold::options::Command_line_options::options_size;
  const gold::options::One_option* options =
    gold::options::Command_line_options::options;
  bool no_more_options = false;
  int i = 0;
  while (i < argc)
    {
      if (argv[i][0] != '-' || no_more_options)
	{
	  this->inputs_.push_back(Input_argument(argv[i],
						 this->position_options_));
	  ++i;
	  continue;
	}

      // Option starting with '-'.
      int dashes = 1;
      if (argv[i][1] == '-')
	{
	  dashes = 2;
	  if (argv[i][2] == '\0')
	    {
	      no_more_options = true;
	      continue;
	    }
	}

      // Look for a long option match.
      char* opt = argv[i] + dashes;
      char first = opt[0];
      int skiparg = 0;
      char* arg = strchr(opt, '=');
      if (arg != NULL)
	*arg = '\0';
      else if (i + 1 < argc)
	{
	  arg = argv[i + 1];
	  skiparg = 1;
	}

      int j;
      for (j = 0; j < options_size; ++j)
	{
	  if (options[j].long_option != NULL
	      && (dashes == 2
		  || (options[j].dash
		      != gold::options::One_option::EXACTLY_TWO_DASHES))
	      && first == options[j].long_option[0]
	      && strcmp(opt, options[j].long_option) == 0)
	    {
	      if (options[j].special)
		i += options[j].special(argc - 1, argv + i, opt, this);
	      else
		{
		  if (!options[j].takes_argument())
		    {
		      arg = NULL;
		      skiparg = 0;
		    }
		  else
		    {
		      if (arg == NULL)
			this->usage(_("missing argument"), argv[i]);
		    }
		  this->apply_option(options[j], arg);
		  i += skiparg + 1;
		}
	      break;
	    }
	}
      if (j < options_size)
	continue;

      // If we saw two dashes, we need to see a long option.
      if (dashes == 2)
	this->usage(_("unknown option"), argv[i]);

      // Look for a short option match.  There may be more than one
      // short option in a given argument.
      bool done = false;
      char* s = argv[i] + 1;
      ++i;
      while (*s != '\0' && !done)
	{
	  char opt = *s;
	  int j;
	  for (j = 0; j < options_size; ++j)
	    {
	      if (options[j].short_option == opt)
		{
		  if (options[j].special)
		    {
		      // Undo the argument skip done above.
		      --i;
		      i += options[j].special(argc - i, argv + i, s, this);
		      done = true;
		    }
		  else
		    {
		      arg = NULL;
		      if (options[j].takes_argument())
			{
			  if (s[1] != '\0')
			    {
			      arg = s + 1;
			      done = true;
			    }
			  else if (i < argc)
			    {
			      arg = argv[i];
			      ++i;
			    }
			  else
			    this->usage(_("missing argument"), opt);
			}
		      this->apply_option(options[j], arg);
		    }
		  break;
		}
	    }

	  if (j >= options_size)
	    this->usage(_("unknown option"), *s);

	  ++s;
	}
    }
}

// Apply a command line option.

void
gold::Command_line::apply_option(const gold::options::One_option& opt,
				 const char* arg)
{
  if (arg == NULL)
    {
      if (opt.general_noarg)
	(this->options_.*(opt.general_noarg))();
      else if (opt.dependent_noarg)
	(this->position_options_.*(opt.dependent_noarg))();
      else
	gold::gold_unreachable();
    }
  else
    {
      if (opt.general_arg)
	(this->options_.*(opt.general_arg))(arg);
      else if (opt.dependent_arg)
	(this->position_options_.*(opt.dependent_arg))(arg);
      else
	gold::gold_unreachable();
    }
}

// Report a usage error.  */

void
gold::Command_line::usage()
{
  fprintf(stderr,
	  _("%s: use the --help option for usage information\n"),
	  gold::program_name);
  gold::gold_exit(false);
}

void
gold::Command_line::usage(const char* msg, const char *opt)
{
  fprintf(stderr,
	  _("%s: %s: %s\n"),
	  gold::program_name, opt, msg);
  this->usage();
}

void
gold::Command_line::usage(const char* msg, char opt)
{
  fprintf(stderr,
	  _("%s: -%c: %s\n"),
	  gold::program_name, opt, msg);
  this->usage();
}
