#include <stdbool.h>
#include "../utils/utils.h"


bool is_coord_exist(int array[64][2], int x, int y, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i][0] == x && array[i][1] == y) {
            return true;
        }
    }
    return false;
}

int compute_legal_moves(char game_board[8][8], char actual_player, int legal_moves[64][2], int moves_origins[8][8][9][2]) {
    for(int i = 0; i < 64; i++) {
        legal_moves[i][0] = 0;
        legal_moves[i][1] = 0;
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            moves_origins[i][j][0][0] = 1;
            moves_origins[i][j][0][1] = 0;
            for(int k = 1; k < 9; k++) {
                // On initialise tout à 0
                moves_origins[i][j][k][0] = 0;
                moves_origins[i][j][k][1] = 0;
            }
            
        }
    }


    int lm_index = 0;  // Index pour le tableau des mouvements possibles
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(game_board[y][x] == actual_player) {
                for(int dir_y = -1; dir_y <= 1; dir_y++) {
                    for(int dir_x = -1; dir_x <= 1; dir_x++) {
                        if(dir_y == 0 && dir_x == 0) continue;
                        if(y+dir_y < 0 || y+dir_y > 7 || x+dir_x < 0 || x+dir_x > 7) continue; // Si on est en dehors du plateau
                        if(game_board[y+dir_y][x+dir_x] != get_opponent(actual_player)) {
                            continue;
                        }
                        for(int i = 1; (0 <= x+i*dir_x && x+i*dir_x < 8) && (0 <= y+i*dir_y && y+i*dir_y < 8); i++) {
                            int move_x = x+(i*dir_x);
                            int move_y = y+(i*dir_y);
                            if(game_board[move_y][move_x] == actual_player) break;
                            if(game_board[move_y][move_x] == '-') {
                                if(!is_coord_exist(legal_moves, move_x, move_y, lm_index)) {
                                    legal_moves[lm_index][0] = move_x;
                                    legal_moves[lm_index][1] = move_y;
                                    lm_index++;
                                    // printf("Ajout de (%d %d)\n", move_x, move_y);
                                }

                                int mo_index = moves_origins[move_y][move_x][0][0];

                                moves_origins[move_y][move_x][mo_index][0] = x;
                                moves_origins[move_y][move_x][mo_index][1] = y;
                                moves_origins[move_y][move_x][0][0]++;

                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    return lm_index;
}

bool is_legal_move(char game_board[8][8], int target_x, int target_y, char actual_player, int moves_origins[8][8][9][2]) {
    if(target_x < 0 || target_x > 7 || target_y < 0 || target_y > 7) return false;
    if(game_board[target_y][target_x] != '-') return false;
    if(moves_origins[target_y][target_x][0][0] == 1) return false;
    return true;
}

void get_legal_moves_board(char game_board[8][8], char player, char legal_moves_board[8][8]) {
    int legal_moves[64][2] = {0};
    int moves_origins[8][8][9][2];
    int lm_index = compute_legal_moves(game_board, player, legal_moves, moves_origins);

    // for(int i = 0; i < 8; i++) {
    //     for(int j = 0; j < 8; j++) {
    //         if(moves_origins[i][j][0][0] > 1) {
    //             for(int k = 0; k < moves_origins[i][j][0][0]; k++) {
    //                 printf("(%d %d) with origins (%d %d)\n", j, i, moves_origins[i][j][k][0], moves_origins[i][j][k][1]);
    //             }
    //         }
    //     }
    // }
    // printf("Legal moves : \n");
    // for(int i = 0; i < lm_index; i++) {
    //     printf("(%d %d)\n", legal_moves[i][0], legal_moves[i][1]);
    // }
    // printf("\n");

    for(int i = 0; i < lm_index; i++) {
        legal_moves_board[legal_moves[i][1]][legal_moves[i][0]] = '*';
    }
}