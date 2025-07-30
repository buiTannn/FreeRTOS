    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "freertos/semphr.h"
    #include <stdio.h>
    #include "esp_task_wdt.h"

    volatile int counter1 = 0;
    volatile int counter2 = 0;

    void Task1(void *pvParameters)
    {
        while (1)
        {
            counter1++;
        }
    }

    void Task2(void *pvParameters)
    {
        while (1)
        {
            counter2++;
        }
    }

    // Task quan sát
    void MonitorTask(void *pvParameters)
    {
        while (1)
        {
            printf("Task1: %d | Task2: %d\n", counter1, counter2);
            vTaskDelay(pdMS_TO_TICKS(500));  
        }
    }

    void app_main()
    {
        xTaskCreate(MonitorTask, "Monitor", 2048, NULL, 5, NULL); 
        xTaskCreate(Task1, "Task1", 2048, NULL, 1, NULL);
        xTaskCreate(Task2, "Task2", 2048, NULL, 1, NULL);
    }
