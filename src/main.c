#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "utils/utils.h"
#include "artificial_intelligence/artificial_intelligence.h"
#include "legal_moves/legal_moves.h"
#include "network/userNetwork.h"

char game_board[8][8];
char player = 'O';

game *mynetgame;
#define BLACK 0

char pvp(char game_board[8][8]) {
    while (!is_win(game_board)){
        // Si aucun coup n'est possible, on passe au joueur suivant
        if(!has_legal_move(game_board, player)) player = get_opponent(player);

        char legal_moves_board[8][8];
        generate_legal_moves_board(game_board, player, legal_moves_board);
        print_game(legal_moves_board);

        // Si on a que un coup possible, le programme le joue directement
        int legal_moves[64][2];
        int moves_origins[8][8][9][2];
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
        int legal_moves[64][2];
        int moves_origins[8][8][9][2];
        if(compute_legal_moves(game_board, player, legal_moves, moves_origins) == 1) {
            char legal_moves_board[8][8];
            generate_legal_moves_board(game_board, player, legal_moves_board);
            print_game(legal_moves_board);
            printf("Player %c, unique move possible is played : %c%c\n", player, legal_moves[0][0] + 'A', legal_moves[0][1] + '1');

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
            compute_best_move(5, game_board, player, &x, &y);
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
        int legal_moves[64][2];
        int moves_origins[8][8][9][2];
        if(compute_legal_moves(game_board, player, legal_moves, moves_origins) == 1) {
            char legal_moves_board[8][8];
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
        compute_best_move(4, game_board, player, &x, &y);
        // printf("%c%c\n", x + 'A', y + '1');
        // strcat(game_moves, (char[]){x + 'A', y + '1', '\0'});
        // printf("%s", game_moves);
           
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
    int move;
    init_game_board(game_board);
    mynetgame = allocateGameOthello();

    mynetgame->address = "192.168.132.18";
    mynetgame->userId = 2;
    mynetgame->port = 8080;
    registerGameOthello(mynetgame, "binome2");
    if(startGameOthello(mynetgame) < 0) {
        printf("Erreur de lancement");
    }
    printf("I am player %s\n",(mynetgame->myColor==BLACK)?"black":"white"); 
    player = mynetgame->myColor==BLACK ? 'O': 'X'; // black => 'O'
    printf("I am %c and server is %c\n", player, get_opponent(player));
	// debut de partie
	while (mynetgame->state == PLAYING && !feof(stdin)) {
	 	if (mynetgame->myColor != mynetgame->currentPlayer) { // attente du coup de l'adversaire 
			if ((move=waitMoveOthello(mynetgame)) == 0 ) {
				printf("Game status %d: \t",mynetgame->state); 
                print_game(game_board);
				if (mynetgame->state == PLAYING) { 
					printf("Received move from server %d (x=%d,y=%d)\n",mynetgame->move,mynetgame->move%8,mynetgame->move/8); 
                    int x = mynetgame->move%8;
                    int y = mynetgame->move/8;
                    proceed_move(game_board, player, x, y);
				}
			}
		}
	 	else {
            int x = 0, y = 0;
            print_game(game_board);
            printf("Player %c, IA is thinking...\n", player);
            compute_best_move(6, game_board, player, &x, &y);
            printf("Coup que je veux jouer : (%d %d)", x, y);
            proceed_move(game_board, player, x, y);
            print_game(game_board);
            mynetgame->move = y*8 + x;
			doMoveOthello(mynetgame);	// envoie du coup à l'adversaire
	   	}
		mynetgame->currentPlayer=!(mynetgame->currentPlayer);  	// on change de joueur 
        player = get_opponent(player);
	} 
	// fin de partie 
	printf("Final game status = %d\n",mynetgame->state); 
	freeGameOthello(mynetgame);
}


