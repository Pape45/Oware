/**
 * Implémentation de la logique de semaille. 
 * 
 * Principe : Tant qu'il reste des boules dans le trou que le joueur a décidé de jouer, on va semer. La question est de savou-ir si on sème chez nous ou l'adversaire. On va utiliser une combinaison binaire de variable identifiant le joueur courant et l'adversaire ( ex : i & checkI sont pour le joueur courant ). Ces deux variables nous permettent de savoir en temps réel si on a dépassé l'index du tableau ( ex : i > 5 ) ou bien savoir quelle partie on doit semer ( ex : checkI nous dit qu'on est encore de semer le joueur courant ).
 *  
 * Si on finit la semaille chez l'adversaire, alors isTheRightHole passe à true et on pourra ainsi passer à la phase de récolte s'il y a lieu.
 * 
 * On oublie pas de réinitialiser les variables i & j quand on repasse une n-ième fois sur telle partie d'un joueur et d'inverser les variables check pour valider la semaille chez le joueur. 
 * 
 * Ajout du prof : Si possible, le joueur courant "offre" des boules à l'adversaire si toutes ses cases sont vides
 * 
 * Pour la version du "PC INTELLIGENT", on va simuler le gain obtenu par chaque coup. Si le coup donne des points, on retourne alors le coup. Si on en a pas trouvé, on joue un coup au hasard dont les cases ne sont pas vides.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/player.h"
#include "seeding.h"
#include "tools.h"
#include "endGame.h"
#include "harvest.h"

#define MAX_HOLE_INDEX 5
#define MIN_HOLE_INDEX 0

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightHole, int gameChoice, bool* specialEndGame) {
    srand(time(NULL));
    int holeValue;
    int realHoleIndex;
    bool isValidHoleIndex = false;
    bool isEmptyHole = false;
    bool pass;
    int* checkTab = malloc(sizeof(int) * 6);

    if (gameChoice == 2 && !strcmp(currentPlayer->name, "PC")) {
        int computerMove = makeComputerMove(currentPlayer, opponent);
        printf("\nPC joue : %d\n", computerMove + 1);
        free(checkTab);
        return seed(currentPlayer, opponent, isTheRightHole, computerMove);
    }

    printf("%s, Quelle case voulait-vous jouer ? : ", currentPlayer->name);
    holeValue = lireInt();

    do {
        *specialEndGame = false;
        pass = true;
        realHoleIndex = holeValue - 1;
        isValidHoleIndex = !(1 <= holeValue && holeValue <= 6);
        isEmptyHole = 0;

        if (isValidHoleIndex) {
            printf("\nVeuillez rentrer un numéro de trou valide : ");
            holeValue = lireInt();
        } else if (currentPlayer->hole[realHoleIndex] == 0) {
            isEmptyHole = 1;
            printf("\nCe trou est vide. Veuillez en choisir un autre : ");
            holeValue = lireInt();
        } else if (!getOpponentStatus(*opponent) && !checkPossiblePlay(currentPlayer, opponent, checkTab, realHoleIndex, specialEndGame)) {
            pass = false;
            printf("\nVous devez jouer un coup qui permet à l'adversaire d'avoir au moins une boule chez lui : ");
            holeValue = lireInt();
        }
        
        if (*specialEndGame) {
            *isTheRightHole = false;
            return 0;
        }

        if (!isValidHoleIndex && !isEmptyHole && pass) {
            break;
        }
    } while (1);

    free(checkTab);
    return seed(currentPlayer, opponent, isTheRightHole, realHoleIndex);
}

int seed(player* currentPlayer, player* opponent, bool* isTheRightHole, int realHoleIndex) {
    int i;
    int j;
    int remainingBalls;
    bool checkI = 1;
    bool checkJ = 0;    

    remainingBalls = currentPlayer->hole[realHoleIndex];
    i = realHoleIndex + 1;
    j = MAX_HOLE_INDEX;

    if (i > 5) {
        checkI = false;
        checkJ = true;
    }

    while (remainingBalls) {
        if (i <= 5 && checkI) {
            if (i == realHoleIndex) {
                if (i == 5) {
                    checkJ = true;
                    checkI = false;
                    j = MAX_HOLE_INDEX;
                }
                i++;
                continue;
            }
            currentPlayer->hole[i]++;
            i++;
            remainingBalls--;
            if (i <= 6 && !remainingBalls) {
                *isTheRightHole = false;
            } else if (i > 5 && remainingBalls) {
                checkJ = true;
                checkI = false;
                j = MAX_HOLE_INDEX;
            }
        } else if (j >= 0 && checkJ) {
            opponent->hole[j]++;
            j--;
            remainingBalls--;          
            if (j >= -1 && !remainingBalls) {
                *isTheRightHole = true;
            } else if (j < 0 && remainingBalls) {
                checkI = true;
                checkJ = false;
                i = 0;
            }
        }
    }
    currentPlayer->hole[realHoleIndex] = 0;
    return ++j;
}

bool getOpponentStatus(player opponent) {
    for (int i = 0; i <= 5; i++) {
        if (opponent.hole[i] > 0) {
            return true;
        } 
    }

    return false;
}

bool checkPossiblePlay(const player* currentPlayer, const player* opponent, int* checkTab, int realHoleIndex, bool *specialEndGame) {
    player* currentPlayer_temp = malloc(sizeof(player)); 
    player* opponent_temp = malloc(sizeof(player));
    bool* isTheRightHole = malloc(sizeof(bool));
    int cpt = 0;

    if (currentPlayer_temp == NULL || opponent_temp == NULL || isTheRightHole == NULL) {
        fprintf(stderr, "Affectation de mémoire échouée !\n");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < 6; j++) {
        checkTab[j] = 0;
    }

    for (int i = 0; i < 6; i++) {
        *currentPlayer_temp = *currentPlayer;
        *opponent_temp = *opponent;
        if (currentPlayer->hole[i] == 0) 
            continue;
        seed(currentPlayer_temp, opponent_temp, isTheRightHole, i);
        if (!getOpponentStatus(*opponent_temp)) {
            cpt++;
        } else {
            checkTab[i] = 1;
        }
    }

    free(currentPlayer_temp);
    free(opponent_temp);
    free(isTheRightHole);

    if (cpt != 6) {

        for (int k = 0; k < 6; k++) {
            if (realHoleIndex == k && checkTab[k]) {
                return true;
            }
        }
        return false;
    } else {
        *specialEndGame = true;
        return true;
    }
}

int makeComputerMove(const player* PC, const player* opponent) {
    bool checkBestPlay = false;
    player* PC_temp = malloc(sizeof(player));
    player* opponent_temp = malloc(sizeof(player));
    bool* isTheRightHole = malloc(sizeof(bool));
    int rightHoleToHarvest = 0;
    int currentScore = 0;
    int moveChoice;

    for (int i = 0; i < 6; i++) {
        *PC_temp = *PC;
        *opponent_temp = *opponent;
        if (PC_temp->hole[i] == 0)
            continue;
        rightHoleToHarvest = seed(PC_temp, opponent_temp, isTheRightHole, i);
        if (*isTheRightHole && harvestStage(PC_temp, opponent_temp, rightHoleToHarvest))
        {
            checkBestPlay = true;
            if (PC_temp->score > currentScore) {
                moveChoice = i;
            }
        }
    }

    if (!checkBestPlay) {
        do {
            moveChoice = rand() % 6;
        } while (PC->hole[moveChoice] == 0);
    }

    free(PC_temp);
    free(opponent_temp);
    free(isTheRightHole);

    return moveChoice;
}