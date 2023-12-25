#ifndef SEEDING_H
#define SEEDING_H

#include "player.h"

int seedingStage(player* currentPlayer, player* opponent, bool* isTheRightCase);
int seeding(int option, int realHoleIndex, player *currentPlayer, player *opponent, bool* isTheRightCase);
#endif