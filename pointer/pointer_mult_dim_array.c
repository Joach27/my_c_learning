#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** create_dynamic_array(int count) {
    char** arr = NULL;
    char buffer[30];

    for (int i = 0; i < count; i++) {
        printf("Insert string %d: ", i + 1);
        scanf("%29s", buffer);

        char** tmp = realloc(arr, sizeof(char*) * (i + 1));
        if (!tmp) {
            fprintf(stderr, "Allocation failed\n");
            // free already allocated
            for (int j = 0; j < i; j++) free(arr[j]);
            free(arr);
            return NULL;
        }
        arr = tmp;

        arr[i] = malloc(strlen(buffer) + 1);
        strcpy(arr[i], buffer);
    }
    return arr;
}

void print_dynamic_array(char** arr, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d - %s\n", i, arr[i]);
    }
}

void free_dynamic_array(char** arr, int count) {
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}


void fill_static_pointer_array(char* arr[], int count) {
    char buffer[30];
    for (int i = 0; i < count; i++) {
        printf("Insert string %d: ", i + 1);
        scanf("%29s", buffer);
        arr[i] = malloc(strlen(buffer) + 1);
        strcpy(arr[i], buffer);
    }
}

void print_static_pointer_array(char* arr[], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d - %s\n", i, arr[i]);
    }
}

void free_static_pointer_array(char* arr[], int count) {
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
}


void fill_fixed_2d_array(char arr[][10], int count) {
    for (int i = 0; i < count; i++) {
        printf("Insert string %d (max 9 chars): ", i + 1);
        scanf("%9s", arr[i]);
    }
}

void print_fixed_2d_array(char arr[][10], int count) {
    for (int i = 0; i < count; i++) {
        printf("%d - %s\n", i, arr[i]);
    }
}

int main() {
    int count = 6;

    printf("===> Version dynamique avec realloc\n");
    char** dyn_array = create_dynamic_array(count);
    if (dyn_array) {
        print_dynamic_array(dyn_array, count);
        free_dynamic_array(dyn_array, count);
    }

    printf("\n===> Version statique avec char* arr[6]\n");
    char* static_ptr_array[6];
    fill_static_pointer_array(static_ptr_array, count);
    print_static_pointer_array(static_ptr_array, count);
    free_static_pointer_array(static_ptr_array, count);

    printf("\n===> Version tableau 2D char arr[6][10]\n");
    char fixed_array[6][10];
    fill_fixed_2d_array(fixed_array, count);
    print_fixed_2d_array(fixed_array, count);

    return 0;
}
