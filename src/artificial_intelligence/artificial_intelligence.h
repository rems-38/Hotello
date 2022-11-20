int stability(char game_board[8][8], char player);
int evaluation(char game_board[8][8], char player, int best_x, int best_y);
int minimax(int depth, char node[8][8], char player, bool maximizingPlayer, int *best_x, int *best_y);
void compute_best_move(int depth, char game_board[8][8], char player, int *best_x, int *best_y);