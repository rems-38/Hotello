#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <math.h>

int evaluation(char game_board[8][8], char player) {
    return get_score(game_board, player); // A chier
}

int minimax(int depth, char node[8][8], char player, bool maximizingPlayer) {
    int value;
    if (depth == 0 || is_win(node)) {
        return evaluation(node, player);
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
            value = max(value, minimax(depth - 1, node, player, false)); // ici node est comme un child_node (on passe à la branche suivante)
        }
    }
    else {
        value = INFINITY;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = min(value, minimax(depth - 1, node, player, true));
        }
    }
    board_copy(origin_board, node);
    return value;
}