#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Handle d? luu task 1
TaskHandle_t xHandleTask1 = NULL;

// Task 1: In ra th�ng b�o v� t? t?m d?ng
void vTask1(void* pvParameters) {
    for (;;) {
        printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(3000));  // Delay 3 gi�y

        printf("Task 1 is now suspended\n");
        vTaskSuspend(NULL);  // Suspend ch�nh task n�y
    }
}

// H�m ph? d? in tr?ng th�i task
void printTaskState(eTaskState state) {
    switch (state) {
        case eRunning:
            printf("Task 1 state: Running\n");
            break;
        case eReady:
            printf("Task 1 state: Ready\n");
            break;
        case eBlocked:
            printf("Task 1 state: Blocked\n");
            break;
        case eSuspended:
            printf("Task 1 state: Suspended\n");
            break;
        case eDeleted:
            printf("Task 1 state: Deleted\n");
            break;
        default:
            printf("Task 1 state: Unknown\n");
            break;
    }
}

// Task 2: In ra th�ng b�o v� resume Task 1 sau m?i 5 l?n ch?y
void vTask2(void* pvParameters) {
    for (int i = 1; i <= 15; i++) {
        printf("Task 2 is running\n");

        eTaskState state = eTaskGetState(xHandleTask1);
        printTaskState(state);

        if (i % 5 == 0) {
            printf("Resuming Task 1 now\n");
            vTaskResume(xHandleTask1);  // Resume Task 1
        }

        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 gi�y
    }

    vTaskDelete(NULL);  // X�a Task 2 sau khi ho�n th�nh
}

void app_main(void) {
    // T?o Task 1 v� luu handle
    xTaskCreate(vTask1, "Task1", 2048, NULL, 1, &xHandleTask1);

    // T?o Task 2
    xTaskCreate(vTask2, "Task2", 2048, NULL, 2, NULL);

}
