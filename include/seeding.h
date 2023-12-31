#ifndef SEEDING_H
#define SEEDING_H

#include "player.h"

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightHole);
int seed(player* currentPlayer, player* opponent, bool* isTheRightHole, int realHoleIndex);
bool getOpponentStatus(player opponent);
bool checkPossiblePlay(player currentPlayer, player opponent, int* checkTab);

#endif