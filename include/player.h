#ifndef PLAYER_H
#define PLAYER_H

typedef struct player{
    char name[100];
    int hole[6];
    int score;
} player;


int initializePlayers(player* player1, player* player2);
void saveScores(const player* player1, const player* player2);

#endif
