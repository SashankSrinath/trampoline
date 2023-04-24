/**
 * @file tpl_os_checkpoint_kernel.h
 *
 * @section descr File description
 *
 * Trampoline checkpointing os services header.
 *
 * @section copyright Copyright
 *
 * Trampoline RTOS
 *
 * Trampoline is copyright (c) CNRS, University of Nantes, Ecole Centrale de Nantes
 * Trampoline is protected by the French intellectual property law.
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

#ifndef TPL_OS_CHECKPOINT_H
#define TPL_OS_CHECKPOINT_H

#include "tpl_os_kernel.h"

extern void tpl_save_checkpoint_dma(const uint16 buffer);
extern void tpl_load_checkpoint_dma(const uint16 buffer);

extern void tpl_save_checkpoint(void);
extern void tpl_load_checkpoint(void);

#define OS_START_SEC_CONST_16BIT
#include "tpl_memmap.h"
static CONST (sint16,OS_CONST) NO_CHECKPOINT = -1;
#define OS_STOP_SEC_CONST_16BIT
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_NON_VOLATILE_16BIT
#include "tpl_memmap.h"
extern VAR (sint16,OS_VAR) tpl_checkpoint_buffer;
#define OS_STOP_SEC_VAR_NON_VOLATILE_16BIT
#include "tpl_memmap.h"

// Following lookup table calculated based on simulator experiments - exponential extrapolation 
#define OS_START_SEC_CONST_16BIT
#include "tpl_memmap.h"
static CONST(uint16,OS_CONST) lookup_time[17][17] ={{0,333,166,111,83,66,55,47,41,37,33,30,27,25,23,22,20},
                                                    {0,0,314,157,104,78,62,52,44,39,34,31,28,26,24,22,20},
                                                    {0,0,0,296,148,98,74,59,49,42,37,32,29,26,24,22,21},
                                                    {0,0,0,0,278,139,92,69,55,46,39,34,30,27,25,23,21},
                                                    {0,0,0,0,0,260,130,86,65,52,43,37,32,28,26,23,21},
                                                    {0,0,0,0,0,0,244,122,81,61,48,40,34,30,27,24,22},
                                                    {0,0,0,0,0,0,0,227,113,75,56,45,37,32,28,25,22},
                                                    {0,0,0,0,0,0,0,0,211,105,70,52,42,35,30,26,23},
                                                    {0,0,0,0,0,0,0,0,0,196,98,65,49,39,32,28,24},
                                                    {0,0,0,0,0,0,0,0,0,0,181,90,60,45,36,30,25},
                                                    {0,0,0,0,0,0,0,0,0,0,0,166,83,55,41,33,27},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,152,76,50,38,30},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,138,69,46,34},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,125,62,41},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,56},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,99},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
#define OS_STOP_SEC_CONST_16BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE) tpl_hibernate_os_service(void);

FUNC(void, OS_CODE) tpl_restart_os_service(void);

FUNC(void, OS_CODE) tpl_chkpt_hibernate(void);

FUNC(void, OS_CODE) get_voltage_measurement(void);

FUNC(uint16, OS_CODE) make_prediction(void);

FUNC(uint16, OS_CODE) calculate_prediction(uint16);

FUNC(uint16, OS_CODE) approx_prediction(uint16);

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* TPL_OS_CHECKPOINT_H */
#endif
/* End of file tpl_os_checkpoint_kernel.h */
