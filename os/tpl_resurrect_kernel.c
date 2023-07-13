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

#include "tpl_resurrect_kernel.h"
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

#if WITH_RESURRECT == YES
#include "tpl_resurrect_kernel.h"

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
STATIC VAR(tpl_application_mode, OS_VAR) application_mode_step = NOAPPMODE;
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_VAR_NON_VOLATILE_16BIT
#include "tpl_memmap.h"
extern VAR (uint16,OS_VAR) voltage_measurement[2];
VAR(uint16_t, AUTOMATIC) result_adc=0;
#define OS_STOP_SEC_VAR_NON_VOLATILE_16BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"


FUNC(void, OS_CODE)
tpl_init_resurrect_os(CONST(tpl_application_mode, AUTOMATIC) app_mode)
{
  GET_CURRENT_CORE_ID(core_id);
  VAR(uint16, AUTOMATIC) i;
  VAR(tpl_status, AUTOMATIC) result = E_OK;
  /*  Start the idle task */
#if NUMBER_OF_CORES == 1
  result = tpl_activate_task(IDLE_TASK_ID);
#else
  result = tpl_activate_task(IDLE_TASK_0_ID + tpl_get_core_id());
#endif

  /*  Init the Ioc's unqueued buffer */
#if ((WITH_IOC == YES) && (IOC_UNQUEUED_COUNT > 0))
  {
    tpl_ioc_init_unqueued();
  }
#endif

//   /* Get energy level from ADC */
//   bool use1V2Ref = true;
//   tpl_adc_init_simple(use1V2Ref);
//   /* Polling */
//   uint16_t energy = readPowerVoltage_simple();
//   uint16_t voltageInMillis;
//   if(energy == 0x0FFF){
//     use1V2Ref = false;
//     tpl_adc_init_simple(use1V2Ref);
//     energy = readPowerVoltage_simple();
//     voltageInMillis = energy;
//   }
//   else{
//     voltageInMillis = energy*3/5;
//   }
//   // end_adc();

//   /* Compare energy level with energy from steps with FROM_STATE =
//    * tpl_kern_resurrect->state */
//   CONSTP2CONST(tpl_step_ref, AUTOMATIC, OS_VAR)
//   ptr_state = tpl_step_state[tpl_kern_resurrect.state];
//   for (i = 0; i < ENERGY_LEVEL_COUNT; i++)
//   {
//     CONSTP2CONST(tpl_step, AUTOMATIC, OS_VAR) ptr_step = ptr_state[i];
//     if (voltageInMillis >= ptr_step->energy)
//     {
//       tpl_kern_resurrect.elected =
//           (CONSTP2VAR(tpl_step, AUTOMATIC, OS_VAR))ptr_step;
//       break;
//     }
//   }

//   /* Point the entry point of a the task to the right function */

//   CONSTP2VAR(tpl_proc, AUTOMATIC, OS_VAR) resurrect_proc = tpl_dyn_proc_table[RESURRECT_TASK_ID];
//   resurrect_proc->entry = (tpl_proc_function)tpl_kern_resurrect.elected->entry_point;
// //   resurrect_proc->entry = ptr_step->entry_point;

//   /* Acitvate the resurrect task */
//   tpl_activate_task(RESURRECT_TASK_ID);

//   /* Update tpl_kern_resurrect.state with next state from step elected */
//   tpl_kern_resurrect.state = tpl_kern_resurrect.elected->to_state;

  tpl_choose_next_step();

}

