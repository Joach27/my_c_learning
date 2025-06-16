#include <stdio.h>
#include <stdlib.h>

int global_init = 10;     // segment data
int global_uninit;        // segment BSS

void print_addresses() {
    int local_var = 5;    // stack
    int *heap_ptr = malloc(sizeof(int)); // heap
    static int static_var = 42; // segment data

    printf("===== Virtual Memory Map Demo =====\n");
    printf("Code (text) segment : %p (function address)\n", (void*)print_addresses);
    printf("Initialized data     : %p (global_init)\n", (void*)&global_init);
    printf("Uninitialized data   : %p (global_uninit)\n", (void*)&global_uninit);
    printf("Static data          : %p (static_var)\n", (void*)&static_var);
    printf("Heap                 : %p (heap_ptr)\n", (void*)heap_ptr);
    printf("Stack                : %p (local_var)\n", (void*)&local_var);

    free(heap_ptr);
}

int main() {
    print_addresses();
    return 0;
}
