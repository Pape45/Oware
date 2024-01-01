#ifndef SEEDING_H
#define SEEDING_H

#include "player.h"

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightHole, int gameChoice, bool* specialEndGame);
int seed(player* currentPlayer, player* opponent, bool* isTheRightHole, int realHoleIndex);
bool getOpponentStatus(player opponent);
bool checkPossiblePlay(const player* currentPlayer, const player* opponent, int* checkTab, int realHoleIndex, bool *specialEndGame);

#endif