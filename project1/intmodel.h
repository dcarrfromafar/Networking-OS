#ifndef __integermodel_h__
#define __integermodel_h__

#include "statemodel.h"

static void SetNegative(fsm_t *fsm);
static void SetMultiplier_10(fsm_t *fsm);
static void MultAndAdd(fsm_t *fsm);
static void SetMultiplier_8(fsm_t *fsm);
static void SyntaxError(fsm_t *fsm);
void integer_event (fsm_t *fsm, intevt_t event);
bool initialize_int_fsm (fsm_t *fsm);

#endif
