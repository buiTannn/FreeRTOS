#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BUTTON_GPIO GPIO_NUM_15

static volatile bool button_pressed = false;
static volatile TickType_t interrupt_tick = 0;

static void IRAM_ATTR gpio_isr_handler(void* arg) {
    button_pressed = true;
    interrupt_tick = xTaskGetTickCountFromISR();
}

void app_main(void) {
    // C?u hình GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE
    };
    gpio_config(&io_conf);

    // Cài d?t interrupt
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_GPIO, gpio_isr_handler, NULL);

    // Vòng l?p chính
    while (1) {
        if (button_pressed) {
            printf("Button pressed! Tick: %lu\n", interrupt_tick);
            button_pressed = false;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}