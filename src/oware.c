#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "seeding.h"
#include "player.h"

int main(int argc, const char *argv[]) {
    player* player1 = malloc(sizeof(player)); 
    player* player2 = malloc(sizeof(player));

    if (player1 == NULL || player2 == NULL) {
        fprintf(stderr, "Memory allocation failed, please debug :)\n");
        return 0;
    }

    initializePlayers(player1, player2);
    seedingStage(player1, player2);

    free(player1);
    free(player2);

    return 1;
}
