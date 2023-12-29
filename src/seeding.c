/**
 * Implémentation de la logique de semaille. 
 * 
 * Principe : Tant qu'il reste des boules dans le trou que le joueur a décidé de jouer, on va semer. La question est de savou-ir si on sème chez nous ou l'adversaire. On va utiliser une combinaison binaire de variable identifiant le joueur courant et l'adversaire ( ex : i & checkI sont pour le joueur courant ). Ces deux variables nous permettent de savoir en temps réel si on a dépassé l'index du tableau ( ex : i > 5 ) ou bien savoir quelle partie on doit semer ( ex : checkI nous dit qu'on est encore de semer le joueur courant ).
 *  
 * Si on finit la semaille chez l'adversaire, alors isTheRightCase passe à true et on pourra ainsi passer à la phase de récolte s'il y a lieu.
 * 
 * On oublie pas de réinitialiser les variables i & j quand on repasse une n-ième fois sur telle partie d'un joueur et d'inverser les variables check pour valider la semaille chez le joueur. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"
#include "seeding.h"
#include "tools.h"

#define MAX_HOLE_INDEX 5
#define MIN_HOLE_INDEX 0

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightCase) {
    int holeValue, realHoleIndex;
    int i, j, remainingBalls;
    bool isValidHoleIndex = false, isEmptyHole = false;
    bool checkI = 1, checkJ = 0;


    printf("%s, Quelle case voulait-vous jouer ? : ", currentPlayer->name);
    holeValue = lireInt();

    do {
        realHoleIndex = holeValue - 1;
        isValidHoleIndex = !(1 <= holeValue && holeValue <= 6);

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
                *isTheRightCase = false;
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
                *isTheRightCase = true;
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

// void getOpponentStatus(player opponent) {
//     for (int i = 0; i < 5; i++) {
//         if (opponent.hole[i] > 0) {
//             return false;
//         } 
//     }

//     return true;
// }

// void checkPossiblePlay() {

// }