#ifndef OWARE_H
#define OWARE_H

#include "player.h"

void displayGame(const player* currentPlayer, const player* opponent, int currentTurn);
void displayHoles(const player* currentPlayer);
int letsPlay(player* player1, player* player2, int* turnWithoutHarvest, int gameTurn);

#endif