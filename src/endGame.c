/**
 * Implémentation de la logique de fin du jeu conformément au PDF fourni.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "endGame.h"
#include "player.h"
#include "oware.h"

bool endGame(player* player1, player* player2, int turnWithoutHarvest, int gameTurn) {
    player* winner;

    if (player1->score >= 19 || player2->score >= 19) {
        displayGame(player1, player2, gameTurn);
        if (player1->score >= 19) {
            printf("\nFélicitations %s ! Tu as gagné avec un score de %d :)\n", player1->name, player1->score);
        } else {
            printf("\nFélicitations %s ! Tu as gagné avec un score de %d :)\n", player2->name, player2->score);
        }

        return true;
    } else if (turnWithoutHarvest == 20) {
        displayGame(player1, player2, gameTurn);
        if (player1->score == player2->score) {
            printf("\nFin du jeu ! On a un match nul :)\n");
        } else {
            winner = player1->score > player2->score ? player1 : player2;
            printf("\nFélicitations %s ! Tu as gagné avec un score de %d :)\n", winner->name, winner->score);
        }
        
        return true;
    }  else {
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

        if (player1Empty || player2Empty) {
            displayGame(player1, player2, gameTurn);
            if (player1->score == player2->score) {
                printf("\nFin du jeu ! On a un match nul :)\n");
            } else {
                winner = player1->score > player2->score ? player1 : player2;
                printf("\nFélicitations %s ! Tu as gagné avec un score de %d :)\n", winner->name, winner->score);
            }
            return true;
        }
    }

    return false;
}
