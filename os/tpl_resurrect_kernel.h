/**
 * @file tpl_sequence_kernel.h
 *
 * @section descr File description
 *
 * Trampoline sequence os services header.
 *
 * @section copyright Copyright
 *
 * Trampoline RTOS
 *
 * Trampoline is copyright (c) CNRS, University of Nantes, Ecole Centrale de
 * Nantes Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the GNU Public Licence V2.
 * Check the LICENSE file in the root directory of Trampoline
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 *
 */

#ifndef TPL_OS_RESURRECT_H
#define TPL_OS_RESURRECT_H

#include "tpl_compiler.h"
#include "tpl_os_internal_types.h"
#include "tpl_os_kernel.h"
#include <stdint.h>
/**
 * @typedef EventResurrectType
 *
 * identifies an event for resurrect
 *
 */
typedef uint16 tpl_event_resurrect;

typedef tpl_event_resurrect  EventResurrectType;

typedef int NumberActivationType;

struct TPL_STEP
{
  CONST(uint32, TYPEDEF) energy;
  CONST(uint8, TYPEDEF) to_state;
  CONST(uint8, TYPEDEF) from_state;
  CONST(tpl_proc_function, TYPEDEF) entry_point;
  #if WITH_RESURRECT_EVENT == YES
  CONST(EventResurrectType, TYPEDEF) resurrect_event[RESURRECT_EVENT_COUNT];
  #endif /* WITH_RESURRECT_EVENT */
};

typedef struct TPL_STEP tpl_step;
typedef tpl_step *tpl_step_ref;

typedef struct
{
  P2VAR(tpl_step, TYPEDEF, OS_VAR) elected;
  VAR(sint32, TYPEDEF) state;
  #if WITH_RESURRECT_EVENT == YES
  VAR(uint16, TYPEDEF) state_event;
  #endif /* WITH_RESURRECT_EVENT */
} tpl_kern_resurrect_state;

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

extern VAR(tpl_kern_resurrect_state, OS_VAR) tpl_kern_resurrect;

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

extern CONSTP2CONST(tpl_step_ref, AUTOMATIC,
                    OS_APPL_DATA) tpl_step_state[RESURRECT_STATE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_NON_VOLATILE_16BIT
#include "tpl_memmap.h"
extern VAR(uint16_t, AUTOMATIC) result_adc;
#define OS_STOP_SEC_VAR_NON_VOLATILE_16BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE)
tpl_start_os_resurrect_service(CONST(tpl_application_mode, AUTOMATIC) mode);

FUNC(void, OS_CODE) tpl_terminate_step_resurrect_service(void);

FUNC(void, OS_CODE) tpl_choose_next_step(void);

FUNC(void, OS_CODE) tpl_set_activation_alarm_service(CONST(tpl_alarm_id, AUTOMATIC)  alarm_id, VAR(int, AUTOMATIC) set_nb_activation);

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* TPL_OS_RESURRECT_H */
#endif
/* End of file tpl_resurrect_kernel.h */