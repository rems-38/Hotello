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
    // printf("(%d %d)\n", target_x, target_y);
    // printf("(%d %d)\n\n", moves_origins[target_y][target_x][1][0], moves_origins[target_y][target_x][1][1]);
    print_game(legal_moves_board);
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
    char game_board_moves[] = "E6D6C4F4F5D3F3G5C6C5F6G6E3G4B6D2E2C2G3E7F7E8B1C3B2D7C7A1";
    init_game_board_from_string(game_board, game_board_moves);
    print_game(game_board);

    char legal_moves_board[8][8];
    generate_legal_moves_board(game_board, player, legal_moves_board);
    print_game(legal_moves_board);
}