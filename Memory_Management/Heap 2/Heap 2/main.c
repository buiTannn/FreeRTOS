#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

// Task thực hiện cấp phát và giải phóng bộ nhớ
void memoryManagementTask(void* pvParameters) {
    void* ptr1, * ptr2, * ptr3, * ptr4;

    printf("Before allocation: Free heap = %u bytes\n", (unsigned int)xPortGetFreeHeapSize());

    // Cấp phát bộ nhớ
    ptr1 = pvPortMalloc(100); // Cấp 100B
    printf("After allocating 100B: Free heap = %u bytes\n", (unsigned int)xPortGetFreeHeapSize());

    ptr2 = pvPortMalloc(50); // Cấp 50B
    printf("After allocating 50B: Free heap = %u bytes\n", (unsigned int)xPortGetFreeHeapSize());

    ptr3 = pvPortMalloc(100); // Cấp 100B
    printf("After allocating 100B: Free heap = %u bytes\n", (unsigned int)xPortGetFreeHeapSize());

    // Giải phóng bộ nhớ
    vPortFree(ptr3);
    printf("After freeing 100B: Free heap = %u bytes\n", (unsigned int)xPortGetFreeHeapSize());

    //ptr4 = pvPortMalloc(140);
    //ptr4 = pvPortMalloc(100); 
    ptr4 = pvPortMalloc(80); 
    if (ptr4 == NULL) {
        printf("Failed to allocate 80B for ptr4\n");
    }
    else {
        printf("After allocating 80B at %p: Free heap = %u bytes\n", ptr4, (unsigned int)xPortGetFreeHeapSize());
    }

}

int main(void) {
    xTaskCreate(memoryManagementTask, "MemoryTask", 1024, NULL, 1, NULL);

    // Bắt đầu scheduler
    vTaskStartScheduler();
    for (;;) {}
}
