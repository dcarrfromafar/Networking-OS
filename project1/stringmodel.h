#ifndef __stringmodel_h__
#define __stringmodel_h__

#include "statemodel.h"

static void AdvancePointer (fsm_t *);
static void AllocateBuffer (fsm_t *);
static void AppendCharacter (fsm_t *);
static void ReplaceCharacter (fsm_t *);
static void SyntaxError (fsm_t *);
void string_event (fsm_t *fsm, strevt_t event);
bool initialize_str_fsm (fsm_t *fsm);

#endif
