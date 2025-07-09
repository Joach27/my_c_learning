#include <stdio.h>
#include <stdlib.h>

void free_array(void**arr, int n);

// const char* alphabet = "abcdefghijklmnopqrstuvwxyz";

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
            if (i<2){
                 arr[i][j] = 2;
            }
            else if (i>=n-2 && i<=n-1){
                arr[i][j] = 1;
            } 
            else {
                arr[i][j] = 0;
            }
        }
    }
}


////  printing  ////  the  ////  board  ////
void print_board(int** arr, int n){
    char** board;
    board = malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        board[i] = malloc(sizeof(char) * n);
    }

    // Remplir la matrice board
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (arr[i][j] == 2)
                board[i][j] = 'B';
            else if (arr[i][j] == 1)
                board[i][j] = 'W';
            else
                board[i][j] = '.';
        }
    }

    int cell_width = (n > 9) ? 3 : 2; // Largeur minimale par case
    int left_margin = (n > 9) ? 4 : 3;

    // 1. Première ligne : tirets horizontaux
    printf("%*s", left_margin, ""); // marge gauche
    for (int j = 0; j < n; j++) {
        printf("%-*s", cell_width, "-");
    }
    printf("\n");

    // 2. Lignes de la grille avec numéros et bordures verticales
    for (int i = 0; i < n; i++) {
        printf("%*d|", left_margin - 1, n - i); // Numéro de ligne
        for (int j = 0; j < n; j++) {
            printf("%-*c", cell_width, board[i][j]);
        }
        printf("|\n");
    }

    // 3. Dernière ligne : tirets
    printf("%*s", left_margin, "");
    for (int j = 0; j < n; j++) {
        printf("%-*s", cell_width, "-");
    }
    printf("\n");

    // 4. Lignes des lettres (colonnes)
    printf("%*s", left_margin, "");
    for (int j = 0; j < n; j++) {
        printf("%-*c", cell_width, 'a' + j);
    }
    printf("\n");

    // Libération mémoire
    free_array((void**)board, n);
}


void free_array(void**arr, int n){
    for (int i=0; i<n; i++){
        free(arr[i]);
    }
    free(arr);
}



