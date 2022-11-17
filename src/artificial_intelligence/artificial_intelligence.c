#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <math.h>

int evaluation(char game_board[8][8], char player, int best_x, int best_y) {
    int legal_moves[64][2];
    char legal_moves_board[8][8];
    int moves_origins[8][8][9][2];
    int lm_index = compute_legal_moves(game_board, player, legal_moves, moves_origins);

    return make_move(game_board, best_x, best_y, player, moves_origins);
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