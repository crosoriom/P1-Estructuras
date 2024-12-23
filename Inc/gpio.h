#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/*Base address for all GPIOs*/
#define GPIOA ((gpio_t *)0x48000000UL)
#define GPIOB ((gpio_t *)0x48000400UL)
#define GPIOC ((gpio_t *)0x48000800UL)
#define GPIOD ((gpio_t *)0x48000C00UL)
#define GPIOE ((gpio_t *)0x48001000UL)
#define GPIOF ((gpio_t *)0x48001400UL)
#define GPIOG ((gpio_t *)0x48001800UL)
#define GPIOH ((gpio_t *)0x48001C00UL)

typedef enum {
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15
}PINx;

typedef enum {
	PULLUP,
	PULLDOWN
}InputMode_t;

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
	volatile uint32_t ASCR;
}gpio_t;

uint8_t get_gpio_number(gpio_t *GPIOx);
void configure_gpio_input(gpio_t *GPIOx, PINx pin);
void configure_gpio_output(gpio_t *GPIOx, PINx pin);
void gpio_set_lowLevel(gpio_t *GPIOx, PINx pin);
void gpio_set_highLevel(gpio_t *GPIOx, PINx pin);
int gpio_get_level(gpio_t *GPIOx, PINx pin, InputMode_t mode);
void gpio_toggle_level(gpio_t *GPIOx, PINx pin);

#endif