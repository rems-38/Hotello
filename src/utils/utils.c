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

void init_game_board_from_string(char game_board[8][8], char *game_board_moves) {
    // Forme de game_board_moves: "E6D5C4B3A2"
    // On initialise le tableau de jeu
    char colonnes[] = "ABCDEFGH";
    char player = 'O';
    init_game_board(game_board);
    for(int i = 0; i < strlen(game_board_moves); i += 2) {
        int x = strchr(colonnes, game_board_moves[i]) - colonnes;
        int y = (game_board_moves[i+1] - '0') - 1;
        // Jouer le coup
        player = get_opponent(player);
    }
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
        for(int j = 0; j < 8; j++) {
            printf("%c", game_board[i][j]);
        }
        printf("\n");
    }
}

char get_opponent(char pion) {
    if(pion == 'X') {
        return 'O';
    } else {
        return 'X';
    }
}




void make_move(char game_board[8][8], int x, int y, char joueur) {

    if (coup_valide(game_board, x, y, joueur)) {
        // Jouer le coup
        // Idée : diviser en 3 fonctions : vertical, horizontal, diagonal
    }
}

