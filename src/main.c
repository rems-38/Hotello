#include <stdio.h>
#include "utils/utils.h"
#include "legal_moves/legal_moves.h"

char game_board[8][8];
char legal_moves_board[8][8];

int main()
{
    char game_board_moves[] = "F5D6C6F4D7F6F3E3G3C5D2E2D3C4E6E7C7G4E1D8H4B5G5G6C8B7F2G2H3H2H1G1F1D1C1F7B8A8C3B6H5C2B1A7A6B3B2B4A3A1A2A4A5F8G7H6H7H8E8G8";
    init_game_board_from_string(game_board, game_board_moves);
    print_game(game_board);
}