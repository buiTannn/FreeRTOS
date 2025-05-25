#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Task 1: ch?y 5 l?n r?i t? xóa
void vTask1(void* pvParameters) {
    for (int i = 0; i < 5; i++) {
        printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 giây
    }

    printf("Task 1 completed and will be deleted\n");
    vTaskDelete(NULL);  // Xóa chính task này
}

// Task 2: ch?y mãi mãi
void vTask2(void* pvParameters) {
    for (;;) {
        printf("Task 2 is running\n");
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 giây
    }
}

void app_main(void) {
    // T?o Task 1
    xTaskCreate(vTask1, "Task1", 2048, NULL, 1, NULL);
    // T?o Task 2
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, NULL);
}
