
#include "msp430.h"
#include "tpl_os.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define APP_COMMON_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(int, OS_APPL_CODE) main(void){
    P1DIR |= BIT0 + BIT2 + BIT4 + BIT5;
    P1OUT &= ~(BIT0 + BIT2 + BIT4 + BIT5);
    P3DIR = 0xFF;
    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
	StartResurrect(OSDEFAULTAPPMODE);
    return 0;
}

FUNC(int, OS_APPL_CODE) restart_main(void){
    P1DIR |= BIT0 + BIT2 + BIT4 + BIT5;
    P1OUT &= ~(BIT0 + BIT2 + BIT4 + BIT5);
    P3DIR = 0xFF;
    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
    P1OUT |= BIT5;
    RestartOS();
    return 0;
}


void main_main(void){
    return;
}

#define APP_COMMON_STOP_SEC_CODE
#include "tpl_memmap.h"




#define APP_Task_blink_START_SEC_CODE
#include "tpl_memmap.h"
TASK(blink){
    P1OUT ^= BIT0;
    TerminateTask();
}
#define APP_Task_blink_STOP_SEC_CODE
#include "tpl_memmap.h"


#define APP_Task_blink2_START_SEC_CODE
#include "tpl_memmap.h"
TASK(blink2){
    P1OUT ^= BIT2;
    TerminateTask();
}
#define APP_Task_blink2_STOP_SEC_CODE
#include "tpl_memmap.h"