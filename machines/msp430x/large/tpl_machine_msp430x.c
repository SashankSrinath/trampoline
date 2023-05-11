#include "tpl_machine.h"
#include "tpl_machine_interface.h"
#include "tpl_os_application_def.h"
#include "tpl_os_definitions.h"
#include "tpl_os.h"
#if WITH_MEMORY_PROTECTION == YES
	#include "tpl_memory_protection.h"
#endif
#if WITH_AUTOSAR == YES
	#include "tpl_as_definitions.h"
#endif
#include "tpl_os_interrupt.h"
#include "tpl_kern_stack.h"

#include "msp430.h"

extern FUNC(void, OS_CODE) CallTerminateTask(void);
extern FUNC(void, OS_CODE) CallTerminateISR2(void);
extern FUNC(void, OS_CODE) tpl_init_it_priority();

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

FUNC(void, OS_CODE) tpl_init_context(
  CONST(tpl_proc_id, OS_APPL_DATA) proc_id)
{
#if WITH_PAINT_REGISTERS == YES || WITH_PAINT_STACK == YES
	VAR(int, AUTOMATIC) i;
#endif

	//pointer to the static descriptor of the process
	CONSTP2CONST(tpl_proc_static, AUTOMATIC, OS_APPL_DATA) the_proc = tpl_stat_proc_table[proc_id];
	
	//pointer to the context of the process
	CONSTP2VAR(msp430x_core_context, AUTOMATIC, OS_APPL_DATA) l_tpl_context = the_proc->context;
	
	//pointer to the stack of the process
	CONSTP2VAR(tpl_stack_word, AUTOMATIC, OS_APPL_DATA) stack = the_proc->stack.stack_zone;
	
	//size of the stack in 16 bit words above the exceptionf rame
	CONST(uint16, AUTOMATIC) size_of_stack_above_exception_frame = (the_proc->stack.stack_size - MSP430X_CORE_EXCEPTION_FRAME_SIZE) >> 1;
	
	//pointer to the exception frame
	CONSTP2VAR(tpl_stack_word, AUTOMATIC, OS_APPL_DATA) exception_frame = stack + size_of_stack_above_exception_frame;
	
#if WITH_PAINT_REGISTERS == YES
	for(i = 0; i < GPR_ON_EXCEPTION_FRAME; i++)
	{
		exception_frame[i] = OS_REG_PATTERN;
	}
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
	l_tpl_context->stackPointer = (uint16)exception_frame;

#if WITH_PAINT_STACK == YES
	for(i = 0; i < size_of_stack_above_exception_frame; i++)
	{
		stack[i] = OS_STACK_PATTERN;
	}
#endif

#if TASK_COUNT > 0
	#if   ISR_COUNT > 0
		uint32 addr_CallTerminateISR2 = (uint32)(CallTerminateISR2);
		uint32 addr_CallTerminateTask = (uint32)(CallTerminateTask);	

		exception_frame[CALL_IDX_LOW] = (IS_ROUTINE == the_proc->type) ? 
			(uint16)(addr_CallTerminateISR2 & 0xffff) :
			(uint16)(addr_CallTerminateTask & 0xffff) ;
		exception_frame[CALL_IDX_HIGH] = (IS_ROUTINE == the_proc->type) ? 
			(uint16)((addr_CallTerminateISR2 >> 16) & 0x000f):
			(uint16)((addr_CallTerminateTask >> 16) & 0x000f);
	#else 
		uint32 addr_CallTerminateTask = (uint32)(CallTerminateTask);	

		exception_frame[CALL_IDX_LOW] = (uint16)(addr_CallTerminateTask & 0xffff);
		exception_frame[CALL_IDX_HIGH] = (uint16)((addr_CallTerminateTask >> 16) & 0x000f);

	#endif
#else
	#if ISR_COUNT > 0
		uint32 addr_CallTerminateISR2 = (uint32)(CallTerminateISR2);

		exception_frame[CALL_IDX_LOW] = (uint16)(addr_CallTerminateISR2 & 0xffff);
		exception_frame[CALL_IDX_HIGH] = (uint16)((addr_CallTerminateISR2 >> 16) & 0x000f);

	#else
		exception_frame[CALL_IDX] = NULL;
	#endif
#endif
	//status register. Set the GIE bit (Global interrupt)
	#if WITH_RESURRECT == NO
	exception_frame[SR_IDX] = (((uint32)(the_proc->entry) & (0xF0000))  >> 4 )| 0x8;
	exception_frame[PC_IDX] = (uint16)(the_proc->entry) & 0xffff;
	#else
	if(proc_id == RESURRECT_TASK_ID) {
		CONSTP2VAR(tpl_proc, AUTOMATIC, OS_APPL_DATA) the_proc_dyn = tpl_dyn_proc_table[proc_id];
		exception_frame[SR_IDX] = (((uint32)(the_proc_dyn->entry) & (0xF0000))  >> 4 )| 0x8;
		exception_frame[PC_IDX] = (uint16)(the_proc_dyn->entry) & 0xffff;
	}
	else {
		exception_frame[SR_IDX] = (((uint32)(the_proc->entry) & (0xF0000))  >> 4 )| 0x8;
		exception_frame[PC_IDX] = (uint16)(the_proc->entry) & 0xffff;
	}
	#endif
#pragma GCC diagnostic pop //"-Wpointer-to-int-cast"

#if WITH_AUTOSAR_STACK_MONITORING == YES && WITH_PAINT_STACK == NO
	(*(uint8 *)(the_proc->stack.stack_zone)) = OS_STACK_PATTERN;
#endif
}

