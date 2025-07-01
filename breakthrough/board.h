#ifndef BOARD_H
#define BOARD_H

int** init_board(int n);    
void fill_array(int** arr, int n);
void print_board(int** arr, int n);
void free_array(void**arr, int n);

#endif 