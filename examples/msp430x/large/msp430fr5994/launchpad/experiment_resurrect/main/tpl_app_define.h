/**
 * @file tpl_app_define.h
 *
 * @section desc File description
 *
 * Header of the automatic generated defines usable
 * by the application base
 * Automatically generated by goil on Wed Jul 19 10:15:36 2023
 * from root OIL file main.oil
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2010
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#ifndef TPL_APP_DEFINE_H
#define TPL_APP_DEFINE_H



#include "tpl_config_def.h"

/*=============================================================================
 * Configuration flags
 */
#define TARGET_ARCH                      "msp430x"
#define TARGET_CHIP                      "large"
#define TARGET_BOARD                     "msp430fr5994/launchpad"
#define NUMBER_OF_CORES                  1
#define WITH_OS_EXTENDED                 YES
#define WITH_ORTI                        NO
#define WITH_PAINT_STACK                 YES
#define WITH_PAINT_REGISTERS             YES
#define WITH_STARTUP_HOOK                NO
#define WITH_SHUTDOWN_HOOK               NO
#define WITH_ERROR_HOOK                  NO
#define WITH_PRE_TASK_HOOK               NO
#define WITH_POST_TASK_HOOK              NO
#define WITH_ANY_HOOK                    NO
#define WITH_PANIC_HOOK                  NO
#define WITH_USEGETSERVICEID             NO
#define WITH_USEPARAMETERACCESS          NO
#define WITH_USERESSCHEDULER             YES
#define WITH_SYSTEM_CALL                 YES
#define WITH_MEMORY_PROTECTION           NO
#define WITH_MEMMAP                      YES
#define WITH_COMPILER_SETTINGS           YES
#define WITH_AUTOSAR                     NO
#define WITH_PROTECTION_HOOK             NO
#define WITH_STACK_MONITORING            NO
#define WITH_AUTOSAR_TIMING_PROTECTION   NO
#define AUTOSAR_SC                       0
#define WITH_OSAPPLICATION               NO
#define WITH_OSAPPLICATION_STARTUP_HOOK  NO
#define WITH_OSAPPLICATION_SHUTDOWN_HOOK NO
#define WITH_TRACE                       NO
#define WITH_ID                          NO
#define WITH_IT_TABLE                    NO
#define WITH_COM                         NO
#define WITH_IOC                         NO
#define WITH_MODULES_INIT                NO
#define WITH_INIT_BOARD                  NO
#define WITH_ISR2_PRIORITY_MASKING       NO

/*=============================================================================
 * Defines related to the key part of a ready list entry.
 * The key part has in the most significant bits the priority of the job and
 * in the least significant bits the rank of the job. So:
 * - PRIORITY_SHIFT is the number of bit the key has to be shifted to the
 *   right) to get the priority only aligned to the right;
 * - PRIORITY_MASK is the mask to get the priority only (not aligned to the
 *   right with the rank set to 0;
 * - RANK_MASK is the mask to get only the rank.
 */
#define PRIORITY_SHIFT                   1
#define PRIORITY_MASK                    6
#define RANK_MASK                        1

/*=============================================================================
 * Number of objects used by the application
 * These informations are used by Trampoline to avoid to
 * alloc structures when some os objects are not present.
 */

/*-----------------------------------------------------------------------------
 * Number of priority levels
 */
#define PRIO_LEVEL_COUNT       3

/*-----------------------------------------------------------------------------
 * Number of tasks
 */
#define TASK_COUNT             1

/*-----------------------------------------------------------------------------
 * Number of spinlocks
 */
#define SPINLOCK_COUNT         0

/*-----------------------------------------------------------------------------
 * Number of extended tasks
 */
#define EXTENDED_TASK_COUNT    0

/*-----------------------------------------------------------------------------
 * Number of ISR2
 */
#define ISR_COUNT              0

/*-----------------------------------------------------------------------------
 * Number of alarms
 */
#define ALARM_COUNT            0

/*-----------------------------------------------------------------------------
 * Number of regular resources (standard and linked) plus RES_SCHEDULER if used 
 */
#define RESOURCE_COUNT         1 

/*-----------------------------------------------------------------------------
 * Number of events
 */
#define EVENT_COUNT            0

/*-----------------------------------------------------------------------------
 * Number of messages
 */
#define MESSAGE_COUNT          0

/*-----------------------------------------------------------------------------
 * Number of send messages
 */
