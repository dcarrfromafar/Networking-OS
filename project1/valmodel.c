#include <stdbool.h>

#include "statemodel.h"
#include "valmodel.h"

// Set up appropriate tables as in stringmodel.c.

bool
initialize_val_fsm (fsm_t *fsm)
{
  // See the hint in stringmodel.c.

  return false;
}

static state_t
transition (fsm_t *fsm, event_t event, action_t *effect, action_t *entry)
{
  state_t next;

  // Strings that are helpful for debugging
  // static const char * event_names[]
  //     = { "START_VALUE", "WHITESPACE", "START_STR",
  //         "END_STR",     "START_INT",  "END_INT",
  //         "BAD_VALUE",   "NIL_VAL" };
  // static const char *state_names[]
  //     = { "VAL_INIT",  "VAL_SKIP",   "BUILD_STR",
  //         "BUILD_INT", "VAL_FINISH", "VAL_ERROR",
  //         "NON_VAL" };
  // if (debug)
  //   printf ("%s.%s -> %s\n", state_names[current],
  //           event_names[event], state_names[next]);

  return next;
}

/* Value version of the handle_event function */
void
value_event (fsm_t *fsm, valevt_t event)
{
  // Declare an event_t, put event in it, and call handle_event().
}

// /////////////////// EFFECT FUNCTIONS ////////////////////

// Use this format string for syntax errors:
// printf ("SYNTAX ERROR: '%c' is an invalid token\n", ...
