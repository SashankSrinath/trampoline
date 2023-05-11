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

#ifndef TPL_OS_RESURRECT_EVENT_H
#define TPL_OS_RESURRECT_EVENT_H

#include "tpl_compiler.h"
#include "tpl_os_internal_types.h"
#include "tpl_os_kernel.h"
#include "tpl_resurrect_kernel.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE) tpl_set_event_resurrect_service(CONST(EventResurrectType, AUTOMATIC) event_resurrect);
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* TPL_OS_RESURRECT_EVENT_H */
#endif
/* End of file tpl_resurrect_event_kernel.h */