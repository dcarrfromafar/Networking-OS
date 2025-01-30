/*
 * COMP 3400: Template lab driver
 *
 * Name: Samuel Costa
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "statemodel.h"

void
usage (void)
{
  printf ("fsm, a state model simulator\n\n");
  printf ("usage: fsm [evt1 evt2 ...]\n");
  printf ("evt1 evt2 ... is a sequence of event combinations. Each event is\n");
  printf ("represented by an int value:\n\n");
  printf ("  ADMIT = 0\n");
  printf ("  DISPATCH = 1\n");
  printf ("  SCHEDULE = 2\n");
  printf ("  BLOCK = 3\n");
  printf ("  UNBLOCK = 4\n");
  printf ("  EXIT = 5\n");
  printf ("  KILL = 6\n");
  printf ("  NIL = 7\n");
}

int
main (int argc, char **argv)
{
  // With no arguments, show usage and exit
  if (argc < 2)
    {
      usage ();
      return EXIT_FAILURE;
    }

  // Declare and initialize a FSM
  fsm_t process;
  if (! initialize_fsm (&process))
    return EXIT_FAILURE;

  // EXAMPLE: Send ADMIT and DISPATCH to the process.
  // TODO: Replace this with a loop for all events.
	for(int i = 1; i < argc; ++i)
		handle_event(&process, atoi(argv[i]));	

  // Under normal runs, we should always end in TRM state
  if (process.state != TRM)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

