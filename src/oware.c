/**
 * Voici le fichier principal du jeu.
 * 
 * Il appelle les fonctions des fichiers seeding.c ( pour la semaille ) et harvest.c ( pour la récole ). 
 * Pour compiler et lancer le jeu : make && ./bin/game
*/

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
    int* turnWithoutHarvest = malloc(sizeof(int));
    bool* isTheRightIndex = malloc(sizeof(bool));
    int gameTurn = 0;

    if (player1 == NULL || player2 == NULL) {
        fprintf(stderr, "Memory allocation failed, please debug :)\n");
        return 0;
    }
    
    initializePlayers(player1, player2);
    
    do {
        gameTurn++;
        if (!(letsPlay(player1, player2, turnWithoutHarvest, isTheRightIndex, gameTurn) || letsPlay(player2, player1, turnWithoutHarvest, isTheRightIndex, gameTurn))) {
            /**
             * Pas de récolte pour ce tour
            */
        
            *turnWithoutHarvest = *turnWithoutHarvest + 1;
        } else {
            *turnWithoutHarvest = 0;
        }
    } while (!endGame(player1, player2, turnWithoutHarvest, gameTurn));

    free(player1);
    free(player2);
    free(turnWithoutHarvest);
    free(isTheRightIndex);

    return 1;
}

int letsPlay(player* player1, player* player2, int* turnWithoutHarvest, bool* isTheRightIndex,int gameTurn) {
    int rightHoleToHarvest = 0;
    *isTheRightIndex = false;
    
    displayGame(player1, player2, gameTurn);
    rightHoleToHarvest = seedingStage(player1, player2, isTheRightIndex);
    
    if (*isTheRightIndex) {
        return harvestStage(player1, player2, rightHoleToHarvest);
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
