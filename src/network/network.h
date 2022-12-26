void init_socket(int *newsockfd);
void receive_move(int *newsockfd, int *move_x, int *move_y);
void send_game_data(int *newsockfd, char opponent_color);
void send_move(int *newsockfd, int move_x, int move_y);