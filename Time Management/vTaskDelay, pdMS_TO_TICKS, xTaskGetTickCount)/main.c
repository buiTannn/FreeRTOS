#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void *pvParameters) {
    while (1) {
        TickType_t xCurrentTime = xTaskGetTickCount();  // L?y th?i gian hi?n t?i (ticks)
        
        printf("Task 1 is running at %ld ms\n", xCurrentTime * portTICK_PERIOD_MS);
        
        // Ð?i 2000 ms (2 giây)
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
void app_main(void) {
    xTaskCreate(task1, "Task1", 2048, NULL, 1, NULL);
}
