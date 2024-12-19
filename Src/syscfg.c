#include "syscfg.h"
#include "rcc.h"

void exti_map(void)
{
    activate_syscfg();
    SYSCFG->EXTICR4 &= ~(0xF << 4);
    SYSCFG->EXTICR4 |= (0x2 << 4);

    SYSCFG->EXTICR4 &= ~(0xF << 0);
    SYSCFG->EXTICR4 |= (0x2 << 0);

    SYSCFG->EXTICR3 &= ~(0xF << 8);
    SYSCFG->EXTICR3 |= (0x2 << 8);
}