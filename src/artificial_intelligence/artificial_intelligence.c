#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <math.h>

int make_move_count(char game_board[8][8], int target_x, int target_y, char joueur, int moves_origins[8][8][9][2]) {
    int count = 0;
    int om_index = moves_origins[target_y][target_x][0][0];
    for(int i = 1; i < om_index; i++) {
        int x = moves_origins[target_y][target_x][i][0];
        int y = moves_origins[target_y][target_x][i][1];
        int delta_x = target_x - x;
        int delta_y = target_y - y;
        int dir_x = delta_x == 0 ? 0 : delta_x / abs(delta_x);
        int dir_y = delta_y == 0 ? 0 : delta_y / abs(delta_y);
        for(int i = 1; (0 <= x+i*dir_x && x+i*dir_x < 8) && (0 <= y+i*dir_y && y+i*dir_y < 8); i++) {
            int move_x = x+(i*dir_x);
            int move_y = y+(i*dir_y);
            count++;
            if(move_x == target_x && move_y == target_y) break;
        }
        count--;
    }
    return count;
}   

int evaluation(char game_board[8][8], char player, int *best_x, int *best_y) {
    int legal_moves[64][2];
    char legal_moves_board[8][8];
    int moves_origins[8][8][9][2];
    int lm_index = compute_legal_moves(game_board, player, legal_moves, moves_origins);

    return make_move_count(game_board, best_x, best_y, player, moves_origins);
}

int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int *best_x, int *best_y) {
    int value;
    if (depth == 0 || is_win(node)) {
        return evaluation(node, player, best_x, best_y);
    }
    int legal_moves[64][2];
    int moves_origins[8][8][9][2];
    int lm_index = compute_legal_moves(node, player, legal_moves, moves_origins);
    
    char origin_board[8][8];
    board_copy(node, origin_board);

    if (maximizingPlayer) {
        value = -INFINITY;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = max(value, minimax(depth - 1, node, player, false, best_x, best_y)); // ici node est comme un child_node (on passe à la branche suivante)
        }
    }
    else {
        value = INFINITY;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = min(value, minimax(depth - 1, node, player, true, best_x, best_y));
        }
    }
    board_copy(origin_board, node);
    return value;
}