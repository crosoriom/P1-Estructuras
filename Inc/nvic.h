#ifndef NVIC_H
#define NVIC_H

#include <stdint.h>

#define NVIC ((NestedVectoredInterruptController_t *)0xE000E100UL)

typedef enum {
    WWDG_IRQn,
    PVD_PVM_IRQn,
    TAMP_STAMP_IRQn,
    RTC_WKUP_IRQn,
    FLASH_IRQn,
    RCC_IRQn,
    EXTI0_IRQn,
    EXTI1_IRQn,
    EXTI2_IRQn,
    EXTI3_IRQn,
    EXTI4_IRQn,
    DMA1_Stream0_IRQn,
    DMA1_Stream1_IRQn,
    DMA1_Stream2_IRQn,
    DMA1_Stream3_IRQn,
    DMA1_Stream4_IRQn,
    DMA1_Stream5_IRQn,
    DMA1_Stream6_IRQn,
    ADC_IRQn,
    FDCAN1_IT0_IRQn,
    FDCAN2_IT0_IRQn,
    FDCAN1_IT1_IRQn,
    FDCAN2_IT1_IRQn,
    EXTI9_5_IRQn,
    TIM1_BRK_IRQn,
    TIM1_UP_IRQn,
    TIM1_TRG_COM_IRQn,
    TIM1_CC_IRQn,
    TIM2_IRQn,
    TIM3_IRQn,
    TIM4_IRQn,
    I2C1_EV_IRQn,
    I2C1_ER_IRQn,
    I2C2_EV_IRQn,
    I2C2_ER_IRQn,
    SPI1_IRQn,
    SPI2_IRQn,
    USART1_IRQn,
    USART2_IRQn,
    USART3_IRQn,
    EXTI15_10_IRQn,
}IRQn_t;

typedef struct {
    volatile uint32_t ISER[8];
    volatile uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];
    volatile uint32_t RESERVED1[24];
    volatile uint32_t ISPR[8];
    volatile uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8];
    volatile uint32_t RESERVED3[24];
    volatile uint32_t IABR[8];
    volatile uint32_t RESERVED4[56];
    volatile uint32_t IPR[60];
    volatile uint32_t RESERVED5[644];
    volatile uint32_t STIR;
}NestedVectoredInterruptController_t;

void nvic_irq_enable(IRQn_t irq);

#endif