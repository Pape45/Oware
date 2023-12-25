#ifndef PLAYER_H
#define PLAYER_H

typedef struct player{
    char name[100];
    int age;
    int hole[6];
    int score;
} player;


void initializePlayers(player* player1, player* player2);

#endif
