#include "systick.h"

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
}SysTick_t;

#define SYSTICK ((SysTick_t *)0xE000E010UL)	//Base address if System Timer.

volatile uint32_t ms_counter = 0;

void systick_init(uint32_t ticks)
{
	SYSTICK->CTRL = 0x4;					//Write 100 on bits 2,1 and 0 in STK_CTRL Register. Turns off the System Timer for configuration and the exception requester.
	
	if(ticks > 0x00FFFFFF)
		ticks = 0x00FFFFFF;
	SYSTICK->LOAD = ticks;					//Load the desired time for the Syster Timer Exception

	SYSTICK->CTRL = 0x7;					//Write 111 on bits 2,1 and 0 in STK_CTRL Register. Turns on the System Timer and the Exception Requester.
}

uint32_t systick_getTick(void)
{
	return ms_counter;
}

void systick_reset(void)
{
	ms_counter = 0;
}

void SysTick_Handler(void)
{
	ms_counter++;
}
