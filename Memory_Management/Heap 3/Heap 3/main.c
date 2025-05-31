#include <stdio.h>
#include <stdlib.h>     // malloc, free
#include <stdint.h>   
#include "FreeRTOS.h"  
#include "task.h"


void memoryManagementTask(void* pvParameters) {
    void* ptr1, * ptr2, * ptr3;


    ptr1 = pvPortMalloc(100);
    printf("Cap 100B tai %p\n", ptr1);

    ptr2 = pvPortMalloc(200);
    printf("Cap 200B tai %p\n", ptr2);

    ptr3 = pvPortMalloc(300);
    printf("Cap 300B tai %p\n", ptr3);

    vPortFree(ptr2);
    printf("Free 200B (ptr2)\n");

    vPortFree(ptr1);
    printf("Free 100B (ptr1)\n");

    vPortFree(ptr3);
    printf("Free 300B (ptr3)\n");

    printf("End task\n");

    vTaskDelete(NULL); 
}

// Main giả lập FreeRTOS
int main(void) {
    xTaskCreate(memoryManagementTask, "MemTask", 1024, NULL, 1, NULL);
    vTaskStartScheduler();  
    while (1);           
}
