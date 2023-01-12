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
            {100 , -10 , 8  ,  6 ,  6 , 8  , -10 ,  100},
            {-10 , -35 ,  -4, -4 , -4 , -4 , -35 , -10 },
            {8   ,  -4 ,   6,   4,   4,   6,  -4 ,  8  },
            {6   ,  -4 ,   4,   0,   0,   4,  -4 ,  6  },
            {6   ,  -4 ,   4,   0,   0,   4,  -4 ,  6  },
            {8   ,  -4 ,   6,   4,   4,   6,  -4 ,  8  },
            {-10 , -35 ,  -4, -4 , -4 , -4 , -35 , -10 },
            {100 , -10 , 8  ,  6 ,  6 , 8  , -10 ,  100}
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
    int coins[4][2] = {{0,0}, {7,0}, {0,7}, {7,7}};    
    
    for(int i = 0; i < 4; i++) {
        if(game_board[coins[i][1]][coins[i][0]] == player) {
            coin = true;
            stability += 100;
        }
    }
    
    if(coin) {
        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                if(game_board[y][x] == player) {
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
                        if(is_stable) stability += 10;
                }
            }
        }

    }

    return stability;
}

// int evaluation(char game_board[8][8], char player) {
//     int legal_moves[64][2] = e_lm;
//     int moves_origins[8][8][9][2] = e_movorigin;

//     int mobility = compute_legal_moves(game_board, player, legal_moves, moves_origins); // Nombre de coup possible (ie. mobilité)
//     int force_score = force_measurement(game_board, player) - force_measurement(game_board, get_opponent(player));
//     int pieces_win = get_score(game_board, player);

//     int my_stab_score = stability(game_board, player);
//     int opponent_stab_score = stability(game_board, get_opponent(player));
//     int stability_score = 100*(my_stab_score - opponent_stab_score)/(my_stab_score + opponent_stab_score + 1);

//     float pieces_onboard = (get_score(game_board, player) + get_score(game_board, get_opponent(player)))/64; // Représente l'avencement de la partie (pourcentage de pièces sur le plateau)

//     return 1*force_score + 3*(1-pieces_onboard)*(mobility) + 1*(pieces_onboard)*pieces_win + 2*(pieces_onboard)*stability_score;
// }

int evaluation(char game_board[8][8], char player) {
    int legal_moves[64][2] = e_lm;
    int moves_origins[8][8][9][2] = e_movorigin;

    // Tester pour voir le meilleur des deux
    float game_progress = (get_score(game_board, player) + get_score(game_board, get_opponent(player)))/64; // Représente l'avencement de la partie (pourcentage de pièces sur le plateau)
    // float game_progress = played_moves/64; // Représente l'avencement de la partie (pourcentage de coups joués) (c'est nul)

    int my_mobility = compute_legal_moves(game_board, player, legal_moves, moves_origins); // Nombre de coup possible (ie. mobilité)
    int op_mobility = compute_legal_moves(game_board, get_opponent(player), legal_moves, moves_origins); // Mobilité de l'adversaire
    int mobility_score = game_progress > 0.5 ? 0 : 100*(my_mobility - op_mobility)/(my_mobility + op_mobility + 1); // Score de mobilité

    int my_force_score = force_measurement(game_board, player); // Force du plateau (somme des forces des pièces)
    int op_force_score = force_measurement(game_board, get_opponent(player));
    int force_score = my_force_score - op_force_score;

    int my_pieces_score = get_score(game_board, player);
    int op_pieces_score = get_score(game_board, get_opponent(player));
    int pieces_score = game_progress < 0.7 ? 0 : 100*(my_pieces_score - op_pieces_score)/(my_pieces_score + op_pieces_score + 1); // Score de pièces

    int my_stab_score = stability(game_board, player);
    int opponent_stab_score = stability(game_board, get_opponent(player));
    int stability_score = game_progress < 0.2 ? 0 : 100*(my_stab_score - opponent_stab_score)/(my_stab_score + opponent_stab_score + 1);

    

    return force_score + 1.5*mobility_score + pieces_score + 1.5*stability_score;
}

int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int alpha, int beta, int *nb_nodes) {
    int value;
    *nb_nodes += 1;
    if (depth == 0 || is_win(node)) {
        if (maximizingPlayer) {
            return evaluation(node, player);
        } else return evaluation(node, get_opponent(player));
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


bool killer_move_check(char game_board[8][8], char player, int x, int y) {
    if (!has_legal_move(game_board, get_opponent(player))) return true; // Si le coup empêche l'adversaire de jouer, on le joue
    // Si on peut placer un pion dans un coin, on le joue
    if(is_in_coins(x, y)) return true;
    return false;
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
        if(killer_move_check(origin_board, player, legal_moves[i][0], legal_moves[i][1])) {
            *best_x = legal_moves[i][0];
            *best_y = legal_moves[i][1];
            return;
        }
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