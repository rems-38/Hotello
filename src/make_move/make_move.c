#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int make_move(char game_board[8][8], int target_x, int target_y, char joueur, int moves_origins[8][8][9][2]) {
    int count = 0;
    int om_index = moves_origins[target_y][target_x][0][0];
    for(int i = 1; i < om_index; i++) {
        int x = moves_origins[target_y][target_x][i][0];
        int y = moves_origins[target_y][target_x][i][1];
        int delta_x = target_x - x;
        int delta_y = target_y - y;
        int dir_x = delta_x == 0 ? 0 : delta_x / abs(delta_x);
        int dir_y = delta_y == 0 ? 0 : delta_y / abs(delta_y);
        for(int i = 1; (0 <= x+i*dir_x && x+i*dir_x < 8) && (0 <= y+i*dir_y && y+i*dir_y < 8); i++) {
            int move_x = x+(i*dir_x);
            int move_y = y+(i*dir_y);
            game_board[move_y][move_x] = joueur;
            count++;
            if(move_x == target_x && move_y == target_y) break;
        }
        count--;
    }
    return count;
}   