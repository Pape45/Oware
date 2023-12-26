#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "endGame.h"
#include "player.h"
#include "oware.h"

bool endGame(player* player1, player* player2, int* turnWithoutHarvest, int gameTurn) {
    int i = 0, j = 0;
    player* winner;
    bool isRemainingBalls = false;

    if (player1->score >= 19 || player2->score >= 19) {
        displayGame(player1, player2, gameTurn);
        if (player1->score >= 19) {
            printf("\nCongrats %s ! You won with a score of %d :)\n", player1->name, player1->score);
        } else {
            printf("\nCongrats %s ! You won with a score of %d :)\n", player2->name, player2->score);
        }

        return true;
    } else if (*turnWithoutHarvest == 20) {
        displayGame(player1, player2, gameTurn);
        if (player1->score == player2->score) {
            printf("\nGame over ! We have a draw :)\n");
        } else {
            winner = player1->score > player2->score ? player1 : player2;
            printf("\nCongrats %s ! You won with a score of %d :)\n", winner->name, winner->score);
        }
        
        return true;
    }  else {
        for (i = 0; i < 6; i++) {
            if (player1->hole[i] > 0) {
                return false;
            }
        }

        for (j = 0; j < 6; j++) {
            if (player2->hole[i] > 0) {
                return false;
            }
        }

        displayGame(player1, player2, gameTurn);
        if (player1->score == player2->score) {
            printf("\nGame over ! We have a draw :)\n");
        } else {
            winner = player1->score > player2->score ? player1 : player2;
            printf("\nCongrats %s ! You won with a score of %d :)\n", winner->name, winner->score);
        }
        
        return true;
    }

    return false;
}
