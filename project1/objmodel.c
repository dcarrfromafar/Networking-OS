#include <stdbool.h>

#include "objmodel.h"
#include "statemodel.h"

// Set up appropriate tables as in stringmodel.c.

bool
initialize_obj_fsm (fsm_t *fsm)
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
  //     = { "OPEN_CB", "OBJ_WS",    "START_ID",  "END_ID",
  //         "BAD_ID",  "COLON",     "NON_COLON", "GOOD_VALUE",
  //         "OBJ_BV",  "BAD_TOKEN", "COMMA",     "CLOSE_CB",
  //         "NIL_OBJ" };
  // static const char *state_names[]
  //     = { "OBJ_INIT",   "OBJ_SKIP",    "BUILD_ID",
  //         "PEND_VALUE", "BUILD_VALUE", "SCANNING",
  //         "OBJ_FINISH", "OBJ_ERROR",   "NON_OBJ" };
  // if (debug)
  //   printf ("%s.%s -> %s\n", state_names[current],
  //           event_names[event], state_names[next]);

  return next;
}

/* Object version of the handle_event function */
void
object_event (fsm_t *fsm, objevt_t event)
{
  // Declare an event_t, put event in it, and call handle_event().
}

// /////////////////// EFFECT FUNCTIONS ////////////////////
// In AppendKeyValuePair, use a combination of strncat() and
// snprintf() to create format strings like the following:
//   printf ("KEYS[%s] = %" PRId64 "\n", ...
//   printf ("KEYS[%s] = %s\n", ...
// These strings should be concatenated with previous key-value
// pairs and stored somewhere that the accept_object can
// retrieve them later. Note that you can use realloc() to
// resize an existing dynamically
//  allocated string to make space to concatenate.

// For syntax errors, if there is a newline character ('\n'),
// replace it with a null byte ('\0'), then use this format
// string:

// printf ("SYNTAX ERROR: Could not process text beginning at '%s'\n", ...
