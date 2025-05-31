#include "FreeRTOS.h"
#include "portable.h"
#include <stdio.h>

/* Khai báo 2 mảng để làm heap regions */
static uint8_t ucHeap1[16384];  /* 16KB */
static uint8_t ucHeap2[32768];  /* 32KB */

/* Định nghĩa 2 vùng nhớ cho heap */
const HeapRegion_t xHeapRegions[] =
{
    { ucHeap1, sizeof(ucHeap1) },  // Vùng 1: 16KB
    { ucHeap2, sizeof(ucHeap2) },  // Vùng 2: 32KB
    { NULL, 0 }                    
};

/* Hiển thị thông tin heap */
void vShowHeapInfo(void)
{
    printf("Free heap: %zu bytes\n", xPortGetFreeHeapSize());
}

int main(void)
{
    /* Khởi tạo heap_5 */
    vPortDefineHeapRegions(xHeapRegions);
    printf("Vung 1: %p, 16KB\n", ucHeap1);
    printf("Vung 2: %p, 32KB\n", ucHeap2);

    vShowHeapInfo();

    /* Cấp phát bộ nhớ */
    void* ptr1 = pvPortMalloc(1024);
    void* ptr2 = pvPortMalloc(2048);

    if (ptr1 && ptr2) {
        printf("Cap phat thanh cong: 3072 bytes\n");
    }
    else {
        printf("Error\n");
    }

    vShowHeapInfo();

    /* Giải phóng bộ nhớ */
    vPortFree(ptr1);
    vPortFree(ptr2);
    printf("Free ptr 1 va ptr 2\n");

    vShowHeapInfo();

    printf("Demo hoàn thành!\n");
    return 0;
}
