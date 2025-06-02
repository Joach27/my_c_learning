// memo_exemple.c
#include <stdio.h>
#include <stdlib.h>

int global_init = 42;         // → .data
int global_uninit;            // → .bss
const char *message = "Hello, World!\n";  // → .rodata

void fonction() {
    int local = 5;            // → stack
    printf("Local: %d\n", local);
}

int main() {
    fonction();

    int *ptr = malloc(sizeof(int));  // → heap
    *ptr = 100;
    printf("Dynamic: %d\n", *ptr);

    printf("%s", message);
    free(ptr);

    return 0;                 // → .text
}
