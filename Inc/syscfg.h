#ifndef SYSCFG_H
#define SYSCFG_H

#include <stdint.h>

#define SYSCFG ((SystemConfiguration_t *)0x40010000UL)

typedef struct {
    volatile uint32_t MEMRMP;
    volatile uint32_t CFGR1;
    volatile uint32_t EXTICR1;
    volatile uint32_t EXTICR2;
    volatile uint32_t EXTICR3;
    volatile uint32_t EXTICR4;
}SystemConfiguration_t;

void exti_map(void);

#endif