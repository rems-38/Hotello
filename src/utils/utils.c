#include "utils.h"
#include <string.h>

void init_game_board(char game_board[8][8]) {
    // Remplir tout le tableau de tiret (case vide)
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game_board[i][j] = '-';
        }
    }

    // Faire l'initialisation des pions
    game_board[3][3] = 'X';
    game_board[3][4] = 'O';
    game_board[4][3] = 'O';
    game_board[4][4] = 'X';
}

void board_copy(char game_board[8][8], char (*game_board_copy)[8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            game_board_copy[i][j] = game_board[i][j];
        }
    }
}

void print_game(char game_board[8][8]) {
    for(int i = 0; i < 8; i++) {
        printf("|");
        for(int j = 0; j < 8; j++) {
            printf("%c|", game_board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

char get_opponent(char pion) {
    if(pion == 'X') {
        return 'O';
    } else {
        return 'X';
    }
}

