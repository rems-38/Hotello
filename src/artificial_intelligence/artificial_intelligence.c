#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <stdlib.h>


bool is_in_coins(int x, int y) {
    int coins[4][2] = {{0,0}, {7,0}, {0,7}, {7,7}};    
    for(int i = 0; i < 4; i++) {
        if(coins[i][0] == x && coins[i][1] == y) {
            return true;
        }
    }
    return false;
}

int stability(char game_board[8][8], char player) {
    int stability = 0;
    bool coin = false;
    
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(game_board[y][x] == player) {
                if(is_in_coins(x, y)) {
                    stability += 300;
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
    int pieces_win = 0;
    int score = 0;
    for(int i = 0; i < lm_index; i++) {
        int x = legal_moves[i][0];
        int y = legal_moves[i][1];

        int new_pieces_win = make_move(temp_board, player, x, y, moves_origins); // Combien de pièces on a mangé avec ce coup (ie. indice de mangeabilité)
        if(new_pieces_win > pieces_win) {
            pieces_win = new_pieces_win;
        }
        
        board_copy(game_board, temp_board);
    }
    score = pieces_win + lm_index + stability_score; // Formule math à définir mieux (addition -> nul)


    return score;
}

int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int alpha, int beta) {
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
            value = max(value, minimax(depth - 1, node, get_opponent(player), !maximizingPlayer, alpha, beta)); // on passe au joueur suivant
            board_copy(origin_board, node);
            if(value >= beta) {
                return value;
            }
            alpha = max(alpha, value);
        }
    }
    else {
        value = 10000;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = min(value, minimax(depth - 1, node, get_opponent(player), !maximizingPlayer, alpha, beta)); // on passe au joueur suivant
            board_copy(origin_board, node);
            if (alpha >= value) {
                return value;
            }
            beta = min(beta, value);
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
        int score = minimax(depth-1, origin_board, get_opponent(player), false, 10000, -10000);
        if (score > best_score && rand() % 2 == 0) {
            best_score = score;
            *best_x = legal_moves[i][0];
            *best_y = legal_moves[i][1];
        }
        board_copy(game_board, origin_board);
    }
}