#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils/utils.h"
#include "artificial_intelligence/artificial_intelligence.h"

char game_board[8][8];
char player = 'O';

char pvp(char game_board[8][8]) {
    while (!is_win(game_board)){
        if(!has_legal_move(game_board, player)) player = get_opponent(player);

        char legal_moves_board[8][8];
        generate_legal_moves_board(game_board, player, legal_moves_board);
        print_game(legal_moves_board);

        printf("Player %c, please enter your move: ", player);
        char move[3];
        scanf("%s", move);
        
        int x = move[0] - 'A';
        int y = move[1] - '1';
        
        if(proceed_move(game_board, player, x, y)) {
            player = get_opponent(player);
        }
        else {
            printf("Illegal move, please try again.\n");
        }
    } 
    return get_score(game_board, 'X') > get_score(game_board, 'O') ? 'X' : 'O';
}


char pvai(char game_board[8][8], char human) {
    while (!is_win(game_board)){
        // Si aucun coup n'est possible, on passe au joueur suivant
        if(!has_legal_move(game_board, player)) player = get_opponent(player);
        
        // Si on a que un coup possible, le programme le joue directement
        int legal_moves[64][2];
        int moves_origins[8][8][9][2];
        if(compute_legal_moves(game_board, player, legal_moves, moves_origins) == 1) {
            char legal_moves_board[8][8];
            generate_legal_moves_board(game_board, player, legal_moves_board);
            print_game(legal_moves_board);
            printf("Player %c, only move possible is played : %c%c\n", player, legal_moves[0][0] + 'A', legal_moves[0][1] + '1');

            proceed_move(game_board, player, legal_moves[0][0], legal_moves[0][1]);
            player = get_opponent(player);
            continue;
        }

        int x = 0, y = 0;
        if(player == human) {
            char legal_moves_board[8][8];
            generate_legal_moves_board(game_board, player, legal_moves_board);
            print_game(legal_moves_board);

            printf("Player %c, please enter your move: ", player);
            char move[3];
            scanf("%s", move);
            
            x = move[0] - 'A';
            y = move[1] - '1';
        }
        else {
            print_game(game_board);
            printf("Player %c, IA is thinking...\n", player);
            compute_best_move(6, game_board, player, &x, &y);
        }
           
        if(proceed_move(game_board, player, x, y)) {
            player = get_opponent(player);
        }
        else {
            printf("Illegal move, please try again.\n");
        }
    } 
    return get_score(game_board, 'X') > get_score(game_board, 'O') ? 'X' : 'O';
}

int main() {
    init_game_board(game_board);
    // init_game_board_from_string(game_board, "E6D6C5F4F5F6G5C4D3E3D7C6G4C3C7D8C8F3E8E7G3H4F8H2D2C2F7E1H3H5H1G6H6B8A8G7H8G8G2F2G1E2B3B4F1");
    printf("Winner: %c", pvai(game_board, 'O'));
}