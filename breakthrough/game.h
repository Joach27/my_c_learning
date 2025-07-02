// game.h
#ifndef GAME_H
#define GAME_H

int winner(int** board, int n); // check winner

bool is_in_the_board(int n, int x, int y); 

char* input_move();

void extract_pos(const char* pos_str, int n, int* i, int* j);

int check_move(int** board, int n, int player, char* move_str);

void play_move(int** board, int n, char* move_str, int player);
 
#endif // GAME_H