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
static CONST(uint16,OS_CONST) lookup_time[21][21] ={{0,424,212,141,106,84,70,60,53,47,42,38,35,32,30,28,26,24,23,22,21},
                                                    {0,0,405,202,135,101,81,67,57,50,45,40,36,33,31,28,27,25,23,22,21},
                                                    {0,0,0,386,193,128,96,77,64,55,48,42,38,35,32,29,27,25,24,22,21},
                                                    {0,0,0,0,368,184,122,92,73,61,52,46,40,36,33,30,28,26,24,23,21},
                                                    {0,0,0,0,0,350,175,116,87,70,58,50,43,38,35,31,29,26,25,23,21},
                                                    {0,0,0,0,0,0,333,166,111,83,66,55,47,41,37,33,30,27,25,23,22},
                                                    {0,0,0,0,0,0,0,316,158,105,79,63,52,45,39,35,31,28,26,24,22},
                                                    {0,0,0,0,0,0,0,0,299,149,99,74,59,49,42,37,33,29,27,24,23},
                                                    {0,0,0,0,0,0,0,0,0,283,141,94,70,56,47,40,35,31,28,25,23},
                                                    {0,0,0,0,0,0,0,0,0,0,268,134,89,67,53,44,38,33,29,26,24},
                                                    {0,0,0,0,0,0,0,0,0,0,0,252,126,84,63,50,42,36,31,28,25},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,237,118,79,59,47,39,33,29,26},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,222,111,74,55,44,37,31,27},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,208,104,69,52,41,34,29},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,194,97,64,48,38,32},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,180,90,60,45,36},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,166,83,55,41},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,153,76,51},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,140,70},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127},
                                                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
#define OS_STOP_SEC_CONST_16BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE) tpl_hibernate_os_service(void);

FUNC(void, OS_CODE) tpl_restart_os_service(void);

FUNC(void, OS_CODE) tpl_chkpt_hibernate(void);

FUNC(void, OS_CODE) get_voltage_measurement(void);

FUNC(uint16, OS_CODE) make_prediction(void);

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* TPL_OS_CHECKPOINT_H */
#endif
/* End of file tpl_os_checkpoint_kernel.h */
