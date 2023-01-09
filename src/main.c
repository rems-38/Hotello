#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils/utils.h"
#include "artificial_intelligence/artificial_intelligence.h"
#include "legal_moves/legal_moves.h"
#include "network/userNetwork.h"
#include "network/network.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h> // notice this! you need it!

#define cz {0,0}
#define cz2 {1, 0}
#define dz {cz2, cz, cz, cz, cz, cz, cz, cz, cz}
#define e_line {dz, dz, dz, dz, dz, dz, dz, dz}
#define e_movorigin {e_line, e_line, e_line, e_line, e_line, e_line, e_line, e_line}
#define e_lm {cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz, cz}
#define e_bline {0,0,0,0,0,0,0,0}
#define e_board {e_bline, e_bline, e_bline, e_bline, e_bline, e_bline, e_bline, e_bline}

char game_board[8][8] = e_board;
char player = 'O';
int nb_nodes = 0;

game *mynetgame;
#define BLACK 0
#define DEPTH 6

char pvp(char game_board[8][8]) {
    while (!is_win(game_board)){
        // Si aucun coup n'est possible, on passe au joueur suivant
        if(!has_legal_move(game_board, player)) player = get_opponent(player);

        char legal_moves_board[8][8] = e_board;
        generate_legal_moves_board(game_board, player, legal_moves_board);
        print_game(legal_moves_board);

        // Si on a que un coup possible, le programme le joue directement
        int legal_moves[64][2] = e_lm;
        int moves_origins[8][8][9][2] = e_movorigin;
        if(compute_legal_moves(game_board, player, legal_moves, moves_origins) == 1) {
            printf("Player %c, unique move possible is played : %c%c\n", player, legal_moves[0][0] + 'A', legal_moves[0][1] + '1');

            proceed_move(game_board, player, legal_moves[0][0], legal_moves[0][1]);
            player = get_opponent(player);
            continue;
        }
        
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
        int legal_moves[64][2] = e_lm;
        int moves_origins[8][8][9][2] = e_movorigin;
        if(compute_legal_moves(game_board, player, legal_moves, moves_origins) == 1) {
            char legal_moves_board[8][8] = e_board;
            generate_legal_moves_board(game_board, player, legal_moves_board);
            print_game(legal_moves_board);
            printf("Player %c, unique move possible is played : %c%c\n", player, legal_moves[0][0] + 'A', legal_moves[0][1] + '1');

            proceed_move(game_board, player, legal_moves[0][0], legal_moves[0][1]);
            player = get_opponent(player);
            continue;
        }

        int x = 0, y = 0;
        if(player == human) {
            char legal_moves_board[8][8] = e_board;
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
            compute_best_move(DEPTH, game_board, player, &x, &y, &nb_nodes);
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

char aivai(char game_board[8][8]) {
    while (!is_win(game_board)){
        // Si aucun coup n'est possible, on passe au joueur suivant
        if(!has_legal_move(game_board, player)) player = get_opponent(player);
        
        // Si on a que un coup possible, le programme le joue directement
        int legal_moves[64][2] = e_lm;
        int moves_origins[8][8][9][2] = e_movorigin;
        if(compute_legal_moves(game_board, player, legal_moves, moves_origins) == 1) {
            char legal_moves_board[8][8] = e_board;
            generate_legal_moves_board(game_board, player, legal_moves_board);
            print_game(legal_moves_board);
            printf("Player %c, unique move possible is played : %c%c\n", player, legal_moves[0][0] + 'A', legal_moves[0][1] + '1');

            proceed_move(game_board, player, legal_moves[0][0], legal_moves[0][1]);
            player = get_opponent(player);
            continue;
        }

        int x = 0, y = 0;

        print_game(game_board);
        printf("Player %c, IA is thinking...\n", get_opponent(player));
        compute_best_move(DEPTH, game_board, player, &x, &y, &nb_nodes);
           
        if(proceed_move(game_board, player, x, y)) {
            player = get_opponent(player);
        }
        else {
            printf("Illegal move, please try again.\n");
        }
    } 
    return get_score(game_board, 'X') > get_score(game_board, 'O') ? 'X' : 'O';
}

char mycolor;
char aivserver(game *g, char game_board[8][8]) {
    int move = 0;
    g = allocateGameOthello();

    g->address = "192.168.130.9";
    g->userId = 6;
    g->port = 8010;
    registerGameOthello(g, "A3lg8i");
    if(startGameOthello(g) < 0) {
        printf("Erreur de lancement");
    }

    printf("I am player %s\n",(g->myColor==BLACK)?"black":"white"); 
    player = g->myColor==BLACK ? 'O': 'X'; // black => 'O'
    mycolor = player;
    printf("I am %c and server is %c\n", player, get_opponent(player));

	// debut de partie
	while (g->state == PLAYING && !feof(stdin)) {
	 	if (g->myColor != g->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(g)) == 0 ) {
				printf("Game status %d: \t",g->state); 
                print_game(game_board);

				if (g->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",g->move,g->move%8,g->move/8); 
                    if(g->move == 64) {
                        printf("Opponent has no legal moves, pass.\n");
                        g->currentPlayer=!(g->currentPlayer);
                        continue;
                    }
                    int x = g->move%8;
                    int y = g->move/8;

                    proceed_move(game_board, get_opponent(player), x, y);
				}
			}
		}
	 	else {
            int x = 0, y = 0;
            print_game(game_board);
            printf("Player %c, IA is thinking...\n", player);
            if(!has_legal_move(game_board, player)) {
                g->move = 64;
                doMoveOthello(g);
                printf("No legal moves, pass.\n");
                g->currentPlayer=!(g->currentPlayer);  	// on change de joueur 
                continue;
            }
            compute_best_move(DEPTH, game_board, player, &x, &y, &nb_nodes);
            printf("Coup que je veux jouer : (%d %d)\n", x, y);
            proceed_move(game_board, player, x, y);
            print_game(game_board);
            g->move = y*8 + x;
			doMoveOthello(g);	// envoie du coup à l'adversaire
            nb_nodes = 0;
	   	}

		g->currentPlayer=!(g->currentPlayer);  	// on change de joueur 
        // player = get_opponent(player);
	} 

	// fin de partie 
	printf("Final game status = %d\n",g->state); 
	freeGameOthello(g);
    if(get_score(game_board, 'X') == get_score(game_board, 'O')) return 'N';
    return get_score(game_board, 'X') > get_score(game_board, 'O') ? 'X' : 'O';
}


// Trying to play against https://github.com/vmoucadeau/Reversi
char aivjava(char game_board[8][8], char aiplayer, int *newsocket) {
    char opponent = get_opponent(aiplayer);
    // if (rand() % 2 == 0) {
    //     opponent = 'X';
    // }
    sleep(1);
    printf("I am %c and client is %c\n", aiplayer, opponent);
    send_game_data(newsocket, opponent);
    while (!is_win(game_board)){
        if(!has_legal_move(game_board, player)) {
            printf("Player %c has no legal move, pass.\n", player);
            player = get_opponent(player);
        }
        if (player != opponent) {
            int x = 0, y = 0;
            printf("Player %c, IA is thinking...\n", player);
            compute_best_move(DEPTH, game_board, player, &x, &y, &nb_nodes);
            printf("Coup que je veux jouer : (%d %d)\n", x, y);
            printf("Nombre de noeuds : %d", nb_nodes);
            proceed_move(game_board, player, x, y);
            sleep(0.1);
            print_game(game_board);
            send_move(newsocket, x, y);
            nb_nodes = 0;
            player = get_opponent(player);
        } else {
            printf("Waiting client...\n");
            int x, y;
            receive_move(newsocket, &x, &y);
            proceed_move(game_board, player, x, y);
            print_game(game_board);
            player = get_opponent(player);
        }
    }

    if(get_score(game_board, 'X') == get_score(game_board, 'O')) return 'N';
    return get_score(game_board, 'X') > get_score(game_board, 'O') ? 'X' : 'O';
}

int get_win_rate(char game_board[8][8], char aiplayer, int nb_games) {
    int win = 0;
    int nulles = 0;
    // int newsocket;
    // init_socket(&newsocket);
    for (int i = 0; i < nb_games; i++) {
        init_game_board(game_board);
        // char winner = aivjava(game_board, aiplayer, &newsocket);
        char winner = aivserver(mynetgame, game_board);
        if (winner == mycolor) {
            win++;
        }
        if(winner == 'N') {
            nulles++;
        }
        player = 'O';
        printf("Number of wins : %d\n", win);
        printf("Number of draws : %d\n", nulles);
        sleep(1);
    }
    return win;
}

int main() {
    srand(time(NULL));
    init_game_board(game_board);
    // init_game_board_from_string(game_board, "E6D6C5F4F5F6G5C4D3E3D7C6G4C3C7D8C8F3E8E7G3H4F8H2D2C2F7E1H3H5H1G6H6B8A8G7H8G8G2F2G1E2B3B4F1");
    //init_game_board_from_string(game_board, "C4E3F4C5C6B5D6F6B4B3C3D3C2G5F5D7B7E2F3D2F2D1B2G4B6A2G3G2G1B8A3F1H2A5C1E6A6A1A8H3B1C7E1A7A4H1H4H5G6G7D8E7");
    
    // printf("Winner: %c\n", aivserver(mynetgame, game_board));
    // printf("Winner: %c", aivai(game_board));
    printf("Number of wins : %d", get_win_rate(game_board, 'O', 100));
}


