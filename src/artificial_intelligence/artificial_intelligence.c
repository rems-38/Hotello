#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>

int evaluation(char game_board[8][8], char player) {
    int legal_moves[64][2];
    int moves_origins[8][8][9][2];
    char temp_board[8][8];
    board_copy(game_board, temp_board);
    int lm_index = compute_legal_moves(temp_board, player, legal_moves, moves_origins);
    int score = 0;
    for(int i = 0; i < lm_index; i++) {
        int x = legal_moves[i][0];
        int y = legal_moves[i][1];
        int new_score = make_move(temp_board, player, x, y, moves_origins);
        if(new_score > score) {
            score = new_score;
        }
    }

    return score;
}

int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int *best_x, int *best_y) {
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
        value = -10000;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            int tmp = minimax(depth - 1, node, get_opponent(player), false, best_x, best_y); // on passe au joueur suivant
            if (tmp > value) {
                value = tmp;
                *best_x = legal_moves[i][0];
                *best_y = legal_moves[i][1];
            }
            board_copy(origin_board, node);
        }
    }
    else {
        value = 10000;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            int tmp = minimax(depth - 1, node, get_opponent(player), true, best_x, best_y); // on passe au joueur suivant
            if (tmp > value) {
                value = tmp;
                *best_x = legal_moves[i][0];
                *best_y = legal_moves[i][1];
            }
            board_copy(origin_board, node);
        }
    }
    return value;
}