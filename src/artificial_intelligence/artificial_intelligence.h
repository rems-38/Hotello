int evaluation(char game_board[8][8], char player, int best_x, int best_y);
int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int *best_x, int *best_y);