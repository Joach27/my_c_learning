#include <stdio.h>
#include <stdlib.h>

int** init_board(int n){
    int** array;
    
    array = malloc(sizeof(int*) * n);
    for (int i=0; i<n; i++){
        array[i] = (int*)malloc(sizeof(int) * n);
    }
    
    return array;
}

void fill_array(int** arr, int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            arr[i][j] = i + j;
        }
    }
}

void print_array(int** array, int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            // printf("Array[%d][%d]: %d\n", i, j, array[i][j]);
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}


void free_array(int**arr, int n){
    for (int i=0; i<n; i++){
        free(arr[i]);
    }
    free(arr);
}

int main()
{
    int** arr;
    int n = 6; // Dimension of the square array
    arr = init_board(n);
    fill_array(arr, n);
    print_array(arr, n);
    
    free_array(arr, n);
    return 0;
}

