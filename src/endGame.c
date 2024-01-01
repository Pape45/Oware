/**
 * Implémentation de la logique de fin du jeu conformément au PDF fourni.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "endGame.h"
#include "player.h"
#include "oware.h"

bool endGame(const player* player1, const player* player2, int turnWithoutHarvest, int gameTurn, bool* specialEndGame) {
    
    if (player1->score >= 19 || player2->score >= 19 || turnWithoutHarvest == 20 || (checkEmptyPlayer(player1, player2) && *specialEndGame)) {
        displayEndGame(player1, player2, gameTurn);
        return true;
    }

    return false;
}

bool checkEmptyPlayer(const player* player1, const player* player2) {
    int player1Empty = 1;
    int player2Empty = 1;

    for (int i = 0; i < 6; i++) {
        if (player1->hole[i] > 0) {
            player1Empty = 0;
        }
    }

    for (int j = 0; j < 6; j++) {
        if (player2->hole[j] > 0) {
            player2Empty = 0;
        }
    }

    return player1Empty || player2Empty;
}

void displayEndGame(const player* player1, const player* player2, int gameTurn) {
        player winner;
        displayGame(player1, player2, gameTurn);
        if (player1->score == player2->score) {
            printf("\nFin du jeu ! On a un match nul :)\n");
        } else {
            winner = player1->score > player2->score ? *player1 : *player2;
            printf("\nFélicitations %s ! Tu as gagné avec un score de %d :)\n", winner.name, winner.score);
        }
}