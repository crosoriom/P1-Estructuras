#include "exti.h"
#include "gpio.h"
#include "nvic.h"

void gpio_interrupt_enable(uint8_t pin, Trigger_t trigger)
{
    EXTI->IMR1 |= (1 << pin);
    switch (trigger) {
    case RISING_EDGE:
        EXTI->RTSR1 |= (0x1 << pin);
        EXTI->FTSR1 &= ~(0x1 << pin);
        break;
    case FALLING_EDGE:
        EXTI->RTSR1 &= ~(0x1 << pin);
        EXTI->FTSR1 |= (0x1 << pin);
        break;
    case BOTH_EDGES:
        EXTI->RTSR1 |= (0x1 << pin);
        EXTI->FTSR1 |= (0x1 << pin);
        break;
    }
    if(pin >= 10)
        nvic_irq_enable(EXTI15_10_IRQn);
    else if (pin >= 5)
        nvic_irq_enable(EXTI9_5_IRQn);
    else if (pin == 4)
        nvic_irq_enable(EXTI4_IRQn);
    else if (pin == 3)
        nvic_irq_enable(EXTI3_IRQn);
    else if (pin == 2)
        nvic_irq_enable(EXTI2_IRQn);
    else if (pin == 1)
        nvic_irq_enable(EXTI1_IRQn);
    else
        nvic_irq_enable(EXTI0_IRQn);
}

void EXTI9_5_IRQHandler()
{
    if (EXTI->PR1 & (1 << 9))
        EXTI->PR1 = (1 << 9);
    if (EXTI->PR1 & (1 << 8))
        EXTI->PR1 = (1 << 8);
    if (EXTI->PR1 & (1 << 7))
        EXTI->PR1 = (1 << 7);
    if (EXTI->PR1 & (1 << 6))
        EXTI->PR1 = (1 << 6);
    if (EXTI->PR1 & (1 << 5))
        EXTI->PR1 = (1 << 5);
}

void EXTI4_IRQHandler()
{
    /*Insertar código*/;
}

void EXTI3_IRQHandler()
{
    /*Insertar código*/;
}

void EXTI2_IRQHandler()
{
    /*Insertar código*/;
}

void EXTI1_IRQHandler()
{
    /*Insertar código*/;
}

void EXTI0_IRQHandler()
{
    /*Insertar código*/;
}