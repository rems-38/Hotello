#include "utils.h"
#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include <string.h>

#define cz {0,0}
#define cz2 {1, 0}
#define dz {cz2, cz, cz, cz, cz, cz, cz, cz, cz}
#define e_line {dz, dz, dz, dz, dz, dz, dz, dz}
#define e_movorigin {e_line, e_line, e_line, e_line, e_line, e_line, e_line, e_line}
#define e_lm {cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz}
#define e_bline {0,0,0,0,0,0,0,0}
#define e_board {e_bline, e_bline, e_bline, e_bline, e_bline, e_bline, e_bline, e_bline}

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
    printf("\n   A B C D E F G H\n");
    for(int i = 0; i < 8; i++) {
        printf("%d |", i+1);
        for(int j = 0; j < 8; j++) {
            printf("%c|", game_board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

char get_opponent(char pion) {
    return (pion == 'O') ? 'X' : 'O';
}

int get_score(char game_board[8][8], char player) {
    int score = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(game_board[i][j] == player) {
                score++;
            }
        }
    }
    return score;
}


bool has_legal_move(char game_board[8][8], char player) {
    int legal_moves[64][2] = e_lm;
    int moves_origins[8][8][9][2] = e_movorigin;
    compute_legal_moves(game_board, player, legal_moves, moves_origins);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(is_legal_move(game_board, i, j, player, moves_origins)) return true;
        }
    }
    return false;
}

bool is_win(char game_board[8][8]) {
    return !has_legal_move(game_board, 'O') && !has_legal_move(game_board, 'X');
}

void generate_legal_moves_board(char game_board[8][8], char player, char legal_moves_board[8][8]) {
    board_copy(game_board, legal_moves_board);
    get_legal_moves_board(game_board, player, legal_moves_board);
}

bool proceed_move(char game_board[8][8], char player, int target_x, int target_y) {
    int moves_origins[8][8][9][2] = e_movorigin;
    int legal_moves[64][2] = e_lm;
    compute_legal_moves(game_board, player, legal_moves, moves_origins);
    if(is_legal_move(game_board, target_x, target_y, player, moves_origins)) {
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
    char player = 'O';
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

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}