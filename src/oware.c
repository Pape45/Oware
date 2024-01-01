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
#include <time.h>
#include "seeding.h"
#include "oware.h"
#include "player.h"
#include "harvest.h"
#include "endGame.h"

int main(int argc, const char *argv[]) {
    srand(time(NULL));
    player* player1 = malloc(sizeof(player)); 
    player* player2 = malloc(sizeof(player));
    int* turnWithoutHarvest = malloc(sizeof(int));
    bool* isTheRightHole = malloc(sizeof(bool));
    bool* specialEndGame = malloc(sizeof(bool));

    *turnWithoutHarvest = 0;
    int gameTurn = 0;
    int gameChoice = 1;
    int firstPlay = 0;

    if (player1 == NULL || player2 == NULL || turnWithoutHarvest == NULL || isTheRightHole == NULL || specialEndGame == NULL) {
        free(player1);
        free(player2);
        free(turnWithoutHarvest);
        free(isTheRightHole);
        free(specialEndGame);

        fprintf(stderr, "Erreur d'affectation mémoire !\n");
        return 0;
    }
    
    gameChoice = initializePlayers(player1, player2);
    
    firstPlay = rand() % 2;

    if (firstPlay) {
        player temp = *player1;
        *player1 = *player2;
        *player2 = temp;
    }

    do {
        gameTurn++;
        *turnWithoutHarvest = letsPlay_Aux(player1, player2, isTheRightHole, gameTurn, turnWithoutHarvest, gameChoice, specialEndGame);
        saveScores(player1, player2);
    } while (!endGame(player1, player2, *turnWithoutHarvest, gameTurn, specialEndGame));

    free(player1);
    free(player2);
    free(turnWithoutHarvest);
    free(isTheRightHole);
    free(specialEndGame);

    return 1;
}

int letsPlay(player* player1, player* player2, bool* isTheRightHole, int gameTurn, int gameChoice, bool* specialEndGame) {
    int rightHoleToHarvest = 0;
    *isTheRightHole = false;
    
    displayGame(player1, player2, gameTurn);
    rightHoleToHarvest = seedingStage(player1, player2, isTheRightHole, gameChoice, specialEndGame);

    if (*isTheRightHole) {
        return harvestStage(player1, player2, rightHoleToHarvest);
    }

    return 0;
}

int letsPlay_Aux(player* current, player* opponent, bool* isTheRightHole, int gameTurn, const int* turnWithoutHarvest, int gameChoice, bool* specialEndGame) {
    *specialEndGame = false;
    int isThereAHarvest_1 = 0;
    int isThereAHarvest_2 = 0;

    isThereAHarvest_1 = letsPlay(current, opponent, isTheRightHole, gameTurn, gameChoice, specialEndGame);
    
    if (*specialEndGame)
        return 0;

    isThereAHarvest_2 = letsPlay(opponent, current, isTheRightHole, gameTurn, gameChoice, specialEndGame);

    return isThereAHarvest_1 || isThereAHarvest_2 ? 0 : (*turnWithoutHarvest + 1);
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
