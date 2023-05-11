/**
 * @file tpl_resurrect_kernel.c
 *
 * @section descr File description
 *
 * Trampoline sequence os services implementation.
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

#include "tpl_resurrect_event_kernel.h"
#include "tpl_chkpt_checkpoint_kernel.h"
#include "tpl_machine_interface.h"
#include "tpl_os_alarm_kernel.h"
#include "tpl_os_definitions.h"
#include "tpl_os_error.h"
#include "tpl_os_hooks.h"
#include "tpl_os_kernel.h"
#include "tpl_os_os_kernel.h"
#include "tpl_trace.h"

#include "msp430.h"

#include "tpl_chkpt_adc.h"

#include <stdint.h>

#if WITH_RESURRECT_EVENT == YES
FUNC(void, OS_CODE) tpl_set_event_resurrect_service(
  CONST(EventResurrectType, AUTOMATIC) event_resurrect){

    tpl_kern_resurrect.state_event |= 1<<event_resurrect;

    return;
}

#endif // WITH_RESURRECT_EVENT
