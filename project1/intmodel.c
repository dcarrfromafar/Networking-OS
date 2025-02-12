#include <stdbool.h>

#include <stdio.h>
#include <stddef.h>
#include "intmodel.h"
#include "statemodel.h"

// Set up appropriate tables as in stringmodel.c.
static intst_t const transitions[NINT_STATES][NINT_EVENTS] = {
//  ZERO       HYPHEN    NZ_DIGIT    DIGIT      TERM_INT     NON_DIGIT 
	{ OCTAL,     SIGN,     MAGNITUDE,  NON_INT,   NON_INT,     NON_INT},   // INT_INIT	
  { NON_INT,   NON_INT,  NON_INT,    MAGNITUDE, INT_FINISH,  INT_ERROR}, // MAGNITUDE
  { OCTAL,     NON_INT,  MAGNITUDE,  NON_INT,   NON_INT,     INT_ERROR}, // SIGN
  { OCTAL,     NON_INT,  MAGNITUDE,  NON_INT,   INT_FINISH,  INT_ERROR}, // OCTAL
  { NON_INT,   NON_INT,  NON_INT,    NON_INT,   NON_INT,     NON_INT},   // INT_FINISH
  { NON_INT,   NON_INT,  NON_INT,    NON_INT,   NON_INT,     NON_INT}    // INT_ERROR
};

static action_t const effects[NINT_STATES][NINT_EVENTS] = {
//  ZERO   HYPHEN        NZ_DIGIT          DIGIT       TERM_INIT   NON_DIGIT    
	{ NULL,  SetNegative,  SetMultiplier_10, NULL,       NULL,       NULL},        // INT_INIT	
  { NULL,  NULL,         NULL,             MultAndAdd, NULL,       SyntaxError}, // MAGNITUDE
  { NULL,  NULL,         SetMultiplier_10, NULL,       NULL,       SyntaxError}, // SIGN
  { NULL,  NULL,         SetMultiplier_8,  NULL,       NULL,       SyntaxError}, // OCTAL
  { NULL,  NULL,         NULL,             NULL,       NULL,       NULL},        // INT_FINISH
  { NULL,  NULL,         NULL,             NULL,       NULL,       NULL}         // INT_ERROR
};

static action_t const entries[NINT_STATES] = {
  NULL, NULL, NULL, NULL, NULL
};

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
	if(fsm -> state.integer <= NON_INT && event.integer <= NIL_INT)
	{
		next.integer = transitions[fsm->state.integer][event.integer];
		*entry = entries[next.integer];
		*effect = effects[fsm->state.integer][event.integer];
  	return next;
  }
  return fsm -> state;
}

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

/* Integer version of the handle_event function */
void
integer_event (fsm_t *fsm, intevt_t event)
{
  // Declare an event_t, put event in it, and call handle_event().
  event_t ev;
  ev.integer = event;
  handle_event(fsm, ev);
  
}


// int len = snprintf(NULL, 0, KEYS%s, ".....");
// /////////////////// EFFECT FUNCTIONS ////////////////////
static void
SetNegative(fsm_t *fsm)
{
  if(fsm->current == '-')
  {
		fsm->negative = -1;
	}
	else
	{
		fsm->negative = 1;
	}
}

static void
SetMultiplier_10(fsm_t *fsm)
{
	fsm->multiplier = 10;
}

static void
MultAndAdd(fsm_t *fsm)
{
	int newCurrent = atoi(fsm->current);
	if(fsm->multiplier = 10)
	{
		 fsm->total += newCurrent * 10;
	}	
	else
	{
		fsm->total += newCurrent * 8;
	}
}

static void
SetMultiplier_8(fsm_t *fsm)
{
	fsm->multiplier = 8;
}

static void
SyntaxError(fsm_t *fsm)
{
	// Use this format string for syntax errors:
  printf ("SYNTAX ERROR: '%c' is not a valid digit\n", fsm -> current);
}
