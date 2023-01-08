#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<stdlib.h>


void init_socket(int *newsockfd)
{
    // Création d'un socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }

    // Configuration du socket
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9999);

    // Liaison du socket à l'adresse et au port spécifiés
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur lors de la liaison du socket");
        exit(1);
    }

    // Mise en écoute du socket
    if (listen(sockfd, 5) < 0) {
        perror("Erreur lors de la mise en écoute du socket");
        exit(1);
    }

    // Acceptation d'une connexion entrante
    *newsockfd = accept(sockfd, NULL, NULL);
    if (*newsockfd < 0) {
        perror("Erreur lors de l'acceptation de la connexion entrante");
        exit(1);
    }
}

void send_game_data(int *newsockfd, char opponent_color) {
    // Envoi des données au client
    char buffer[2];
    memset(buffer, 0, sizeof(buffer));
    buffer[0] = opponent_color;
    buffer[1] = '\n';
    int n = write(*newsockfd, buffer, 2);
    if (n < 0) {
        perror("Erreur lors de l'envoi des données");
        exit(1);
    }
}

void receive_move(int *newsockfd, int *move_x, int *move_y) {
    // Lecture des données envoyées par le client
    char buffer[3];
    memset(buffer, 0, sizeof(buffer));
    int n = read(*newsockfd, buffer, sizeof(buffer));
    if (n < 0) {
        perror("Erreur lors de la lecture des données");
        exit(1);
    }
    *move_x = buffer[0]-'0';
    *move_y = buffer[1]-'0';
    printf("Données reçues : %s\n", buffer);
}

void send_move(int *newsockfd, int move_x, int move_y) {
    // Envoi des données au client
    char buffer[4];
    memset(buffer, 0, sizeof(buffer));
    buffer[0] = move_x + '0';
    buffer[1] = ',';
    buffer[2] = move_y + '0';
    buffer[3] = '\n';
    int n = write(*newsockfd, buffer, strlen(buffer));
    if (n < 0) {
        perror("Erreur lors de l'envoi des données");
        exit(1);
    }
}