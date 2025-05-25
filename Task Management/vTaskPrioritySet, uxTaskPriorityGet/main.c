#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t xTaskHandle1;
TaskHandle_t xTaskHandle2;

// Hàm c?a Task 1
void vTask1(void *pvParameters) {
    while (1) {
        printf("Task 1 is running\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// Hàm c?a Task 2
void vTask2(void *pvParameters) {
    while (1) {
        printf("Task 2 is running\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

// Hàm setup d? t?o và di?u ch?nh các task
void app_main(void) {
    xTaskCreate(vTask1, "Task 1", 2048, NULL, 2, &xTaskHandle1);

    xTaskCreate(vTask2, "Task 2", 2048, NULL, 1, &xTaskHandle2);

    vTaskDelay(2000 / portTICK_PERIOD_MS);
    UBaseType_t uxPriority1 = uxTaskPriorityGet(xTaskHandle1);
    printf("Task 1 priority: %d\n", uxPriority1);

    UBaseType_t uxPriority2 = uxTaskPriorityGet(xTaskHandle2);
    printf("Task 2 priority: %d\n", uxPriority2);

    vTaskPrioritySet(xTaskHandle2, 3);
    printf("Task 3 priority:3\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    uxPriority2 = uxTaskPriorityGet(xTaskHandle2);
    printf("Task 2 new priority: %d\n", uxPriority2);
}