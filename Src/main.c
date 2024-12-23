/* Access Control System Implementation */
#include <stdint.h>
#include "systick.h"
#include "exti.h"
#include "gpio.h"

#define TEMP_UNLOCK_DURATION 5000 // Duration in ms for temporary unlock

typedef enum {
    LOCKED,
    TEMP_UNLOCK,
    PERM_UNLOCK
} DoorState_t;

DoorState_t current_state = LOCKED;
uint32_t unlock_timer = 0;

int main(void) {
    
    systick_init(4000);
    configure_gpio_input(GPIOC, PIN_13);
    gpio_interrupt_enable(GPIOC, PIN_13, FALLING_EDGE);
    configure_gpio_output(GPIOA, PIN_5);
    configure_gpio_output(GPIOA, PIN_4);
    // UART_Init(USART2);

    // usart2_send_string("System Initialized\r\n");

    uint32_t heartbeat_tick = 0;
    while (1) {
        if (systick_getTick() - heartbeat_tick >= 500) {
            heartbeat_tick = systick_getTick();
            gpio_toggle_level(GPIOA, PIN_5);
        }

        switch (current_state)
        {
        case LOCKED:
            gpio_set_lowLevel(GPIOA, PIN_4);
            break;
        case TEMP_UNLOCK:
            gpio_set_highLevel(GPIOA, PIN_4);
            if(systick_getTick() - unlock_timer >= TEMP_UNLOCK_DURATION)
                current_state = LOCKED;
            break;
        case PERM_UNLOCK:
            break;
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI->PR1 & (1 << 13)) {
        if(current_state == LOCKED) {
            current_state = TEMP_UNLOCK;
            unlock_timer = systick_getTick();
        } else if (current_state == TEMP_UNLOCK)
            current_state = PERM_UNLOCK;
        else
            current_state = LOCKED;
        EXTI->PR1 = (1 << 13);
    }
}