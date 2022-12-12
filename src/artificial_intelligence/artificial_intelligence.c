#include "../legal_moves/legal_moves.h"
#include "../make_move/make_move.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <stdlib.h>

#define cz {0,0}
#define cz2 {1, 0}
#define dz {cz2, cz, cz, cz, cz, cz, cz, cz, cz}
#define e_line {dz, dz, dz, dz, dz, dz, dz, dz}
#define e_movorigin {e_line, e_line, e_line, e_line, e_line, e_line, e_line, e_line}
#define e_lm {cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz}
#define e_bline {0,0,0,0,0,0,0,0}
#define e_board {e_bline, e_bline, e_bline, e_bline, e_bline, e_bline, e_bline, e_bline}

int force_array[8][8] = {
    {500,-75,30,10,10,30,-75,500},
    {-75,-175,0,0,0,0,-175,-75},
    {30,0,1,2,2,1,0,30},
    {10,0,2,16,16,2,0,10},
    {10,0,2,16,16,2,0,10},
    {30,0,1,2,2,1,0,30},
    {-75,-175,0,0,0,0,-175,-75},
    {500,-75,30,10,10,30,-75,500}
};


bool is_in_coins(int x, int y) {
    int coins[4][2] = {{0,0}, {7,0}, {0,7}, {7,7}};    
    for(int i = 0; i < 4; i++) {
        if(coins[i][0] == x && coins[i][1] == y) {
            return true;
        }
    }
    return false;
}

int force_measurement(char game_board[8][8], char player) {
    int force = 0;
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(game_board[y][x] == player) {
                force += force_array[y][x];
            }
        }
    }
    return force;
}

int stability(char game_board[8][8], char player) {
    int stability = 0;
    bool coin = false;
    
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            if(game_board[y][x] == player) {
                if(is_in_coins(x, y)) {
                    stability += 100;
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
                    if(is_stable) stability += 100;
                }
                    
            }
        }
    }
    return stability;
}

int evaluation(char game_board[8][8], char player) {
    int legal_moves[64][2] = e_lm;
    int moves_origins[8][8][9][2] = e_movorigin;

    int lm_index = compute_legal_moves(game_board, player, legal_moves, moves_origins); // Nombre de coup possible (ie. mobilité)
    int force_score = force_measurement(game_board, player);
    int pieces_win = get_score(game_board, player);
    float pieces_onboard = (get_score(game_board, player) + get_score(game_board, get_opponent(player)))/64;
    return pieces_onboard*force_score + (1-pieces_onboard)*(lm_index-1) + pieces_onboard*pieces_win;
}

int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int alpha, int beta, int *nb_nodes) {
    int value;
    *nb_nodes += 1;
    if (depth == 0 || is_win(node)) {
        return evaluation(node, player);
    }
    int legal_moves[64][2] = e_lm;
    int moves_origins[8][8][9][2] = e_movorigin;
    int lm_index = compute_legal_moves(node, player, legal_moves, moves_origins);
    
    char origin_board[8][8] = e_board;
    board_copy(node, origin_board);

    if (maximizingPlayer) {
        value = -10000;
        for (int i = 0; i < lm_index; i++) {
            make_move(node, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
            value = max(value, minimax(depth - 1, node, get_opponent(player), !maximizingPlayer, alpha, beta, nb_nodes)); // on passe au joueur suivant
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
            value = min(value, minimax(depth - 1, node, get_opponent(player), !maximizingPlayer, alpha, beta, nb_nodes)); // on passe au joueur suivant
            board_copy(origin_board, node);
            if (alpha >= value) {
                return value;
            }
            beta = min(beta, value);
        }
    }
    return value;
}



void compute_best_move(int depth, char game_board[8][8], char player, int *best_x, int *best_y, int *nb_nodes) {
    int legal_moves[64][2] = e_lm;
    int moves_origins[8][8][9][2] = e_movorigin;
    
    int best_score = -10000;
    char origin_board[8][8] = e_board;
    board_copy(game_board, origin_board);
    int lm_index = compute_legal_moves(origin_board, player, legal_moves, moves_origins);
    *best_x = legal_moves[0][0];
    *best_y = legal_moves[0][1];
    for (int i = 0; i < lm_index; i++) {
        make_move(origin_board, legal_moves[i][0], legal_moves[i][1], player, moves_origins);
        int score = minimax(depth-1, origin_board, get_opponent(player), false, -10000, 10000, nb_nodes);
        if(score == best_score && rand() % 2 == 0) {
            *best_x = legal_moves[i][0];
            *best_y = legal_moves[i][1];
        }
        else if (score > best_score) {
            best_score = score;
            *best_x = legal_moves[i][0];
            *best_y = legal_moves[i][1];
        }
        board_copy(game_board, origin_board);
    }
}