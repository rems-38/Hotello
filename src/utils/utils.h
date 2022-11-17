#include <stdio.h>
#include <stdbool.h>

void init_game_board(char game_board[8][8]);
void init_game_board_from_string(char game_board[8][8], char *game_board_string);
void print_game(char game_board[8][8]);
bool coup_valide(char game_board[8][8], int x, int y, char joueur);
void jouer_coup(char game_board[8][8], int x, int y, char joueur);
void board_copy(char game_board[8][8], char (*game_board_copy)[8]);
char get_opponent(char actual_player);
int get_score(char game_board[8][8], char player);