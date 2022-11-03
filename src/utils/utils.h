#include <stdio.h>
#include <stdbool.h>

void init_game_board(char game_board[8][8]);
void init_game_board_from_string(char game_board[8][8], char *game_board_string);
void print_game(char game_board[8][8]);
bool coup_valide(char game_board[8][8], int x, int y, char joueur);
void jouer_coup(char game_board[8][8], int x, int y, char joueur);
void compute_legal_moves(char game_board[8][8], char actual_player, char (*legal_moves_board)[8]);
void board_copy(char game_board[8][8], char (*game_board_copy)[8]);
char get_opponent(char actual_player);