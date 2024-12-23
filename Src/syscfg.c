#include "syscfg.h"
#include "gpio.h"
#include "rcc.h"

void exti_map(gpio_t *GPIOx, PINx pin)
{
    activate_syscfg();
    
    if(GPIOx == GPIOA)
        SYSCFG->EXTICR[pin / 4] |= (0x0 << 4 * (pin % 4));
    else if(GPIOx == GPIOB)
        SYSCFG->EXTICR[pin / 4] |= (0x1 << 4 * (pin % 4));
    else if(GPIOx == GPIOC)
        SYSCFG->EXTICR[pin / 4] |= (0x2 << 4 * (pin % 4));
    else if(GPIOx == GPIOD)
        SYSCFG->EXTICR[pin / 4] |= (0x3 << 4 * (pin % 4));
    else if(GPIOx == GPIOE)
        SYSCFG->EXTICR[pin / 4] |= (0x4 << 4 * (pin % 4));
    else if(GPIOx == GPIOF)
        SYSCFG->EXTICR[pin / 4] |= (0x5 << 4 * (pin % 4));
    else if(GPIOx == GPIOG)
        SYSCFG->EXTICR[pin / 4] |= (0x6 << 4 * (pin % 4));
    else if(GPIOx == GPIOH)
        SYSCFG->EXTICR[pin / 4] |= (0x7 << 4 * (pin % 4));
}