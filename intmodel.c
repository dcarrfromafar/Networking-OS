#include <stdbool.h>

#include "intmodel.h"
#include "statemodel.h"

// Set up appropriate tables as in stringmodel.c.
static strst_t const transitions[NINT_STATES][NINT_EVENTS] = {
//  ZERO       HYPHEN    NZ_DIGIT    DIGIT      TERM_INT     NON_DIGIT  NIL_INT
	{ OCTAL,     SIGN,     MAGNITUDE,  NON_INT,   NON_INT,     NON_INT,   NON_INT}, // INT_INIT	
  { NON_INT,   NON_INT,  NON_INT,    MAGNITUDE, INT_FINISH,  INT_ERROR, NON_INT}, // MAGNITUDE
  { OCTAL,     NON_INT,  MAGNITUDE,  NON_INT,   NON_INT,     INT_ERROR, NON_INT}, // SIGN
  { OCTAL,     NON_INT,  MAGNITUDE,  NON_INT,   INT_FINISH,  INT_ERROR, NON_INT}, // OCTAL
  { NON_INT,   NON_INT,  NON_INT,    NON_INT,   NON_INT,     NON_INT,   NON_INT}, // INT_FINISH
  { NON_INT,   NON_INT,  NON_INT,    NON_INT,   NON_INT,     NON_INT,   NON_INT}  // INT_ERROR
};

static strst_t const effects[NINT_STATES][NINT_EVENTS] = {
//  ZERO   HYPHEN        NZ_DIGIT          DIGIT       TERM_INIT   NON_DIGIT    NIL_INT
	{ NULL,  SetNegative,  SetMultiplier_10, NULL,       NULL,       NULL,        NULL}, // INT_INIT	
  { NULL,  NULL,         NULL,             MultAndAdd, NULL,       SyntaxError, NULL}, // MAGNITUDE
  { NULL,  NULL,         SetMultiplier_10, NULL,       NULL,       SyntaxError, NULL}, // SIGN
  { NULL,  NULL,         SetMultiplier_8,  NULL,       NULL,       SyntaxError, NULL}, // OCTAL
  { NULL,  NULL,         NULL,             NULL,       NULL,       NULL,        NULL}, // INT_FINISH
  { NULL,  NULL,         NULL,             NULL,       NULL,       NULL,        NULL}  // INT_ERROR
};

static action_t const entries[NINT_OF_STATES] = {
  NULL, NULL, NULL, NULL, NULL
};

bool
initialize_int_fsm (fsm_t *fsm)
{
  // See the hint in stringmodel.c.
  if(fsm == NULL)
  {
 	  return false;
 	}
 	
 	fsm -> type = INT;
 	fsm -> state.integer = INT_INIT;
 	fsm -> max_valid_event.integer = NIL_INT;
 	fsm -> max_valid_state.integer = NON_INT;
 	fsm -> transition = transition;
 	return true;
}

static state_t
transition (fsm_t *fsm, event_t event, action_t *effect, action_t *entry)
{
  state_t next;

  // Strings that are helpful for debugging
  // static const char *event_names[]
  //     = { "ZERO",     "HYPHEN",    "NZ_DIGIT", "DIGIT",
  //         "TERM_INT", "NON_DIGIT", "NIL_INT" };
  // static const char *state_names[]
  //     = { "INT_INIT",   "MAGNITUDE", "SIGN",   "OCTAL",
  //         "INT_FINISH", "INT_ERROR", "NON_INT" };
	if(fsm -> state <= NON_INT && event <= NIL_INT)
	{
		next = transitions[fsm->state][event];
		*entry = entries[next];
		*effect = effects[fsm->state][event];
  	return next;
  }
  return NON_INT;
}

/* Integer version of the handle_event function */
void
integer_event (fsm_t *fsm, intevt_t event)
{
  // Declare an event_t, put event in it, and call handle_event().
  event_t ev;
  ev.integer = event;
  handle_event(fsm, ev);
  
}

// /////////////////// EFFECT FUNCTIONS ////////////////////

// Use this format string for syntax errors:
// printf ("SYNTAX ERROR: '%c' is not a valid digit\n", ...
