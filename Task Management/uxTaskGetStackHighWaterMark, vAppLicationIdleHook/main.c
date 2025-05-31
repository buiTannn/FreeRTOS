#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Handle cho 2 task
TaskHandle_t xHandleTask1 = NULL;
TaskHandle_t xHandleTask2 = NULL;

// Task 1
void vTask1(void* pvParameters) {
    while (1) {
        printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task 2
void vTask2(void* pvParameters) {
    while (1) {
        printf("Task 2 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Idle Hook d? giám sát stack còn l?i
void vApplicationIdleHook(void) {
    static int count = 0;

    if (++count >= 300) {  // Gi?m t?n su?t in log
        count = 0;

        UBaseType_t stack1 = uxTaskGetStackHighWaterMark(xHandleTask1);
        UBaseType_t stack2 = uxTaskGetStackHighWaterMark(xHandleTask2);

        printf("[IdleHook] Stack left - Task1: %lu words, Task2: %lu words\n",
            (unsigned long)stack1, (unsigned long)stack2);
    }
}

// Ðây là hàm chính trong ESP-IDF, du?c g?i t? d?ng
void app_main(void) {
    // T?o Task 1
    xTaskCreate(vTask1, "Task1", 2048, NULL, 1, &xHandleTask1);

    // T?o Task 2
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, &xHandleTask2);
}
