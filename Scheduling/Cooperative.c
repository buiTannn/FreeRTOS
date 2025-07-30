#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"

void low_priority_task(void *pvParameters) {
    while (1) {
        printf("Low Priority Task running\n");
    }
}

void high_priority_task(void *pvParameters) {
    while (1) {
        printf("High Priority Task running\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    xTaskCreate(low_priority_task, "LowTask", 2048, NULL, 1, NULL);

    vTaskDelay(1000 / portTICK_PERIOD_MS); 

    xTaskCreate(high_priority_task, "HighTask", 2048, NULL, 5, NULL);
}
