#ifndef SYSCFG_H
#define SYSCFG_H

#include <stdint.h>
#include "gpio.h"

#define SYSCFG ((SystemConfiguration_t *)0x40010000UL)

typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t CFGR1;
    volatile uint32_t EXTICR[4];
}SystemConfiguration_t;

void exti_map(gpio_t *GPIOx, PINx pin);

#endif