#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QLCDNumber>
#include "constant.h"

class Player
{
public:
    int numberOfShots;
    int hitShots;
    int missShots;
    int sunkShips;

    Player();
    void playerStart();
    void playerShot(int hit);
    void playerUpadteStats(QLCDNumber *screen);
    bool playerWin();

};




#endif // PLAYER_H
