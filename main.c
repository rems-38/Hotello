#include <stdio.h>
#include "core_game/functions/functions.h"

char game_board[8][8];
char legal_moves_board[8][8];

void main()
{
    init_game_board(game_board);
    print_game(game_board);
    board_copy(game_board, legal_moves_board);
    compute_legal_moves(game_board, 'O', legal_moves_board);
    printf("Coups légaux : \n");
    print_game(legal_moves_board);
}