#include <stdio.h>
#include "utils/utils.h"
#include "make_move/make_move.h"
#include "legal_moves/legal_moves.h"
#include <string.h>

char game_board[8][8];
char player = 'O';

void generate_legal_moves_board(char game_board[8][8], char player, char legal_moves_board[8][8]) {
    int moves_origins[8][8][9][2];
    board_copy(game_board, legal_moves_board);
    compute_legal_moves(game_board, player, legal_moves_board, moves_origins);
}


bool proceed_move(char game_board[8][8], char player, int target_x, int target_y) {
    char legal_moves_board[8][8];
    int moves_origins[8][8][9][2];
    board_copy(game_board, legal_moves_board);
    compute_legal_moves(game_board, player, legal_moves_board, moves_origins);
    if(legal_moves_board[target_y][target_x] == '*') {
        make_move(game_board, target_x, target_y, player, moves_origins);
        return true;
    }
    else {
        return false;
    }
}

void init_game_board_from_string(char game_board[8][8], char *game_board_moves) {
    // Forme de game_board_moves: "E6D5C4B3A2"
    // On initialise le tableau de jeu
    char colonnes[] = "ABCDEFGH";
    init_game_board(game_board);
    for(int i = 0; i < strlen(game_board_moves); i += 2) {
        int x = strchr(colonnes, game_board_moves[i]) - colonnes;
        int y = (game_board_moves[i+1] - '0') - 1;
        // printf("(%d %d)\n", x, y);
        // Jouer le coup
        proceed_move(game_board, player, x, y);
        player = get_opponent(player);
    }

} 


int main()
{
    char game_board_moves[] = "E6D6C5F4F5F6G5C4D3E3D7C6G4C3C7D8C8F3E8E7G3H4F8H2D2C2F7E1H3H5H1G6H6B8A8G7H8G8G2F2G1E2B3B4F1";
    init_game_board_from_string(game_board, game_board_moves);
    print_game(game_board);

    char legal_moves_board[8][8];
    generate_legal_moves_board(game_board, player, legal_moves_board);
    print_game(legal_moves_board);
}