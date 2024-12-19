#include "nvic.h"

void nvic_irq_enable(IRQn_t irq)
{
    NVIC->ISER[irq / 32] |= (0x1 << irq % 32);
}
