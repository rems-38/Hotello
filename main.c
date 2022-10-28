#include <stdio.h>
#include "core_game/functions/functions.h"

int game_board[8][8];

void main()
{
    init_game_board(game_board);
    print_game(game_board);
    
}