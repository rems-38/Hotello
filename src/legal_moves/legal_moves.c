#include <stdbool.h>
#include "../utils/utils.h"

void compute_legal_moves(char game_board[8][8], char actual_player, char (*legal_moves_board)[8], int moves_origins[8][8][9][2]) {
    int legal_moves[64][2];
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
                                legal_moves[lm_index][0] = move_x;
                                legal_moves[lm_index][1] = move_y;

                                int mo_index = moves_origins[move_y][move_x][0][0];

                                moves_origins[move_y][move_x][mo_index][0] = x;
                                moves_origins[move_y][move_x][mo_index][1] = y;
                                moves_origins[move_y][move_x][0][0]++;

                                lm_index++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i = 0; i < lm_index; i++) {
        legal_moves_board[legal_moves[i][1]][legal_moves[i][0]] = '*';
    }

    return;
}