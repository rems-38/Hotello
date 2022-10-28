#include <stdio.h>
#include <stdbool.h>

char *init_game_board(char game_board[8][8]);
void print_game(char game_board[8][8]);
bool coup_valide(char game_board[8][8], int x, int y, char joueur);
char *jouer_coup(char game_board[8][8], int x, int y, char joueur);
