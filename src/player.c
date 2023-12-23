#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "tools.h"

void initializePlayers(player* player1, player* player2) {
    /**
     * TODO : 
     *  - Verification for fields 
    */
    // printf("Bienvenue au jeu du Awale!\n\n");
    // printf("Joueur 1, Veuillez rentrer votre nom : ");
    // lire(player1->name, 100);
    // printf("Veuillez rentrer votre âge : ");
    // player1->age = lireLong();
    // printf("\nJoueur 2, Veuillez rentrer votre nom : ");
    // lire(player2->name, 100);
    // printf("Veuillez rentrer votre âge : ");
    // player2->age = lireLong();

    strcpy(player1->name, "Player 1");
    strcpy(player2->name, "Player 2");

    for(int i = 0; i < 6; i++) {
        player1->hole[i] = 3;
        player2->hole[i] = 3;
    }

    player1->score = 0; 
    player2->score = 0;
}