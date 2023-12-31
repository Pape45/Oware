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
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "seeding.h"
#include "tools.h"
#include "endGame.h"

#define MAX_HOLE_INDEX 5
#define MIN_HOLE_INDEX 0

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightHole) {
    int holeValue;
    int realHoleIndex;
    bool isValidHoleIndex = false;
    bool isEmptyHole = false;
    bool pass;
    int* checkTab = malloc(sizeof(int) * 6);


    printf("%s, Quelle case voulait-vous jouer ? : ", currentPlayer->name);
    holeValue = lireInt();

    do {
        pass = true;
        realHoleIndex = holeValue - 1;
        isValidHoleIndex = !(1 <= holeValue && holeValue <= 6);
        isEmptyHole = (currentPlayer->hole[realHoleIndex] == 0);

        if (isValidHoleIndex) {
            printf("\nVeuillez rentrer un numéro de trou valide : ");
            holeValue = lireInt();
        } else if (isEmptyHole) {
            printf("\nCe trou est vide. Veuillez en choisir un autre : ");
            holeValue = lireInt();
        } else if (!getOpponentStatus(*opponent)) {
            if (checkPossiblePlay(*currentPlayer, *opponent, checkTab)) {
                for (int k = 0; k < 6; k++) {
                    pass = false;
                    if (realHoleIndex == k && checkTab[k]) {
                        pass = true;
                        break;
                    }
                }
            } else {
                endGame(currentPlayer, opponent, 20, 0);
                printf("\nExplication : Tous les cases du joueur adversaire sont à 0 et %s n'a pas la possibilité de jouer un coup lui permettant d'obtenir une boule !\n", currentPlayer->name);
                exit(EXIT_SUCCESS);
            }

            if (!pass) {
                printf("\nVous devez jouer un coup qui permet à l'adversaire d'avoir au moins une boule chez lui : ");
                holeValue = lireInt();
            }
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
                i++;
                continue;
            }
            currentPlayer->hole[i]++;
            i++;
            remainingBalls--;
            if (i <= 5 && !remainingBalls) {
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
            if (j >= 0 && !remainingBalls) {
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

bool checkPossiblePlay(player currentPlayer, player opponent, int* checkTab) {
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
        *currentPlayer_temp = currentPlayer;
        *opponent_temp = opponent;
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

    return (cpt != 6);
}