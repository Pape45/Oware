#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "seeding.h"
#include "tools.h"

void seedingStage(player* currentPlayer, player* opponent) {
    int holeValue, realHoleIndex, holeFillingStop, holeFillingStart;
    int i = 0;
    bool checkUnderFilling = 0, checkHoleIndex = 0, checkEmptyHole = 0;

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

    checkUnderFilling = realHoleIndex + currentPlayer->hole[realHoleIndex] < 6 ? true : false;

    if (checkUnderFilling) {
        holeFillingStart = (realHoleIndex + 1);
        holeFillingStop = realHoleIndex + currentPlayer->hole[realHoleIndex];

        for (i = holeFillingStart; i <= holeFillingStop; i++) {
            currentPlayer->hole[i]++;
        }
    }

    currentPlayer->hole[realHoleIndex] = 0;

    for (int j = 0; j < 6; j++) {
        printf("%d", currentPlayer->hole[j]);        
    }
}

