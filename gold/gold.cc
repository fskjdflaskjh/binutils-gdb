// ld.c -- linker main function

#include "gold.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "options.h"
#include "workqueue.h"
#include "dirsearch.h"
#include "readsyms.h"
#include "symtab.h"
#include "object.h"
#include "layout.h"
#include "reloc.h"

namespace gold
{

const char* program_name;

void
gold_exit(bool status)
{
  exit(status ? EXIT_SUCCESS : EXIT_FAILURE);
}

void
gold_fatal(const char* msg, bool perrno)
{
  fprintf(stderr, "%s: ", program_name);
  if (perrno)
    perror(msg);
  else
    fprintf(stderr, "%s\n", msg);
  gold_exit(false);
}

void
gold_nomem()
{
  // We are out of memory, so try hard to print a reasonable message.
  // Note that we don't try to translate this message, since the
  // translation process itself will require memory.
  write(2, program_name, strlen(program_name));
  const char* const s = ": out of memory\n";
  write(2, s, strlen(s));
  gold_exit(false);
}

void
gold_unreachable()
{
  abort();
}

// This class arranges to run the functions done in the middle of the
// link.  It is just a closure.

class Middle_runner : public Task_function_runner
{
 public:
  Middle_runner(const General_options& options,
		const Input_objects* input_objects,
		Symbol_table* symtab,
		Layout* layout)
    : options_(options), input_objects_(input_objects), symtab_(symtab),
      layout_(layout)
  { }

  void
  run(Workqueue*);

 private:
  const General_options& options_;
  const Input_objects* input_objects_;
  Symbol_table* symtab_;
  Layout* layout_;
};

void
Middle_runner::run(Workqueue* workqueue)
{
  queue_middle_tasks(this->options_, this->input_objects_, this->symtab_,
		     this->layout_, workqueue);
}

// Queue up the initial set of tasks for this link job.

void
queue_initial_tasks(const General_options& options,
		    const Dirsearch& search_path,
		    const Input_argument_list& inputs,
		    Workqueue* workqueue, Input_objects* input_objects,
		    Symbol_table* symtab, Layout* layout)
{
  if (inputs.empty())
    gold_fatal(_("no input files"), false);

  // Read the input files.  We have to add the symbols to the symbol
  // table in order.  We do this by creating a separate blocker for
  // each input file.  We associate the blocker with the following
  // input file, to give us a convenient place to delete it.
  Task_token* this_blocker = NULL;
  for (Input_argument_list::const_iterator p = inputs.begin();
       p != inputs.end();
       ++p)
    {
      Task_token* next_blocker = new Task_token();
      next_blocker->add_blocker();
      workqueue->queue(new Read_symbols(options, input_objects, symtab, layout,
					search_path, *p, this_blocker,
					next_blocker));
      this_blocker = next_blocker;
    }

  workqueue->queue(new Task_function(new Middle_runner(options,
						       input_objects,
						       symtab,
						       layout),
				     this_blocker));
}

// Queue up the middle set of tasks.  These are the tasks which run
// after all the input objects have been found and all the symbols
// have been read, but before we lay out the output file.

void
queue_middle_tasks(const General_options& options,
		   const Input_objects* input_objects,
		   Symbol_table* symtab,
		   Layout* layout,
		   Workqueue* workqueue)
{
  // Read the relocations of the input files.  We do this to find
  // which symbols are used by relocations which require a GOT and/or
  // a PLT entry, or a COPY reloc.  When we implement garbage
  // collection we will do it here by reading the relocations in a
  // breadth first search by references.
  //
  // We could also read the relocations during the first pass, and
  // mark symbols at that time.  That is how the old GNU linker works.
  // Doing that is more complex, since we may later decide to discard
  // some of the sections, and thus change our minds about the types
  // of references made to the symbols.
  Task_token* blocker = new Task_token();
  Task_token* symtab_lock = new Task_token();
  for (Input_objects::Object_list::const_iterator p = input_objects->begin();
       p != input_objects->end();
       ++p)
    {
      // We can read and process the relocations in any order.  But we
      // only want one task to write to the symbol table at a time.
      // So we queue up a task for each object to read the
      // relocations.  That task will in turn queue a task to wait
      // until it can write to the symbol table.
      blocker->add_blocker();
      workqueue->queue(new Read_relocs(options, symtab, *p, symtab_lock,
				       blocker));
    }

  // Allocate common symbols.  This requires write access to the
  // symbol table, but is independent of the relocation processing.
  // blocker->add_blocker();
  // workqueue->queue(new Allocate_commons_task(options, symtab, layout,
  //					     symtab_lock, blocker));

  // When all those tasks are complete, we can start laying out the
  // output file.
  workqueue->queue(new Task_function(new Layout_task_runner(options,
							    input_objects,
							    symtab,
							    layout),
				     blocker));
}

// Queue up the final set of tasks.  This is called at the end of
// Layout_task.

void
queue_final_tasks(const General_options& options,
		  const Input_objects* input_objects,
		  const Symbol_table* symtab,
		  const Layout* layout,
		  Workqueue* workqueue,
		  Output_file* of)
{
  // Use a blocker to block the final cleanup task.
  Task_token* final_blocker = new Task_token();

  // Queue a task for each input object to relocate the sections and
  // write out the local symbols.
  for (Input_objects::Object_list::const_iterator p = input_objects->begin();
       p != input_objects->end();
       ++p)
    {
      final_blocker->add_blocker();
      workqueue->queue(new Relocate_task(options, symtab, layout, *p, of,
					 final_blocker));
    }

  // Queue a task to write out the symbol table.
  final_blocker->add_blocker();
  workqueue->queue(new Write_symbols_task(symtab, input_objects->target(),
					  layout->sympool(), of,
					  final_blocker));

  // Queue a task to write out everything else.
  final_blocker->add_blocker();
  workqueue->queue(new Write_data_task(layout, of, final_blocker));

  // Queue a task to close the output file.  This will be blocked by
  // FINAL_BLOCKER.
  workqueue->queue(new Task_function(new Close_task_runner(of),
				     final_blocker));
}

} // End namespace gold.

using namespace gold;

int
main(int argc, char** argv)
{
#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  gold::program_name = argv[0];

  // Handle the command line options.
  gold::Command_line command_line;
  command_line.process(argc - 1, argv + 1);

  // The work queue.
  gold::Workqueue workqueue(command_line.options());

  // The list of input objects.
  Input_objects input_objects;

  // The symbol table.
  Symbol_table symtab;

  // The layout object.
  Layout layout(command_line.options());

  // Get the search path from the -L options.
  Dirsearch search_path;
  search_path.add(&workqueue, command_line.options().search_path());

  // Queue up the first set of tasks.
  queue_initial_tasks(command_line.options(), search_path,
		      command_line.inputs(), &workqueue, &input_objects,
		      &symtab, &layout);

  // Run the main task processing loop.
  workqueue.process();

  gold::gold_exit(true);
}
