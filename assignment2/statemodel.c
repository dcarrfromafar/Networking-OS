#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "effects.h"
#include "statemodel.h"

// TODO: Complete this table mapping state/events to the target state
static state_t const transitions[NUMBER_OF_STATES][NUMBER_OF_EVENTS] = {
 // ADMIT  DISPATCH SCHEDULE BLOCK UNBLOCK EXIT KILL NIL
  { RDY,   NST,     NST,     NST,  NST,    NST, TRM, NST }, // NEW
  { NST,   RUN,     NST,     BLK,  NST,    NST, TRM, NST }, // READY
  { NST,   RUN,     RDY,     BLK,  NST,    TRM, NST, NST }, // RUNNING
  { NST,   NST,     NST,     NST,  RDY,    NST, TRM, NST }, // BLOCKED
  { NST,   NST,     NST,     NST,  NST,    NST, NST, NST }  // TERM
};

// TODO: Create a table of action_t mapping states/events to effect functions
//2d array of function pointers
static action_t const effects[NUMBER_OF_STATES][NUMBER_OF_EVENTS] = {
 // ADMIT       DISPATCH  SCHEDULE  BLOCK  UNBLOCK        EXIT  KILL       NIL
  { set_live,   NULL,     NULL,     NULL,  NULL,    			NULL, kill_proc, NULL }, // NEW
  { NULL,   		NULL,     NULL,     NULL,  NULL,    			NULL, kill_proc, NULL }, // READY
  { NULL,   		NULL,     NULL,     NULL,  NULL,    			NULL, NULL, 		 NULL }, // RUNNING
  { NULL,   		NULL,     NULL,     NULL,  say_unblocked, NULL, kill_proc, NULL }, // BLOCKED
  { NULL,   		NULL,     NULL,     NULL,  NULL,    			NULL, NULL, 		 NULL }  // TERM
};

// TODO: Create an array of action_t to map each state to its entry function
//array of function pointers
/* Lookup table for state entry actions */
static action_t const entries[NUMBER_OF_STATES] = {
 //NEW					 READY RUNNING			 BLOCKED	    TERM         NST	
  reset_runtime, NULL, incr_runtime, say_blocked, print_stats, NULL
};

/* Given FSM instance and event, perform the table lookups.
   Return NST if the state/event combination is bad.
   Otherwise, store the appropriate effect and entry functions
   into the pointer parameters. Return the next state. */
static state_t
transition(fsm_t *fsm, event_t event, action_t *effect, action_t *entry)
{
  if(fsm -> state <= NST && event <= NIL)
  {
  	state_t next = transitions[fsm -> state][event];
  	*entry = entries[next];
  	*effect = effects[fsm -> state][event];
  	return next;	
  }
  return NST;
}

/* Initialize FSM to contain a pointer to the transition function.
   Also set the live, runtime, and state values to defaults.
   Return true if successful. */
bool
initialize_fsm (fsm_t *fsm)
{
  if(fsm == NULL)
  {
  	return false;
  }
  fsm -> state = NEW;	
  fsm -> runtime = 0;
  fsm -> live = false;
  fsm -> transition = transition;
  return true;
}

/* Handle an event given an FSM configuration. Confirm that the event is valid.
   Call the transition function pointer stored in the FSM with appropriate
   arguments. Print information about the transition. Call effect functions and entry functions if they aren't NULL. Update the state. */
void
handle_event (fsm_t *fsm, event_t event)
{
	  static const char * event_names[] =
    { "ADMIT", "DISPATCH", "SCHEDULE", "BLOCK", "UNBLOCK", "EXIT", "KILL", "NIL" };
  static const char * state_names[] = { "NEW", "RDY", "RUN", "BLK", "TRM", "NST" };
  assert(fsm != NULL);

	action_t effect = NULL;
	action_t entry = NULL;
	state_t next = fsm -> transition(fsm, event, &effect, &entry);
	
  // TODO: Use the following format string to print the current state name,
  // state name, the event name, and the new state name for valid transitions.
	printf ("%s.%s -> %s\n", state_names[fsm -> state], event_names[event], state_names[next]);
	if(next != NST)
	{
		if(effect)
			effect(fsm);
			
		if(entry)
			entry(fsm);
			
		fsm -> state = next;		
	}
}
