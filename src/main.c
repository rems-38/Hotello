#include <stdio.h>
#include "utils/utils.h"
#include "legal_moves/legal_moves.h"

char game_board[8][8];
char legal_moves_board[8][8];

int main()
{
    init_game_board(game_board);
    print_game(game_board);
    printf("Coups légaux : \n");
    board_copy(game_board, legal_moves_board);
    compute_legal_moves(game_board, 'X', legal_moves_board);
    print_game(legal_moves_board);
}