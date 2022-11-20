#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>

int stability(char game_board[8][8], char player) {
    int stability = 0;
    bool coin = false;

    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(game_board[y][x] == player) {
                if(x == 0 || x == 7 || y == 0 || y == 7) {
                    stability += 5;
                    coin = true;
                }
                if(coin) {
                    bool is_stable = true;
                    for(int dir_y = -1; dir_y <= 1; dir_y++) {
                        for(int dir_x = -1; dir_x <= 1; dir_x++) {
                            if(dir_y == 0 && dir_x == 0) continue;
                            if(y+dir_y < 0 || y+dir_y > 7 || y+dir_x < 0 || y+dir_x > 7) continue;
                            if(game_board[y+dir_y][x+dir_x] != player) {
                                is_stable = false;
                            }
                        }
                    }
                    if(is_stable) stability += 5;
                }
                    
            }
        }
    }
    return stability;
}

int evaluation(char game_board[8][8], char player) {
    int legal_moves[64][2];
    int moves_origins[8][8][9][2];

    char temp_board[8][8];
    board_copy(game_board, temp_board);

    int lm_index = compute_legal_moves(temp_board, player, legal_moves, moves_origins); // Nombre de coup possible (ie. mobilité)
    int stability_score = stability(temp_board, player); // normalement ça marche (mais IA super lente mtn)

    int score = 0;
    for(int i = 0; i < lm_index; i++) {
        int x = legal_moves[i][0];
        int y = legal_moves[i][1];

        int pieces_win = make_move(temp_board, player, x, y, moves_origins); // Combien de pièces on a mangé avec ce coup (ie. indice de mangeabilité)
        
        int new_score = pieces_win + lm_index + stability_score; // Formule math à définir mieux (addition -> nul)
        if(new_score > score) {
            score = new_score;
        }
        board_copy(game_board, temp_board);
    }

    return score;
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
        value = -10000;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = max(value, minimax(depth - 1, node, get_opponent(player), !maximizingPlayer)); // on passe au joueur suivant
            board_copy(origin_board, node);
        }
    }
    else {
        value = 10000;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = min(value, minimax(depth - 1, node, get_opponent(player), !maximizingPlayer)); // on passe au joueur suivant
            board_copy(origin_board, node);
        }
    }
    return value;
}

void compute_best_move(int depth, char game_board[8][8], char player, int *best_x, int *best_y) {
    int legal_moves[64][2];
    int moves_origins[8][8][9][2];
    
    int best_score = -10000;
    char origin_board[8][8];
    board_copy(game_board, origin_board);
    int lm_index = compute_legal_moves(origin_board, player, legal_moves, moves_origins);
    for (int i = 0; i < lm_index; i++) {
        make_move(origin_board, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
        int score = minimax(depth-1, origin_board, get_opponent(player), false);
        if (score > best_score) {
            best_score = score;
            *best_x = legal_moves[i][0];
            *best_y = legal_moves[i][1];
        }
        board_copy(game_board, origin_board);
    }
}