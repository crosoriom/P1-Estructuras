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

volatile uint8_t button_pressed = 0; // Flag to indicate button press
uint8_t button_driver_get_event(void)
{
    return button_pressed;
}

uint32_t b1_tick = 0;
void detect_button_press(void)
{
    if (systick_getTick() - b1_tick < 50) {
        return; // Ignore bounces of less than 50 ms
    } else if (systick_getTick() - b1_tick > 500) {
        button_pressed = 1; // single press
    } else {
        button_pressed = 2; // double press
    }

    b1_tick = systick_getTick();
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1 << 13)) {
        EXTI->PR1 = (1 << 13); // Clear pending bit
        detect_button_press();
    }
}