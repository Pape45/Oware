#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "seeding.h"
#include "tools.h"

void seedingStage(player* currentPlayer, player* opponent) {
    int holeValue, realHoleIndex, holeFillingStop, holeFillingStart, fillingOption, checkOverFilling;
    int i = 0;
    bool checkHoleIndex = 0, checkEmptyHole = 0;

    printf("%s, Quelle case voulait-vous jouer ? : ", currentPlayer->name);
    holeValue = lireInt();

    do {
        realHoleIndex = holeValue - 1;
        checkHoleIndex = holeValue < 1 || holeValue > 6 ? true : false;

        if (checkHoleIndex) {
            printf("\nVeuillez rentrer un numéro de trou valide : ");
            holeValue = lireInt();
        } else {
            checkEmptyHole = currentPlayer->hole[realHoleIndex] == 0 ? true : false;

            if (checkEmptyHole) {
                printf("\nCe trou est vide. Veuillez en choisir un autre : ");
                holeValue = lireInt();
            }
        }
    } while (checkEmptyHole || checkHoleIndex);

    checkOverFilling = realHoleIndex + currentPlayer->hole[realHoleIndex];

    if (checkOverFilling < 6) {
        fillingOption = 1;
    } else if (checkOverFilling >= 6 && checkOverFilling < 12) {
        fillingOption = 2;
    }

    // fillingOption = realHoleIndex + currentPlayer->hole[realHoleIndex] < 6 ? 1 : 0;

    seeding(fillingOption, realHoleIndex, currentPlayer, opponent);


    printf("\nCurrent player : ");
    for (int j = 0; j < 6; j++) {
        printf("%d", currentPlayer->hole[j]);        
    }

    printf("\nOpponent : ");
    for (int j = 0; j < 6; j++) {
        printf("%d", opponent->hole[j]);        
    }
}

void seeding(int option, int realHoleIndex, player *currentPlayer, player *opponent) {
    int holeFillingStart, holeFillingStop, remainingBalls, i = 0;

    remainingBalls = currentPlayer->hole[realHoleIndex];

    if (option == 1) {
        holeFillingStart = realHoleIndex + 1;
        holeFillingStop = realHoleIndex + currentPlayer->hole[realHoleIndex];

        for (i = holeFillingStart; i <= holeFillingStop; i++) {
            currentPlayer->hole[i]++;
        }   
    } else if (option == 2) {
        holeFillingStart = realHoleIndex + 1;
        holeFillingStop = 5;

        for (i = holeFillingStart; i <= holeFillingStop; i++) {
            currentPlayer->hole[i]++;
            remainingBalls--;
        }

        holeFillingStart = 5;
        holeFillingStop = 5 - remainingBalls;

        for (i = holeFillingStart; i > holeFillingStop; i--) {
            opponent->hole[i]++;
        }
    } else {
        
    }

    currentPlayer->hole[realHoleIndex] = 0;
}