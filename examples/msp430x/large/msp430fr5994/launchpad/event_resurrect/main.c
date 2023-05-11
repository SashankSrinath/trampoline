
#include "msp430.h"
#include "tpl_os.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define APP_COMMON_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(int, OS_APPL_CODE) main(void){
    P1DIR |= BIT0 + BIT1 + BIT4 + BIT5;
    P1OUT &= ~(BIT0 + BIT1 + BIT4 + BIT5);
    P3DIR = 0xFF;

    /* Button S1 and S2 */
    P5DIR &= ~(BIT5);
    P5REN |= BIT5;
    P5OUT |= BIT5;
    P5IES |= BIT5;
    P5IE |= BIT5;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;
	StartResurrect(OSDEFAULTAPPMODE);
    return 0;
}

FUNC(int, OS_APPL_CODE) restart_main(void){
    P1DIR |= BIT0 + BIT1 + BIT4 + BIT5;
    P1OUT &= ~(BIT0 + BIT1 + BIT4 + BIT5);
    P3DIR = 0xFF;

    /* Button S1 and S2 */
    P5DIR &= ~(BIT5);
    P5REN |= BIT5;
    P5OUT |= BIT5;
    P5IES |= BIT5;
    P5IE |= BIT5;

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

void green(void){
    P1OUT ^= BIT1;
    return;
}

void red(void){
    P1OUT ^= BIT0;
    return;
}
#define APP_COMMON_STOP_SEC_CODE
#include "tpl_memmap.h"


// #define APP_ISR_buttonS1_START_SEC_CODE
// #include "tpl_memmap.h"

// ISR(buttonS1){
//     tpl_set_event_resurrect_service(button);
//     // SetEventResurrect(button);
// }

// #define APP_ISR_buttonS1_STOP_SEC_CODE
// #include "tpl_memmap.h"

#define APP_ISR_buttonS2_START_SEC_CODE
#include "tpl_memmap.h"

ISR(buttonS2){
    tpl_set_event_resurrect_service(button2);
    // SetEventResurrect(button2);
}

#define APP_ISR_buttonS2_STOP_SEC_CODE
#include "tpl_memmap.h"