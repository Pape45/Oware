/**
 * Mise en place des principales informations du joueur. Sa structure se trouve dans player.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "tools.h"

void initializePlayers(player* player1, player* player2) {
    printf("\n\nBienvenue au jeu du Awale!\n\n");
    printf("Veuillez rentrer votre nom : ");
    lire(player1->name, 100);

    for(int i = 0; i < 6; i++) {
        player1->hole[i] = 3;
        player2->hole[i] = 3;
    }

    strcpy(player1->name, "pape");
    strcpy(player2->name, "PC");
}