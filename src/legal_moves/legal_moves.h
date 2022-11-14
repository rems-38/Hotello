void compute_legal_moves(char game_board[8][8], char actual_player, char (*legal_moves_board)[8], int moves_origins[8][8][9][2]);
bool coup_valide(char game_board[8][8], int x, int y, char joueur);