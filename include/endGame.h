#ifndef END_GAME_H
#define END_GAME_H

#include "player.h"

bool endGame(const player* player1, const player* player2, int turnWithoutHarvest, int gameTurn, bool* specialEndGame);
void displayEndGame(const player* player1, const player* player2, int gameTurn);
bool checkEmptyPlayer(const player* player1, const player* player2);

#endif