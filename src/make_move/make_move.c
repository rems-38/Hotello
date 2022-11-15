#include<stdbool.h>
#include<stdio.h>

void make_horizontal_move(char game_board[8][8], int origin_x, int origin_y, int target_x, int target_y, char joueur) {
    bool direction = (origin_x < target_x);
    if(direction) {
        for(int i = origin_x + 1; i < target_x; i++) {
            game_board[origin_y][i] = joueur;
        }
    } else {
        for(int i = origin_x - 1; i > target_x; i--) {
            game_board[origin_y][i] = joueur;
        }
    }
}

void make_vertical_move(char game_board[8][8], int origin_x, int origin_y, int target_x, int target_y, char joueur) {
    bool direction = (origin_y < target_y);
    if(direction) {
        for(int i = origin_y + 1; i < target_y; i++) {
            game_board[i][origin_x] = joueur;
        }
    } else {
        for(int i = origin_y - 1; i > target_y; i--) {
            game_board[i][origin_x] = joueur;
        }
    }
}

void make_diagonal_move(char game_board[8][8], int origin_x, int origin_y, int target_x, int target_y, char joueur) {
    bool dir_x = (origin_x < target_x);
    bool dir_y = (origin_y < target_y);
    if(dir_x && !dir_y) {
        for(int x = origin_x + 1, y = origin_y - 1; x < target_x && y > target_y; x++, y--) {
            game_board[y][x] = joueur;
        }
    }
    if(dir_x && dir_y) {
        for(int x = origin_x + 1, y = origin_y + 1; x < target_x && y < target_y; x++, y++) {
            game_board[y][x] = joueur;
        }
    }
    if(!dir_x && dir_y) {
        for(int x = origin_x - 1, y = origin_y + 1; x > target_x && y < target_y; x--, y++) {
            game_board[y][x] = joueur;
        }
    }
    if(!dir_x && !dir_y) {
        for(int x = origin_x - 1, y = origin_y - 1; x > target_x && y > target_y; x--, y--) {
            game_board[y][x] = joueur;
        }
    }
}

void make_move(char game_board[8][8], int target_x, int target_y, char joueur, int moves_origins[8][8][9][2]) {
    int om_index = moves_origins[target_y][target_x][0][0];
    for(int i = 1; i < om_index; i++) {
        int origin_x = moves_origins[target_y][target_x][i][0];
        int origin_y = moves_origins[target_y][target_x][i][1];
        bool horizontal_move = (origin_y == target_y);
        bool vertical_move = (origin_x == target_x);
        bool diagonal_move = (!horizontal_move && !vertical_move);
        if(horizontal_move) {
            make_horizontal_move(game_board, origin_x, origin_y, target_x, target_y, joueur);
        }
        if(vertical_move) {
            make_vertical_move(game_board, origin_x, origin_y, target_x, target_y, joueur);
        }
        if(diagonal_move) {
            make_diagonal_move(game_board, origin_x, origin_y, target_x, target_y, joueur);
        }
        game_board[target_y][target_x] = joueur;
    }
    return;
}   