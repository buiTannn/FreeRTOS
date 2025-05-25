#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Handle d? luu task 1
TaskHandle_t xHandleTask1 = NULL;

// Task 1: In ra th�ng b�o v� t? t?m d?ng
void vTask1(void* pvParameters) {
    for (;;) {
        printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 gi�y

        // T?m d?ng task n�y
        printf("Task 1 is now suspended\n");
        vTaskSuspend(NULL);  // Suspend ch�nh task n�y
    }
}

// Task 2: In ra th�ng b�o v� resume Task 1 sau 5 l?n
void vTask2(void* pvParameters) {
    for (int i = 1; i < 16; i++) {
        printf("Task 2 is running\n");
        if (i % 5 == 0) {
            printf("Resuming Task 1 now\n");
            vTaskResume(xHandleTask1);  // Resume Task 1
        }
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 gi�y
    }

    // Sau khi Task 2 ch?y 5 l?n, resume Task 1
}

void app_main(void) {
    // T?o Task 1 v� luu handle
    xTaskCreate(vTask1, "Task1", 2048, NULL, 1, &xHandleTask1);

    // T?o Task 2
    xTaskCreate(vTask2, "Task2", 2048, NULL, 1, NULL);

    // Kh�ng c?n g?i vTaskStartScheduler()
}
