// Access Control System Implementation
#include <stdint.h>
#include "systick.h"
#include "syscfg.h"
#include "uart.h"
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

void run_state_machine(void) {
    switch (current_state) {
        case LOCKED:
            // No periodic action in locked state
            break;
        case TEMP_UNLOCK:
            if (systick_getTick() - unlock_timer >= TEMP_UNLOCK_DURATION) {
                gpio_set_lowLevel(GPIOA, PIN_4); // Turn off door state LED
                current_state = LOCKED;
            }
            break;
        case PERM_UNLOCK:
            // No periodic action in permanent unlock state
            break;
    }
}

void handle_event(uint8_t event) {
    if (event == 1) { // Single button press
        gpio_set_highLevel(GPIOA, PIN_4); // Turn on door state LED
        current_state = TEMP_UNLOCK;
        unlock_timer = systick_getTick();
    } else if (event == 2) { // Double button press
        gpio_set_highLevel(GPIOA, PIN_4); // Turn on door state LED
        current_state = PERM_UNLOCK;
    } else if (event == 'O') { // UART OPEN command
        gpio_set_highLevel(GPIOA, PIN_4); // Turn on door state LED
        current_state = TEMP_UNLOCK;
        unlock_timer = systick_getTick();
    } else if (event == 'C') { // UART CLOSE command
        gpio_set_lowLevel(GPIOA, PIN_4); // Turn off door state LED
        current_state = LOCKED;
    }
}

int main(void) {
    systick_init(4000);
    configure_gpio_input(GPIOC, PIN_13);
    gpio_interrupt_enable(PIN_13, FALLING_EDGE);
    configure_gpio_output(GPIOA, PIN_5);
    configure_gpio_output(GPIOA, PIN_4);
    UART_Init(USART2);

    usart2_send_string("System Initialized\r\n");

    uint32_t heartbeat_tick = 0;
    while (1) {
        if (systick_getTick() - heartbeat_tick >= 500) {
            heartbeat_tick = systick_getTick();
            gpio_toggle_level(GPIOA, PIN_5);
        }

        uint8_t button_pressed = button_driver_get_event();
        if (button_pressed != 0) {
            handle_event(button_pressed);
            button_pressed = 0;
        }

        uint8_t rx_byte = usart2_get_command();
        if (rx_byte != 0) {
            handle_event(rx_byte);
            rx_byte = 0;
        }

        run_state_machine();
    }
}