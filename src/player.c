/**
 * Mise en place des principales informations du joueur. Sa structure se trouve dans player.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "tools.h"

int initializePlayers(player* player1, player* player2) {
    int gameChoice = 1;
    printf("\n\nBienvenue au jeu du Awale!\n\n");
    printf("Quel mode voulez vous tester ? : \n\n1 - Joueur vs Joueur\n2 - Joueur vs PC");
    printf("\n\nChoix : ");
    gameChoice = lireInt();

    while (gameChoice < 1 || gameChoice > 2) {
        printf("\nVeuiller donner un mode valide : ");
        gameChoice = lireInt();
    }
    if (gameChoice == 1) {
        printf("Joueur 1, veuillez rentrer votre nom : ");
        lire(player1->name, 100);
        printf("Joueur 2, veuillez rentrer votre nom : ");
        lire(player2->name, 100);
    } else {
        printf("Joueur 1, veuillez rentrer votre nom : ");
        lire(player1->name, 100);
        strcpy(player2->name, "PC");
    }

    for(int i = 0; i < 6; i++) {
        player1->hole[i] = 3;
        player2->hole[i] = 3;
    }

    return gameChoice;
}

void saveScores(const player* player1, const player* player2) {
    FILE *file = fopen("scores.txt", "w+");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Joueur Score \n");
    fprintf(file, "%s \t %d\n", player1->name, player1->score);
    fprintf(file, "%s \t %d\n", player2->name, player2->score);

    fclose(file);
}