FUNC (void, OS_CODE) tpl_init_machine_generic (void)
{
	#if WITH_MEMORY_PROTECTION == YES
		tpl_init_mpu();	//TODO: mpu not implemented yet
	#endif
}

FUNC(void, OS_CODE) tpl_init_machine_specific (void)
{
	#if WITH_SYSTICK == YES
	tpl_set_systick_timer(); //TODO a remettre.
	#endif
	//tpl_init_external_interrupts();
	//tpl_init_it_priority();
}

FUNC(void, OS_CODE) tpl_set_systick_timer()
{
    PJSEL0 = BIT4 | BIT5;                   // Initialize LFXT pins
    // Configure LFXT 32kHz crystal
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL4 &= ~LFXTOFF;                     // Enable LFXT
    do
    {
        CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT fault flag
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag
    CSCTL0_H = 0;                           // Lock CS registers
    
	/* Set up timer TA3 with ACLK. ACLK is set to LFXTCLK at start : 32.768 kHz */
	TA3CCR0 = 0;          /* lock the timer */
	TA3CTL = TASSEL__ACLK /* ACLK */ | ID__1 /* divide by 1 */ | MC__UP /* Up count */ ;
	TA3CCTL0 |= CCIE;     /* enable the compare interrupt */
	TA3CCR0 = 32;         /* start with a 1.007 ms period (33/32768) */
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/*
 * The kernel stack
 * On MSP430, the kernel stack is separated from other data, as the
 * kernel stack (in use during startup) should not be restored
 * with a checkpoint: it would crash the system.
 */
#define OS_START_SEC_KERN_STACK
#include "tpl_memmap.h"
CONSTP2VAR(tpl_stack_word, AUTOMATIC, OS_APPL_DATA)
  tpl_kern_stack[TPL_KERNEL_STACK_SIZE];
#define OS_STOP_SEC_KERN_STACK
#include "tpl_memmap.h"

/*
 * The reentrancy flag is used to distinguish between a service call`
 * from the application and from a hook.
 * If 0, it ia a call from the application
 * if 1, it is a call from a hook
 */
#define OS_START_SEC_VAR_8BIT
#include "tpl_memmap.h"
volatile uint8 tpl_reentrancy_flag = 0;
#define OS_STOP_SEC_VAR_8BIT
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/* TODO Will not work, the GIE bit has to be changed in the saved SR */
FUNC (void, OS_CODE) tpl_disable_interrupts() {
	__disable_interrupt(); /* msp430 intrinsics.h */
}
FUNC (void, OS_CODE) tpl_enable_interrupts() {
	__enable_interrupt();  /* msp430 intrinsics.h */
}
FUNC (void, OS_CODE) tpl_disable_os_interrupts() {
	tpl_disable_interrupts();
}
FUNC (void, OS_CODE) tpl_enable_os_interrupts() {
	tpl_enable_interrupts();
}

//void tpl_sc_handler() {}

FUNC (void, OS_CODE) idle_function(void)
{
    while(1){
#if IDLE_POWER_MODE != ACTIVE_POWER_MODE
        IDLE_LPM;
#endif
    }
}

FUNC (void, OS_CODE) tpl_init_machine() {
	tpl_init_machine_generic();
	tpl_init_machine_specific();
}

FUNC (void, OS_CODE) tpl_shutdown() {
	LPM4;
}
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"
