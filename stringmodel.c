#include <stdbool.h>

#include "statemodel.h"
#include "stringmodel.h"

static void AdvancePointer (fsm_t *);
static void AllocateBuffer (fsm_t *);
static void AppendCharacter (fsm_t *);
static void ReplaceCharacter (fsm_t *);
static void SyntaxError (fsm_t *);
static state_t transition (fsm_t *, event_t, action_t *, action_t *);

// HINT: The type declarations in statemodel.h include
// unions. See https://www.learn-c.org/en/Unions for an
// introduction to unions. This example shows how
// to set up your transition table, much like Assignment 2:

static strst_t const transitions[NSTR_STATES][NSTR_EVENTS] = {
// OPEN_QUOTE  BACKSLAH  ESC_CHAR  NON_CTRL  CLOSE_QUOTE  NO_ESC     NIL_CHAR
	{ BUILDING,  NON_STR,  NON_STR,  NON_STR,  NON_STR,     NON_STR,   NON_STR},  // STR_INIT	
  { NON_STR,   ESCAPE,   NON_STR,  BUILDING, STR_FINISH,  NON_STR,   NON_STR},  // BUILDING
  { NON_STR,   NON_STR,  BUILDING, NON_STR,  ESCAPE,      STR_ERROR, NON_STR},  // ESCAPE
  { NON_STR,   NON_STR,  NON_STR,  BUILDING, NON_STR,     NON_STR,   NON_STR}, // STR_FINISH
  { NON_STR,   NON_STR,  NON_STR,  BUILDING, NON_STR,     NON_STR,   NON_STR}  // STR_ERROR
};

// Then create a table of effect functions.
static strst_t const effects[NSTR_STATES][NSTR_EVENTS] = {
// OPEN_QUOTE       BACKSLAH  ESC_CHAR          NON_CTRL         CLOSE_QUOTE      NO_ESC       NIL_CHAR
	{ AllocateBuffer, NULL,     NULL,             NULL,            NULL,            NULL,        NULL}, // STR_INIT	
  { NULL,           NULL,     NULL,             AppendCharacter, AdvancePointer,  NULL,        NULL}, // BUILDING
  { NULL,           NULL,     ReplaceCharacter, NULL,            NULL,            SyntaxError, NULL}, // ESCAPE
  { NULL,           NULL,     NULL,             NULL,            NULL,            NULL,        NULL}, // STR FINISH
  { NULL,           NULL,     NULL,             NULL,            NULL,            NULL,        NULL}  // STR_ERROR
};

// Finally, create an array of entry functions.
static action_t const entries[NSTR_STATES] = {
  NULL, NULL, NULL, NULL, NULL
};

bool
initialize_str_fsm (fsm_t *fsm)
{
  // Note that, when setting other fields in the struct,
  // you will need to add .string to the end of the field name
  // because of the union types. For instance, you can set the
  // maximum valid event for this FSM as:

  // fsm->max_valid_event.string = NIL_CHAR;
  
  if(fsm == NULL)
  {
  	return false;
  }
  
  fsm -> type = STRING;
  fsm -> state.string = STR_INIT;
  fsm -> max_valid_event.string = NIL_CHAR;
  fsm -> max_valid_state.string = NON_STR;
  fsm -> transition = transition;
  return true;
}

/* String version of the handle_event function */
void
string_event (fsm_t *fsm, strevt_t event)
{
  // Declare an event_t, put event in it, and call handle_event().
  event_t ev;
  ev.string = event;
  handle_event(fsm, ev);
}

/* String version of the transition function */
static state_t
transition (fsm_t *fsm, event_t event, action_t *effect, action_t *entry)
{
  state_t next;

  // Strings that are helpful for debugging
  // static const char * event_names[]
  //     = { "OPEN_QUOTE", "CLOSE_QUOTE", "NON_CTRL",
  //         "BACKSLASH", "ESC_CHAR", "NO_ESC", "NIL_CHAR" };
  // static const char *state_names[]
  //     = { "STR_INIT", "BUILDING", "ESCAPE", "STR_FINISH",
  //         "STR_ERROR", "NON_STR" };

	if(fsm -> state <= NON_STR && event <= NIL_CHAR)
	{
		next = transitions[fsm->state][event];
		*entry = entries[next];
		*effect = effects[fsm->state][event];
		return next;
	}
	return NON_STR;
}

// /////////////////// EFFECT FUNCTIONS ////////////////////

/* Used to move beyond the quote at the end of the string */
static void
AdvancePointer (fsm_t *fsm)
{
	fsm -> current = fsm->input[fsm->inputIndex++];
}

/* Create a dynamically allocated buffer for storing the string as it is
   being built. Note that you will need to modify the fsm_t struct declaration
   to include whatever fields you may need for managing the buffer. */
static void
AllocateBuffer (fsm_t *fsm)
{
	fsm -> buffPtr = (char*) malloc(sizeof(char) * strlen(fsm -> input)+1);
}

/* Append a character from the current string to a buffer */
static void
AppendCharacter (fsm_t *fsm)
{
	fsm -> buffPtr[fsm->buffIndex++] += fsm -> current;
}

/* Replaces a control sequence (\\ or \") by putting just the
   latter character into the buffer */
static void
ReplaceCharacter (fsm_t *fsm)
{
	if(fsm -> current == '\\')
	{
		advancePointer(fsm);
		
		if(fsm -> current == '\\' || fsm -> current == '"')
		{
			fsm -> buffPtr[fsm->buffIndex++] = fsm->current;
		}
		else
		{
			SyntaxError(fsm);
		}
	}
}

/* Reports an invalid escape-code character */
static void
SyntaxError (fsm_t *fsm)
{
  printf ("SYNTAX ERROR: '%c%c' is not a valid escape code\n", fsm->current);
}
