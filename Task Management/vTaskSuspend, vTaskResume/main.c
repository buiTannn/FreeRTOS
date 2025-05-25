#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Handle d? luu task 1
TaskHandle_t xHandleTask1 = NULL;

// Task 1: In ra thông báo và t? t?m d?ng
void vTask1(void* pvParameters) {
    for (;;) {
        printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 giây

        // T?m d?ng task này
        printf("Task 1 is now suspended\n");
        vTaskSuspend(NULL);  // Suspend chính task này
    }
}

// Task 2: In ra thông báo và resume Task 1 sau 5 l?n
void vTask2(void* pvParameters) {
    for (int i = 1; i < 16; i++) {
        printf("Task 2 is running\n");
        if (i % 5 == 0) {
            printf("Resuming Task 1 now\n");
            vTaskResume(xHandleTask1);  // Resume Task 1
        }
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 giây
    }

    // Sau khi Task 2 ch?y 5 l?n, resume Task 1
}

void app_main(void) {
    // T?o Task 1 và luu handle
    xTaskCreate(vTask1, "Task1", 2048, NULL, 1, &xHandleTask1);

    // T?o Task 2
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, NULL);

    // Không c?n g?i vTaskStartScheduler()
}
