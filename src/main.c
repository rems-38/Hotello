#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils/utils.h"
#include "make_move/make_move.h"
#include "legal_moves/legal_moves.h"
#include "network/network.h"

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
        // Jouer le coup
        proceed_move(game_board, player, x, y);
        player = get_opponent(player);
    }

} 

bool is_win(char game_board[8][8], char player) {
    char legal_moves_board[8][8];
    generate_legal_moves_board(game_board, player, legal_moves_board);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (legal_moves_board[i][j] == '*') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // init_game_board(game_board);
    init_game_board_from_string(game_board, "E6D6C5F4F5F6G5C4D3E3D7C6G4C3C7D8C8F3E8E7G3H4F8H2D2C2");
    print_game(game_board);
    // while (!is_win(game_board, player)){
    //     char legal_moves_board[8][8];
    //     generate_legal_moves_board(game_board, player, legal_moves_board);
    //     print_game(legal_moves_board);

    //     printf("Player %c, please enter your move: ", player);
    //     char move[3];
    //     scanf("%s", move);
        
    //     int x = move[0] - 'A';
    //     int y = move[1] - '1';
        
    //     if(proceed_move(game_board, player, x, y)) {
    //         player = get_opponent(player);
    //     }
    //     else {
    //         printf("Illegal move, please try again.\n");
    //     }
    // } 
}