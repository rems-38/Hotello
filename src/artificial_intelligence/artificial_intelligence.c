#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>

int evaluation(char game_board[8][8], char player) {
    return get_score(game_board, player); // A chier
}

int minimax(int depth, char game_board[8][8], char player, int *max_score, int *best_x, int *best_y, bool maximizing_player) {
    if(depth == 0 || is_win(game_board)) {
        return max_score;
    }
    int legal_moves[64][2];
    int moves_origins[8][8][9][2];
    int lm_index = compute_legal_moves(game_board, player, legal_moves, moves_origins);
    int score = evaluation(game_board, player);
    if(maximizing_player) {
        char origin_board[8][8];
        board_copy(game_board, origin_board);
        for(int i = 0; i < lm_index; i++) {
            int target_x = legal_moves[i][0];
            int target_y = legal_moves[i][0];
            make_move(game_board, target_x, target_y, player, moves_origins);
            // passer à la branche suivante
            // on revient à l'origine pour tester le prochain coup
            board_copy(origin_board, game_board);
        }
    }
}