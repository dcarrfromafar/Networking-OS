
#include "statemodel.h"

bool debug = false;

/* Frees up dynamically allocated data inside the FSM as needed. */
void
free_fsm (fsm_t *fsm)
{
}

/* Handles events by calling the transition function inside the FSM.
   Should be called by specific functions such as string_event(),
   integer_event(), value_event(), and object_event(). */
void
handle_event (fsm_t *fsm, event_t event)
{
}
