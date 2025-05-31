#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TickType_t xLastWakeTime;

void task1(void *pvParameters) {
    // Kh?i t?o xLastWakeTime v?i th?i di?m hi?n t?i
    xLastWakeTime = xTaskGetTickCount();

    while (1) {
        // In thông báo m?i l?n task ch?y
        printf("Task 1 is running at tick %ld\n", xLastWakeTime);
        vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_PERIOD_MS);

    }
}
void app_main(void) {
    // T?o task1 v?i d? uu tiên 1
    xTaskCreate(task1, "Task 1", 2048, NULL, 1, NULL);
}
