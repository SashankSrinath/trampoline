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
static CONST(uint16,OS_CONST) lookup_time[528] = {1335, 667, 445, 333, 267, 222, 190, 166, 148, 133, 121, 111, 102, 95, 89, 83, 78, 74, 70, 66, 63, 60, 58, 55, 53, 51, 49, 47, 46, 44, 43, 41, 1296, 648, 432, 324, 259, 216, 185, 162, 144, 129, 117, 108, 99, 92, 86, 81, 76, 72, 68, 64, 61, 58, 56, 54, 51, 49, 48, 46, 44, 43, 41, 1258, 629, 419, 314, 251, 209, 179, 157, 139, 125, 114, 104, 96, 89, 83, 78, 74, 69, 66, 62, 59, 57, 54, 52, 50, 48, 46, 44, 43, 41, 1221, 610, 407, 305, 244, 203, 174, 152, 135, 122, 111, 101, 93, 87, 81, 76, 71, 67, 64, 61, 58, 55, 53, 50, 48, 46, 45, 43, 42, 1184, 592, 394, 296, 236, 197, 169, 148, 131, 118, 107, 98, 91, 84, 78, 74, 69, 65, 62, 59, 56, 53, 51, 49, 47, 45, 43, 42, 1148, 574, 382, 287, 229, 191, 164, 143, 127, 114, 104, 95, 88, 82, 76, 71, 67, 63, 60, 57, 54, 52, 49, 47, 45, 44, 42, 1113, 556, 371, 278, 222, 185, 159, 139, 123, 111, 101, 92, 85, 79, 74, 69, 65, 61, 58, 55, 53, 50, 48, 46, 44, 42, 1078, 539, 359, 269, 215, 179, 154, 134, 119, 107, 98, 89, 82, 77, 71, 67, 63, 59, 56, 53, 51, 49, 46, 44, 43, 1043, 521, 347, 260, 208, 173, 149, 130, 115, 104, 94, 86, 80, 74, 69, 65, 61, 57, 54, 52, 49, 47, 45, 43, 1009, 504, 336, 252, 201, 168, 144, 126, 112, 100, 91, 84, 77, 72, 67, 63, 59, 56, 53, 50, 48, 45, 43, 976, 488, 325, 244, 195, 162, 139, 122, 108, 97, 88, 81, 75, 69, 65, 61, 57, 54, 51, 48, 46, 44, 943, 471, 314, 235, 188, 157, 134, 117, 104, 94, 85, 78, 72, 67, 62, 58, 55, 52, 49, 47, 44, 910, 455, 303, 227, 182, 151, 130, 113, 101, 91, 82, 75, 70, 65, 60, 56, 53, 50, 47, 45, 879, 439, 293, 219, 175, 146, 125, 109, 97, 87, 79, 73, 67, 62, 58, 54, 51, 48, 46, 847, 423, 282, 211, 169, 141, 121, 105, 94, 84, 77, 70, 65, 60, 56, 52, 49, 47, 816, 408, 272, 204, 163, 136, 116, 102, 90, 81, 74, 68, 62, 58, 54, 51, 48, 785, 392, 261, 196, 157, 130, 112, 98, 87, 78, 71, 65, 60, 56, 52, 49, 755, 377, 251, 188, 151, 125, 107, 94, 83, 75, 68, 62, 58, 53, 50, 725, 362, 241, 181, 145, 120, 103, 90, 80, 72, 65, 60, 55, 51, 696, 348, 232, 174, 139, 116, 99, 87, 77, 69, 63, 58, 53, 667, 333, 222, 166, 133, 111, 95, 83, 74, 66, 60, 55, 639, 319, 213, 159, 127, 106, 91, 79, 71, 63, 58, 610, 305, 203, 152, 122, 101, 87, 76, 67, 61, 582, 291, 194, 145, 116, 97, 83, 72, 64, 555, 277, 185, 138, 111, 92, 79, 69, 528, 264, 176, 132, 105, 88, 75, 501, 250, 167, 125, 100, 83, 474, 237, 158, 118, 94, 448, 224, 149, 112, 422, 211, 140, 397, 198, 371};
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

FUNC(uint16, OS_CODE) linear_prediction(uint16);

FUNC(uint16, OS_CODE) approx_prediction(uint16);

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* TPL_OS_CHECKPOINT_H */
#endif
/* End of file tpl_os_checkpoint_kernel.h */
