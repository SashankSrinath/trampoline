#include "tpl_os.h"
#include "msp430.h"
#include <stdint.h>
#define APP_COMMON_START_SEC_CODE
#include "tpl_memmap.h"


FUNC(void, OS_APPL_CODE) io_init()
{
  	//set GPIO P1.1 (LED2) as an output
    P1DIR = 0xFF;
    P3DIR = 0xFF;
    
    P1OUT &= ~(BIT0 + BIT1);
    P3OUT &= ~BIT0;     // Set GPIO P3.0 as output (transistor switch)

	// Disable the GPIO power-on default high-impedance mode
	// to activate previously configured port settings
	PM5CTL0 &= ~LOCKLPM5;
    
    // tpl_serial_begin(SERIAL_TX_MODE_BLOCK);
}

FUNC(int, OS_APPL_CODE) main(void)
{
    io_init();
    // tpl_serial_print_string("main\n");
    // tpl_serial_tx_fifo_flush();
    __bic_SR_register(GIE);
	StartResurrect(OSDEFAULTAPPMODE);
	return 0;
}

FUNC(int, OS_APPL_CODE) restart_main(void)
{
    io_init();
    // tpl_serial_print_string("restart_main\n");
    // tpl_serial_tx_fifo_flush();
    RestartOS();
    return 0;
}


FUNC(void, OS_APPL_CODE) transistor_on(void){
	
    P1OUT |= BIT0;
    P3OUT |= BIT0; // Switch on the transistor for a duration to drain the capac
    for (volatile uint32_t i = 0; i < 400000; i++);

    return;
}

#define APP_COMMON_STOP_SEC_CODE
#include "tpl_memmap.h"

#define APP_ISR_adc_sampling_START_SEC_CODE
#include "tpl_memmap.h"

ISR(adc_sampling)
{

}

#define APP_ISR_adc_sampling_STOP_SEC_CODE
#include "tpl_memmap.h"