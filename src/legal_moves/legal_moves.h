#include <stdbool.h>

int compute_legal_moves(char game_board[8][8], char actual_player, int legal_moves[64][2], int moves_origins[8][8][9][2]);
void get_legal_moves_board(char game_board[8][8], char player, char legal_moves_board[8][8]);
bool is_legal_move(char game_board[8][8], int target_x, int target_y, char actual_player, int moves_origins[8][8][9][2]);