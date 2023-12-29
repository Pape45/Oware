/**
 * Implémentation de la logique de récolte. 
 * S'il y a eu récolte, on renverra TRUE à oware.c. Cela nous permettra de compter en temps réel le nombre de tours sans récolte.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "player.h"

bool harvestStage(player* currentPlayer, player* opponent, int IndexToHarvest) {
    if(opponent->hole[IndexToHarvest] == 2 || opponent->hole[IndexToHarvest] == 3) {
        currentPlayer->score += opponent->hole[IndexToHarvest];
        opponent->hole[IndexToHarvest] = 0;
        return true; 
    } else {
        return false;
    }
}