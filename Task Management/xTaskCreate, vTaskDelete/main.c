#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Task 1: ch?y 5 l?n r?i t? x�a
void vTask1(void* pvParameters) {
    for (int i = 0; i < 5; i++) {
        printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 gi�y
    }

    printf("Task 1 completed and will be deleted\n");
    vTaskDelete(NULL);  // X�a ch�nh task n�y
}

// Task 2: ch?y m�i m�i
void vTask2(void* pvParameters) {
    for (;;) {
        printf("Task 2 is running\n");
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 gi�y
    }
}

void app_main(void) {
    // T?o Task 1
    xTaskCreate(vTask1, "Task1", 2048, NULL, 1, NULL);
    // T?o Task 2
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, NULL);
}
