#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "game.h"

int main()
{   
    // Demander la taille du plateau
    // Initialiser le plateau
    // Boucle de jeu :
    //   - Afficher le plateau
    //   - Demander un coup
    //   - Vérifier le format
    //   - Valider le coup
    //   - Appliquer le coup
    //   - Vérifier s'il y a un gagnant
    
    /* Defining players */
    int player1 = 1;
    int current_player = player1;
    int player2 = 2;
    
    char* move;
    
    int n;
    printf("Entrez la taille du plateaux : \n");
    scanf("%d", &n);
    while (getchar() != '\n'); // Ajoute ceci pour vider le tampon

    
    int** board;
    board = init_board(n);
    fill_array(board, n);
    
    while(1){
        print_board(board, n);
        printf("C'est au tour du jour %d de jouer\n", current_player);
        
        /* Ask for the move */
        move = input_move();
        
        /* check the move */
        int is_move_valide = check_move(board, n, current_player, move);
        
        while (is_move_valide != 1){
            printf("Coup non valide, ressayez : \n");
            free(move);
            move = input_move();
            is_move_valide = check_move(board, n, current_player, move);
        }
        
        /* Playing the move */
        play_move(board, n, move, current_player);
        free(move);
        
        /* Check for a winner */
        int winnerr = winner(board, n);
        if (winnerr == 1){
            print_board(board, n);
            printf("Le joueurs N°1 a gagné !\n");
            break;
        }
        else if (winnerr == 2){
            print_board(board, n);
            printf("Le joueurs N°2 a gagné !\n");
            break;
        }
        
        /* Changer player */
        current_player = (current_player == player1) ? player2 : player1;
    }
        
    
    free_array((void**)board, n);
    return 0;
}