#define SEND_MESSAGE_COUNT     0

/*-----------------------------------------------------------------------------
 * Number of receive messages
 */
#define RECEIVE_MESSAGE_COUNT  0

/*-----------------------------------------------------------------------------
 * Number of counters
 */
#define COUNTER_COUNT          1

/*-----------------------------------------------------------------------------
 * Number of schedule tables
 */
#define SCHEDTABLE_COUNT       0

/*-----------------------------------------------------------------------------
 * Number of OS Applications
 */
#define APP_COUNT              0

/*-----------------------------------------------------------------------------
 * Number of trusted functions
 */
#define TRUSTED_FCT_COUNT      0

/*-----------------------------------------------------------------------------
 * Number of IOC
 */
#define IOC_COUNT 0
#define IOC_QUEUED_COUNT 0
#define IOC_UNQUEUED_COUNT 0


/*-----------------------------------------------------------------------------
 * Priority of RES_SCHEDULER
 */
#define RES_SCHEDULER_PRIORITY 2

#define IDLE_TASK_ID    TASK_COUNT + ISR_COUNT

/*-----------------------------------------------------------------------------
 * To fasten the SPINLOCK_IS_SUCCESSOR macro
 */
#define SPINLOCK_SUCCESSOR_BITFIELD_SHIFT 4
#define SPINLOCK_SUCCESSOR_BITFIELD_MASK  7

/*-----------------------------------------------------------------------------
 * Spinlocks max possessed spinlocks per core.
 * This definition is used to maximize the size of possessed spinlocks.
 * In OSExtended mode, as we're checking nesting spinlocks, we can set the max
 * size of the LIFOS to the longest chain in the spinlocks graph.
 * In OSStandard mode, we set the maximum to the number of spinlocks (a
 * spinlock can only be taken once).
 */
#define MAX_POSSESSED_SPINLOCKS 0

/*-----------------------------------------------------------------------------
 * Debugging
 */
#define WITH_DEBUG             NO

#include "tpl_config_check.h"

#endif

/*-----------------------------------------------------------------------------
 * Configuration STM Flags
 */
#define NUMBER_OF_OBJECTS                 0
#define NUMBER_OF_TRANSACTIONS            0

/*-----------------------------------------------------------------------------
 *  Tick optimization
 */
#define TPL_OPTIMIZE_TICKS NO
/**
 * set the CPU default frequency at startup in MHz.
 * Value defined with .oil key CPU->OS->CPU_FREQ_MHZ;
 *
 * This frequency may be overriden using at runtime with
 * void tpl_set_mcu_clock(uint16_t freqInMHz);
 * (defined in tpl_clocks.h)
 */
#define CPU_FREQ_MHZ    8

/*
 * Power mode to be used in the idle task
 */
#define ACTIVE_POWER_MODE  -1
#define LPM0_POWER_MODE     0
#define LPM1_POWER_MODE     1
#define LPM2_POWER_MODE     2
#define LPM3_POWER_MODE     3

#define IDLE_POWER_MODE   ACTIVE_POWER_MODE
#define IDLE_LPM          ACTIVE

/*
 * If YES, init the .data section using the DMA
 */
#define WITH_INIT_WITH_DMA    NO

/*
 * If YES, use checkpointing with the msp430
 */
#define WITH_CHECKPOINTING    YES

#define WITH_CHECKPOINTING_STATIC     YES
#define RESUME_FROM_HIBERNATE_THRESHOLD    3000

/*
 * If YES, use lea with the msp430
 */
#define WITH_LEA             NO

/*
 * If YES, use sequence with the msp430
 */
 #define WITH_SEQUENCING    NO
 
 /*
 * If YES, use RESURRECT with the msp430
 */
 #define WITH_RESURRECT     YES

/*
 * Number of sequences
 */
#define TRANSITION_COUNT    0
#define STATE_COUNT    0

/*-----------------------------------------------------------------------------
 *  Activate or not the System counter
 */
#define WITH_SYSTICK   NO



/*
 * Number of Resurrect State
 */
#define RESURRECT_STATE_COUNT    1 
#define RESURRECT_TRANSITION_COUNT    1
#define RESURRECT_EVENT_COUNT     0

#define ENERGY_LEVEL_COUNT    1
#define RESURRECT_TASK_ID 0
#define WITH_RESURRECT_EVENT NO
/*=============================================================================
 * libraries related defines
 */

/* End of file TPL_APP_DEFINE_H */
