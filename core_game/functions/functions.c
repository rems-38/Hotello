#include "functions.h"

char *init_game_board(char game_board[8][8]) {
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

void print_game(char game_board[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%c", game_board[i][j]);
        }
        printf("\n");
    }
}

bool coup_valide(char game_board[8][8], int x, int y, char joueur) {
    return true;
}

char *jouer_coup(char game_board[8][8], int x, int y, char joueur) {

    if (coup_valide(game_board, x, y, joueur)) {
        // Jouer le coup

    }
}