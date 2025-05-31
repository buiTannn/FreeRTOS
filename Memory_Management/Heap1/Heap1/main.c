#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"


int main(void)
{
    size_t xFreeHeapBefore, xFreeHeapAfterFree;
    void* pvTestMemory;

    // In ra dung lượng heap ban đầu
    xFreeHeapBefore = xPortGetFreeHeapSize();
    printf("Free heap before task creation: %u bytes\n", (unsigned int)xFreeHeapBefore);


    pvTestMemory = pvPortMalloc(100);
    printf("Free heap after malloc: %u bytes\n", (unsigned int)xPortGetFreeHeapSize());

    vPortFree(pvTestMemory);

    // Kiểm tra heap sau khi free
    xFreeHeapAfterFree = xPortGetFreeHeapSize();
    printf("Free heap after vPortFree: %u bytes\n", (unsigned int)xFreeHeapAfterFree);

    // Bắt đầu scheduler
    vTaskStartScheduler();
    for (;;);
}