FUNC(void, OS_CODE)
tpl_start_os_resurrect_service(CONST(tpl_application_mode, AUTOMATIC) mode)
{
  GET_CURRENT_CORE_ID(core_id)
  tpl_init_machine();
#if WITH_MODULES_INIT == YES
  tpl_init_modules();
#endif
#if (WITH_ERROR_HOOK == YES) || (WITH_OS_EXTENDED == YES) | (WITH_ORTI == YES)
  /*  init the error to no error  */
  VAR(tpl_status, AUTOMATIC) result = E_OK;
#endif
  /*  lock the kernel    */
  LOCK_KERNEL()

  /*  store information for error hook routine    */
  STORE_SERVICE(OSServiceId_StartResurrect)
  STORE_MODE(mode)

  CHECK_OS_NOT_STARTED(core_id, result)

  IF_NO_EXTENDED_ERROR(result)
  {
    application_mode_step = mode;

    tpl_init_resurrect_os(mode);

    tpl_enable_counters();

    /*
     * Call the startup hook. According to the spec, it should be called
     * after the os is initialized and before the scheduler is running
     */
    CALL_STARTUP_HOOK()

    /*
     * Call the OS Application startup hooks if needed
     */
    CALL_OSAPPLICATION_STARTUP_HOOKS()

    /*
     * Call tpl_start_scheduling to elect the highest priority task
     * if such a task exists.
     */

    tpl_start_scheduling(CORE_ID_OR_NOTHING(core_id));

    SWITCH_CONTEXT_NOSAVE(core_id)
  }

  PROCESS_ERROR(result)

  /*  unlock the kernel  */
  UNLOCK_KERNEL()
}

FUNC(void, OS_CODE) tpl_choose_next_step(void){
    VAR(StatusType, AUTOMATIC) result = E_OK;

    VAR(uint16, AUTOMATIC) i;
    CONSTP2CONST(tpl_step_ref, AUTOMATIC, OS_VAR)
    ptr_state = tpl_step_state[tpl_kern_resurrect.state];
    P2VAR(tpl_step, AUTOMATIC, OS_VAR) ptr_step = NULL;
    P2VAR(tpl_step, AUTOMATIC, OS_VAR) tmp_ptr_step = NULL;

    P2VAR(uint16_t, AUTOMATIC, OS_VAR) result_adc_adc = &result_adc;
    while (ptr_step == NULL)
    {
      P1OUT |= BIT2;
      /* Get energy level from ADC */
      bool use1V2Ref = true;
      tpl_adc_init_simple(use1V2Ref, result_adc_adc);
      /* Polling */
      readPowerVoltage_simple();
      // uint16_t energy = (~result_adc)+1;
      uint16_t energy = result_adc;
      uint16_t voltageInMillis;
      if(energy == 0x0FFF){ // 12 bit ADC, Can read upto 1111 1111 1111. Setting use1V2ref to 
                            // True means when the value is 0xFFF, we have 1.2ref. So the 
                            // actual value is 2.4
        use1V2Ref = false;
        tpl_adc_init_simple(use1V2Ref, result_adc_adc);
        readPowerVoltage_simple();
        // energy = (~result_adc)+1;
        energy = result_adc;
        voltageInMillis = energy;
        voltage_measurement[0] = voltageInMillis;

      }
      else{
        voltageInMillis = energy*3/5; // Conversion from energy to volts 
        voltage_measurement[0] = voltageInMillis;
      }

      for (i = 0; i < ENERGY_LEVEL_COUNT; i++)
      {//P2VAR is pointer to variable
        tmp_ptr_step = (P2VAR(tpl_step, AUTOMATIC, OS_VAR))ptr_state[i]; 
        if (voltageInMillis >= tmp_ptr_step->energy)
        {
          #if WITH_RESURRECT_EVENT == YES
          VAR(uint8, AUTOMATIC) j;
          VAR(uint16, AUTOMATIC) mask = 0x0001;
          for(j = 0; j < RESURRECT_EVENT_COUNT; j++){
            if(((tpl_kern_resurrect.state_event & mask)>>j) == (tmp_ptr_step->resurrect_event[j])){
              mask = mask<<1;
            }
            else{
              break;
            }
            tpl_kern_resurrect.elected = tmp_ptr_step;
            ptr_step = tmp_ptr_step;
            // break;
          }
          // break;
          #else
          tpl_kern_resurrect.elected = tmp_ptr_step;
          ptr_step = tmp_ptr_step;
          break;
          #endif /* WITH_RESURRECT_EVENT */
        }
      }
      P1OUT &= ~BIT2;
      /* Not enough energy to elect next step --> hibernate */
      if (ptr_step == NULL)
      {
        tpl_chkpt_hibernate();
      }
    }

    /* Point the entry point of a the task to the right function */

    CONSTP2VAR(tpl_proc, AUTOMATIC, OS_VAR) resurrect_proc = tpl_dyn_proc_table[RESURRECT_TASK_ID];
    // tpl_proc_static *resurrect_proc = (tpl_proc_static *) the_proc;
    // CONSTP2VAR(tpl_proc_static, AUTOMATIC, OS_VAR) resurrect_proc = (CONSTP2VAR(tpl_proc_static, AUTOMATIC,OS_VAR))the_proc;
    resurrect_proc->entry = (tpl_proc_function)tpl_kern_resurrect.elected->entry_point;
    #if WITH_RESURRECT_EVENT
    /* Reset Event Resurrect */
    for(i = 0; i < RESURRECT_EVENT_COUNT; i++){
      if(tpl_kern_resurrect.elected->resurrect_event[i]==1){
        tpl_kern_resurrect.state_event &= ~(1<<i);
      }
    }
    #endif /* WITH_RESURRECT_EVENT */
    /* Activate the resurrect task */
    tpl_activate_task(RESURRECT_TASK_ID);
    /* Update tpl_kern_resurrect.state with next state from step elected */
    tpl_kern_resurrect.state = tpl_kern_resurrect.elected->to_state; 
}


