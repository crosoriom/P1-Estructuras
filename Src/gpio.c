#include "systick.h"
#include "gpio.h"
#include "exti.h"
#include "rcc.h"

uint8_t get_gpio_number(gpio_t *GPIOx)
{
	if(GPIOx == GPIOA) return 0;
	else if(GPIOx == GPIOB) return 1;
	else if(GPIOx == GPIOC) return 2;
	else if(GPIOx == GPIOD) return 3;
	else if(GPIOx == GPIOE) return 4;
	else if(GPIOx == GPIOF) return 5;
	else if(GPIOx == GPIOG) return 6;
	else if(GPIOx == GPIOH) return 7;
	else return 0xFF;
}

void reset_gpio_mode(gpio_t *GPIOx, PINx pin)
{
	GPIOx->MODER &= ~(0x3 << (2 * pin));
}

void configure_gpio_input(gpio_t *GPIOx, PINx pin)
{
	gpio_activate(get_gpio_number(GPIOx));
	reset_gpio_mode(GPIOx, pin);
}

void configure_gpio_output(gpio_t *GPIOx, PINx pin)
{
	gpio_activate(get_gpio_number(GPIOx));
	reset_gpio_mode(GPIOx, pin);
	GPIOx->MODER |= (0x1 << (2 * pin));
}

void gpio_set_highLevel(gpio_t *GPIOx, PINx pin)
{
	GPIOx->ODR |= (0x1 << pin);
}

void gpio_set_lowLevel(gpio_t *GPIOx, PINx pin)
{
	GPIOx->ODR &= ~(0x1 << pin);
}

// int gpio_get_level(gpio_t *GPIOx, PINx pin, InputMode_t mode)
// {
// 	switch(mode) {
// 	case PULLUP:
// 		if((GPIOx->IDR & (1 << pin)) == 0)
// 			return 1;
// 		else
// 			return 0;
// 		break;
// 	case PULLDOWN:
// 		if((GPIOx->IDR & (1 << pin)) == 1)
// 			return 1;
// 		else
// 			return 0;
// 		break;
// 	}
// }

void gpio_toggle_level(gpio_t *GPIOx, PINx pin)
{
	GPIOx->ODR ^= (0x1 << pin);
}