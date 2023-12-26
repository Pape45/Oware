#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "seeding.h"
#include "tools.h"

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightCase) {
    int holeValue, realHoleIndex, holeFillingStop, holeFillingStart, checkOverFilling;
    int i = 0;
    bool isValidHoleIndex = false, isEmptyHole = false;
    int rightIndex;

    printf("%s, Quelle case voulait-vous jouer ? : ", currentPlayer->name);
    holeValue = lireInt();

    do {
        realHoleIndex = holeValue - 1;
        isValidHoleIndex = holeValue < 1 || holeValue > 6 ? true : false;

        if (isValidHoleIndex) {
            printf("\nVeuillez rentrer un numéro de trou valide : ");
            holeValue = lireInt();
        } else {
            isEmptyHole = currentPlayer->hole[realHoleIndex] == 0 ? true : false;

            if (isEmptyHole) {
                printf("\nCe trou est vide. Veuillez en choisir un autre : ");
                holeValue = lireInt();
            }
        }
    } while (isEmptyHole || isValidHoleIndex);

    checkOverFilling = realHoleIndex + currentPlayer->hole[realHoleIndex];

    if (checkOverFilling < 6) {
        rightIndex = seeding(1, realHoleIndex, currentPlayer, opponent, isTheRightCase);
    } else if (checkOverFilling >= 6 && checkOverFilling < 12) {
        rightIndex = seeding(2, realHoleIndex, currentPlayer, opponent, isTheRightCase);
    } else if (checkOverFilling >= 12 && checkOverFilling < 18) {
        rightIndex = seeding(3, realHoleIndex, currentPlayer, opponent, isTheRightCase);
    } else {
        rightIndex = seeding(4, realHoleIndex, currentPlayer, opponent, isTheRightCase);
    }

    return rightIndex;
}

int seeding(int option, int realHoleIndex, player *currentPlayer, player *opponent, bool* isTheRightCase) {
    int holeFillingStart, holeFillingStop, indexToEscape;
    int remainingBalls = currentPlayer->hole[realHoleIndex];
    int i;

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

        *isTheRightCase = true;

    } else if (option == 3) {
        holeFillingStart = realHoleIndex + 1;
        holeFillingStop = 5;
        indexToEscape = realHoleIndex;

        for (i = holeFillingStart; i <= holeFillingStop; i++) {
            currentPlayer->hole[i]++;
            remainingBalls--;
        }

        for (i = 5; i >= 0; i--) {
            opponent->hole[i]++;
            remainingBalls--;
        }

        printf("Remaining : %d", remainingBalls);

        for (i = 0; i < remainingBalls; i++) {
            currentPlayer->hole[i]++;
        }
    } else {
        holeFillingStart = realHoleIndex + 1;
        holeFillingStop = 5;
        indexToEscape = realHoleIndex;

        for (i = holeFillingStart; i <= holeFillingStop; i++) {
            currentPlayer->hole[i]++;
            remainingBalls--;
        }

        for (i = 5; i >= 0; i--) {
            opponent->hole[i]++;
            remainingBalls--;
        }

        printf("\nremaining : %d\n", remainingBalls);
        for (i = 0; i < 5; i++) {
            if (i == realHoleIndex) {
                continue;
            } else {
                currentPlayer->hole[i]++;
                remainingBalls--;
            }
        }
        
        holeFillingStop = 5 - remainingBalls;

        for (i = 5; i > holeFillingStop; i--) {
            opponent->hole[i]++;
        }

        *isTheRightCase = true;
    }

    currentPlayer->hole[realHoleIndex] = 0;
    return ++holeFillingStop;
}