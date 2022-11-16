#include <stdbool.h>
#include "../utils/utils.h"


int compute_vertical_moves(char game_board[8][8], int pion_x, int pion_y, char actual_player, char (*legal_moves)[2]) {
    int vm_index = 0;  // Index pour le tableau des mouvements possibles
    if(game_board[pion_y][pion_x] != actual_player) {
        return vm_index;
    }
    bool adv_pion_found = false;
    for(int i = pion_y+1; i < 8; i++) { // On regarde vers le bas
        if(game_board[i][pion_x] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[i][pion_x] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[i][pion_x] == '-') {
                legal_moves[vm_index][0] = pion_x;
                legal_moves[vm_index][1] = i;
                vm_index++;
                break;
            }
        }  
    }
    adv_pion_found = false;
    for(int i = pion_y-1; i >= 0; i--) { // On regarde vers le haut
        if(game_board[i][pion_x] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[i][pion_x] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[i][pion_x] == '-') {
                legal_moves[vm_index][0] = pion_x;
                legal_moves[vm_index][1] = i;
                vm_index++;
                break;
            }
        }  
    }
    return vm_index;
}

int compute_horizontal_moves(char game_board[8][8], int pion_x, int pion_y, char actual_player, char (*legal_moves)[2]) {
    int hm_index = 0;  // Index pour le tableau des mouvements possibles
    if(game_board[pion_y][pion_x] != actual_player) {
        return hm_index;
    }
    bool adv_pion_found = false;
    for(int i = pion_x+1; i < 8; i++) { // On regarde vers le bas
        if(game_board[pion_y][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[pion_y][i] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[pion_y][i] == '-') {
                legal_moves[hm_index][0] = i;
                legal_moves[hm_index][1] = pion_y;
                hm_index++;
                break;
            }
        }  
    }
    adv_pion_found = false;
    for(int i = pion_x-1; i >= 0; i--) { // On regarde vers le haut
        if(game_board[pion_y][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[pion_y][i] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[pion_y][i] == '-') {
                legal_moves[hm_index][0] = i;
                legal_moves[hm_index][1] = pion_y;
                hm_index++;
                break;
            }
        }  
    }
    return hm_index;
}

int compute_diagonal_moves(char game_board[8][8], int pion_x, int pion_y, char actual_player, char (*legal_moves)[2]) {
    int dm_index = 0;  // Index pour le tableau des mouvements possibles
    if(game_board[pion_y][pion_x] != actual_player) {
        return dm_index;
    }
    bool adv_pion_found = false;
    for(int i = pion_x+1, j = pion_y+1; i < 8 && j < 8; i++, j++) { // Dir : bas-droite
        if(game_board[j][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[j][i] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[j][i] == '-') {
                legal_moves[dm_index][0] = i;
                legal_moves[dm_index][1] = j;
                dm_index++;
                break;
            }
        }  
    }
    adv_pion_found = false;
    for(int i = pion_x-1, j = pion_y-1; i >= 0 && j >= 0; i--, j--) { // Dir : haut-gauche
        if(game_board[j][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[j][i] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[j][i] == '-') {
                legal_moves[dm_index][0] = i;
                legal_moves[dm_index][1] = j;
                dm_index++;
                break;
            }
        }  
    }
    adv_pion_found = false;
    for(int i = pion_x-1, j = pion_y+1; i >= 0 && j < 8; i--, j++) { // Dir : bas-gauche
        if(game_board[j][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[j][i] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[j][i] == '-') {
                legal_moves[dm_index][0] = i;
                legal_moves[dm_index][1] = j;
                dm_index++;
                break;
            }
        }
    }
    adv_pion_found = false;
    for(int i = pion_x+1, j = pion_y-1; i < 8 && j >= 0; i++, j--) { // Dir : haut-droite
        if(game_board[j][i] == actual_player) {
            break;
        }
        if(!adv_pion_found) {
            if(game_board[j][i] == get_opponent(actual_player)) {
                adv_pion_found = true;
            }
        }
        else {
            if(game_board[j][i] == '-') {
                legal_moves[dm_index][0] = i;
                legal_moves[dm_index][1] = j;
                dm_index++;
                break;
            }
        }
    }
    return dm_index;
}

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
                
                char vertical_moves[2][2];
                int vm_index = compute_vertical_moves(game_board, x, y, actual_player, vertical_moves);
                for(int k = 0; k < vm_index; k++) {
                    int move_x = vertical_moves[k][0];
                    int move_y = vertical_moves[k][1];
                    legal_moves[lm_index][0] = move_x;
                    legal_moves[lm_index][1] = move_y;

                    int mo_index = moves_origins[move_y][move_x][0][0];
                    moves_origins[move_y][move_x][mo_index][0] = x;
                    moves_origins[move_y][move_x][mo_index][1] = y;
                    moves_origins[move_y][move_x][0][0]++;
                    
                    lm_index++;
                }

                char horizontal_moves[2][2];
                int hm_index = compute_horizontal_moves(game_board, x, y, actual_player, horizontal_moves);
                for(int k = 0; k < hm_index; k++) {
                    int move_x = horizontal_moves[k][0];
                    int move_y = horizontal_moves[k][1];
                    legal_moves[lm_index][0] = move_x;
                    legal_moves[lm_index][1] = move_y;
                    
                    int mo_index = moves_origins[move_y][move_x][0][0];
                    moves_origins[move_y][move_x][mo_index][0] = x;
                    moves_origins[move_y][move_x][mo_index][1] = y;
                    moves_origins[move_y][move_x][0][0]++;

                    lm_index++;
                }

                char diagonal_moves[4][2];
                int dm_index = compute_diagonal_moves(game_board, x, y, actual_player, diagonal_moves);
                for(int k = 0; k < dm_index; k++) {
                    int move_x = diagonal_moves[k][0];
                    int move_y = diagonal_moves[k][1];
                    
                    legal_moves[lm_index][0] = move_x;
                    legal_moves[lm_index][1] = move_y;

                    int mo_index = moves_origins[move_y][move_x][0][0];

                    moves_origins[move_y][move_x][mo_index][0] = x;
                    moves_origins[move_y][move_x][mo_index][1] = y;
                    moves_origins[move_y][move_x][0][0]++;
                
                    
                    
                    lm_index++;
                }
                
            }
        }
    }

    for(int i = 0; i < lm_index; i++) {
        legal_moves_board[legal_moves[i][1]][legal_moves[i][0]] = '*';
    }

    return;
}