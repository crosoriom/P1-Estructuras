#include "rcc.h"

void activate_syscfg()
{
	RCC->APB2ENR |= (0x1 << 0);
}

void gpio_activate(uint8_t gpio)
{
	if(gpio == 0xFF)
		return;
	RCC->AHB2ENR |= (0x1 << gpio);
}