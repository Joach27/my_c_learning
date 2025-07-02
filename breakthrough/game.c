#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include "utils.h"
#include "game.h"


// Checking the winner
int winner(int** board, int n)
{
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (board[i][j] == 1 && i == n-1){
                return 1;
            }
            else if (board[i][j] == 2 && i == 0) {
                return 2;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

// Check if the position is on the board
bool is_in_the_board(int n, int x, int y){
    
    if ((x >= 0 && x <= n-1) && (y >= 0 && y <= n-1)){
        return true;
    }
    return false;
}

// Input move (check the move format: a1>b2)
char* input_move() {
    const char* pattern = "([a-z])(1[0-9]|2[0-6]|[1-9])>([a-z])(1[0-9]|2[0-6]|[1-9])";
    regex_t regex;
    regmatch_t matches[5];
    
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Erreur de compilation de la regex\n");
        return NULL;
    }

    char input[30];
    do {
        printf("Entrez une chaîne de caractères : ");
        fgets(input, sizeof(input), stdin);
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }

        if (regexec(&regex, input, 5, matches, 0) != 0) {
            printf("Format incorrect, veuillez réessayer.\n");
        }
    } while (regexec(&regex, input, 5, matches, 0) != 0);

    regfree(&regex);

    char* final_input = malloc(strlen(input) + 1);
    if (final_input != NULL) {
        strcpy(final_input, input);
    }

    return final_input;
}

// Extract the position
void extract_pos(const char* pos_str, int n, int* i, int* j) {
    if (!pos_str || strlen(pos_str) < 2) {
        *i = -1;
        *j = -1;
        return;  // position invalide
    }

    *j = pos_str[0] - 'a';          // colonne (lettre)

    int row = atoi(pos_str + 1);   // ligne (plusieurs chiffres possibles) [Commence à pos_str[1]]
    *i = n - row;                  // convertir vers indice de matrice
}

// Cheking the move int check_move : vérifie si les coups respectent les règles
int check_move(int** board, int n, int player, char* move_str)
{
    // move format : a1>b2
    char* source;
    copy_until(source, move_str, '>');
    
    int len_source = strlen(source);
    char* destination = move_str+(len_source+1);
    
    // Extrating positions
    int i_source, j_source;
    extract_pos(source, n, &i_source, &j_source);
    
    int i_destination, j_destination;
    extract_pos(destination, n, &i_destination, &j_destination);
    
    if ((player == 1) && (i_source < i_destination) && is_in_the_board(n, i_source, j_source) && is_in_the_board(n, i_destination, j_destination))
    { 
        if ((board[i_destination][j_destination] == 0 || board[i_destination][j_destination] == 2) && ((j_destination == j_source + 1 || j_destination == j_source - 1 || j_destination == j_source)) ){
            return 1;
        }
    }
    if ((player == 2) && (i_source > i_destination) && is_in_the_board(n, i_source, j_source) && is_in_the_board(n, i_destination, j_destination))
    { 
        if ((board[i_destination][j_destination] == 0 || board[i_destination][j_destination] == 1) && ((j_destination == j_source + 1 || j_destination == j_source - 1 || j_destination == j_source)) ){
            return 1;
        }
    }

    return 0;
}

// void play_move: Met à jour le plateau après un coup valide
void play_move(int** board, int n, char* move_str, int player)
{
    // move format : a1>b2
    char* source;
    copy_until(source, move_str, '>');
    
    int len_source = strlen(source);
    char* destination = move_str+(len_source+1);
    
    // Extrating positions
    int i_source, j_source;
    extract_pos(source, n, &i_source, &j_source);
    
    int i_destination, j_destination;
    extract_pos(destination, n, &i_destination, &j_destination);
    
    
    int valide_coup = check_move(board, n, player, move_str);
    
    if (valide_coup == 1){
        board[i_destination][j_destination] = player;
    }
}