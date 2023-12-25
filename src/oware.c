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
    int rightHoleToHarvest = 0, turnNumber = 0;
    bool* isTheRightIndex = malloc(sizeof(bool));
    bool falseValue = false;

    if (player1 == NULL || player2 == NULL) {
        fprintf(stderr, "Memory allocation failed, please debug :)\n");
        return 0;
    }
    
    initializePlayers(player1, player2);
    displayGame(player1, player2);
    rightHoleToHarvest = seedingStage(player1, player2, isTheRightIndex);
    harvestStage(player1, player2, rightHoleToHarvest);
    isTheRightIndex = &falseValue;
    
    printf("\nCurrent player : ");
    for (int j = 0; j < 6; j++) {
        printf("%d", player1->hole[j]);        
    }

    printf("\nOpponent : ");
    for (int j = 0; j < 6; j++) {
        printf("%d", player2->hole[j]);        
    }

    free(player1);
    free(player2);

    return 1;
}

void displayGame(const player* player1, const player* player2) {
    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("Player 1 (%s)\n\n", player1->name);
    displayHoles(player1);
    printf("\nScore: %d\n", player1->score);

    printf("\n-------------------------------------------------------------------------------------------------\n");
    printf("Player 2 (%s)\n\n", player2->name);
    displayHoles(player2);
    printf("\nScore: %d\n", player2->score);
    printf("-------------------------------------------------------------------------------------------------\n");
}

void displayHoles(const player* currentPlayer) {
    printf("| ");
    for (int i = 0; i < 6; i++) {
        printf("\t%d\t| ", currentPlayer->hole[i]);
    }
    printf("\n");
}
