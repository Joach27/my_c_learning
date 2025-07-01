#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include <stdbool.h>

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
_Bool is_in_the_board(int n, int x, int y){
    
    if ((x >= 0 && x <= n-1) && (y >= 0 && y <= n-1)){
        return true;
    }
    return false;
}

// Input move (check the move format: a1>b2)
char* regex_input() {
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