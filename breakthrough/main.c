#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int main()
{
    int n = 7;
    int** arr;
    arr = init_board(n);
    fill_array(arr, n);
    print_board(arr, n);
    
    free_array((void**)arr, n);
    return 0;
}