#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void HighPriorityTask(void *pvParameters)
{
    while (1)
    {
        printf(">> High Priority Task is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}

void LowPriorityTask(void *pvParameters)
{
    while (1)
    {
        printf("Low Priority Task is running\n");
   
    }
}

void app_main(void)
{
    xTaskCreate(LowPriorityTask, "LowTask", 2048, NULL, 1, NULL);
    xTaskCreate(HighPriorityTask, "HighTask", 2048, NULL, 2, NULL);
}
