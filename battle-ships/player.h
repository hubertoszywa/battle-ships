#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QLCDNumber>

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

};




#endif // PLAYER_H