FUNC(void, OS_CODE) tpl_terminate_step_resurrect_service(void){

  GET_CURRENT_CORE_ID(core_id)

  /* init the error to no error */
  VAR(StatusType, AUTOMATIC) result = E_OK;

  /* lock the kernel */
  LOCK_KERNEL()
  /* store information for error hook routine */
  STORE_SERVICE(OSServiceId_TerminateTaskSequence)
  /* check interrupts are not disabled by user */
  CHECK_INTERRUPT_LOCK(result)
  /* check we are at the task level */
  CHECK_TASK_CALL_LEVEL_ERROR(core_id, result)
  /* check the task does not own a ressource */
  CHECK_RUNNING_OWNS_REZ_ERROR(core_id, result)
  /* check the task does not occupy spinlock(s) */
  CHECK_SCHEDULE_WHILE_OCCUPED_SPINLOCK(core_id, result)

#if TASK_COUNT > 0
  IF_NO_EXTENDED_ERROR(result){
    /* the activate count is decreased */
    TPL_KERN(core_id).running->activate_count--;
    /* terminate the running task */
    tpl_terminate();
    /* task switching should occur */
    TPL_KERN(core_id).need_switch = NEED_SWITCH;
  }
#endif

  /* unlock kernel */
  UNLOCK_KERNEL()
  
  tpl_choose_next_step();

  /* start the highest priority process */
  tpl_start(CORE_ID_OR_NOTHING(core_id));
  SWITCH_CONTEXT_NOSAVE(CORE_ID_OR_NOTHING(core_id))

  PROCESS_ERROR(result)
  return;
}


FUNC(void, OS_CODE) tpl_set_activation_alarm_service(CONST(tpl_alarm_id, AUTOMATIC)  alarm_id, VAR(int, AUTOMATIC) set_nb_activation){
  #if ALARM_COUNT > 0
    P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) alarm;
    alarm = tpl_alarm_table[alarm_id];
    alarm->nb_iteration = set_nb_activation;
  #endif

  return;
}
// #if WITH_RESURRECT_EVENT == YES
// FUNC(void, OS_CODE) tpl_set_event_resurrect_service(
//   CONST(EventResurrectType, AUTOMATIC) event_resurrect){

//     tpl_kern_resurrect.state_event |= 1<<event_resurrect;

//     return;
// }

// #endif // WITH_RESURRECT_EVENT

#endif // WITH_RESURRECT