#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

#define SYSTICK ((SysTick_t *)0xE000E010UL)	//Base address if System Timer.

void systick_init(uint32_t ticks);
uint32_t systick_getTick(void);
void systick_reset(void);

#endif
