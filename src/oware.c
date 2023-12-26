#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "seeding.h"
#include "oware.h"
#include "player.h"
#include "harvest.h"
#include "endGame.h"

int main(int argc, const char *argv[]) {
    player* player1 = malloc(sizeof(player)); 
    player* player2 = malloc(sizeof(player));
    int rightHoleToHarvest = 0;
    int* turnWithoutHarvest = malloc(sizeof(int));
    bool* isTheRightIndex = malloc(sizeof(bool));
    bool isThereAHarvest = false;
    int gameTurn = 1;

    if (player1 == NULL || player2 == NULL) {
        fprintf(stderr, "Memory allocation failed, please debug :)\n");
        return 0;
    }
    
    initializePlayers(player1, player2);

    player1->score = 18;

    do {
        if (letsPlay(player1, player2, turnWithoutHarvest, gameTurn) || letsPlay(player2, player1, turnWithoutHarvest, gameTurn)) {
            break;
        }
        gameTurn++;
    } while (1);

    free(player1);
    free(player2);

    return 1;
}

int letsPlay(player* player1, player* player2, int* turnWithoutHarvest, int gameTurn) {
    bool isThereAHarvest = false;
    bool* isTheRightIndex = malloc(sizeof(bool));
    int rightHoleToHarvest = 0;

    *isTheRightIndex = false;
    displayGame(player1, player2, gameTurn);
    rightHoleToHarvest = seedingStage(player1, player2, isTheRightIndex);
    
    if (*isTheRightIndex) {
        isThereAHarvest = harvestStage(player1, player2, rightHoleToHarvest);
    }

    if (isThereAHarvest) {
        *turnWithoutHarvest = 0;
    } else {
        *turnWithoutHarvest = *turnWithoutHarvest + 1;
    }
    
    if (endGame(player1, player2, turnWithoutHarvest, gameTurn)) {
        return 1;
    }   

    return 0;
}

void displayGame(const player* currentPlayer, const player* opponent, int currentTurn) {
    printf("\n-------------------------------------------------------------------------------------------------\n");

    printf("(%s)\n\n", opponent->name);
    displayHoles(opponent);
    printf("\nScore: %d\n", opponent->score);

    printf("\n-------------------------------------------------------------------------------------------------\n");

    printf("(%s)\n\n", currentPlayer->name);
    displayHoles(currentPlayer);
    printf("\nScore: %d\n", currentPlayer->score);
    printf("\nTour : %d\n", currentTurn);

    printf("-------------------------------------------------------------------------------------------------\n");
}
void displayHoles(const player* currentPlayer) {
    printf("| ");
    for (int i = 0; i < 6; i++) {
        printf("\t%d\t| ", currentPlayer->hole[i]);
    }
    printf("\n");
}
