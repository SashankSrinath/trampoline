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

#ifndef TPL_OS_SEQUENCE_H
#define TPL_OS_SEQUENCE_H

#include "tpl_compiler.h"
#include "tpl_os_internal_types.h"

struct TPL_SEQUENCE_ALARM
{
  CONST(uint8, TYPEDEF) al_id;
  VAR(uint32, TYPEDEF) al_alarmTime;
  VAR(uint32, TYPEDEF) al_cycleTime;
  VAR(uint32, TYPEDEF) al_nbActivation;
  CONST(uint32, TYPEDEF) al_nbActivationReset;
};

typedef struct TPL_SEQUENCE_ALARM tpl_sequence_alarm;

struct TPL_SEQUENCE
{
  CONST(uint32, TYPEDEF) energy;
  CONST(uint8, TYPEDEF) to_state;
  CONST(uint8, TYPEDEF) from_state;
  CONST(uint8, TYPEDEF) nb_task;
  VAR(uint16, TYPEDEF) mask_seq_terminate;
  CONST(uint16, TYPEDEF) vec_seq_terminate;
  CONST(uint8, TYPEDEF) * seqTaskTab;
  CONST(uint8, TYPEDEF) nb_alarm;
  VAR(tpl_sequence_alarm, TYPEDEF) * seqAlarmTab;
};

typedef struct TPL_SEQUENCE tpl_sequence;
typedef tpl_sequence *tpl_sequence_ref;

typedef struct
{
  P2VAR(tpl_sequence, TYPEDEF, OS_VAR) elected;
  VAR(sint32, TYPEDEF) state;
} tpl_kern_seq_state;

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

extern VAR(tpl_kern_seq_state, OS_VAR) tpl_kern_seq;

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

extern CONSTP2CONST(tpl_sequence_ref, AUTOMATIC,
                    OS_APPL_DATA) tpl_sequence_state[STATE_COUNT];

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE)
tpl_start_os_sequence_service(CONST(tpl_application_mode, AUTOMATIC) mode);

FUNC(void, OS_CODE) tpl_terminate_task_sequence_service(void);

FUNC(void, OS_CODE) tpl_choose_next_sequence(void);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* TPL_OS_SEQUENCE_H */
#endif
/* End of file tpl_sequence_kernel.h */