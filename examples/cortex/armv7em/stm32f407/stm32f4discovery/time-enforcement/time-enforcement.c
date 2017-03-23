#include "tp.h"
#include "tpl_os.h"
#include "tpl_os_kernel.h" /* FIXME: provides definition of tpl_kern, see below */
#include "tpl_os_time_model.h"

#define APP_Task_t_delay_START_SEC_CODE
#include "tpl_memmap.h"
FUNC(int, OS_APPL_CODE) main(void)
{
  initBoard();
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

TASK(t_delay)
{
  ledToggle(BLUE);
  TerminateTask();
}
#define APP_Task_t_delay_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_Task_t_nodelay_START_SEC_CODE
#include "tpl_memmap.h"

TASK(t_nodelay)
{
  ledToggle(RED);
  TerminateTask();
}

#define APP_Task_t_nodelay_STOP_SEC_CODE
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 *  * This is necessary for ST libraries
 *   */
FUNC(void, OS_CODE) assert_failed(uint8_t* file, uint32_t line)
{
}

FUNC(void, OS_CODE) PreUserServiceHook(uint32 serviceID) {
    /* 
     * TODO: get proc_id through parameters
     * FIXME: not functionnal w/ memory protection activated
     */
    tpl_proc_id running = tpl_kern.running_id;

    /*
     * Identify the transitions that has been taken
     */
    if (tpl_state_table[running] != NULL) {

        tpl_te_model_state current_state   = tpl_te_current_state[running];
        tpl_te_transition const * transition_set = tpl_state_table[running][current_state].transitions;
        uint8 transition_count             = tpl_state_table[running][current_state].count;

        uint8 cpt = 0;
        while 
            (
             (cpt < transition_count) 
             && (transition_set[cpt].service_id != serviceID)
            ) 
            {
                cpt++;
            }
        
        tpl_te_transition const * transition = &(transition_set[cpt]);
   
        /* Wait for eft if the transistion has been fired early */
        tpl_te_earliest_firing_time eft = transition->eft;
        tpl_wait_enforcement_timer(0, eft);

        /* Update current state */
        tpl_te_current_state[running] = transition->target_state;
    }
}

FUNC(void, OS_CODE) PostUserServiceHook(uint32 serviceID) {
    tpl_set_enforcement_timer(0);
}

FUNC(void, OS_CODE) PreTaskHook()
{
}

FUNC(void, OS_CODE) PostTaskHook()
{
}
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"