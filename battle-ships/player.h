#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QString>
#include "constant.h"
#include <QFile>
#include <QTextStream>

class Player
{
public:
    int numberOfShots;
    int hitShots;
    int missShots;
    int sunkShips;
    int score;
    QString level;

    Player();
    void playerStart();
    void playerShot(int hit);
    void playerUpadteStats(QLCDNumber *screen);
    bool playerWin();
    void countScore(Player bott, int time, int lvl);

};




#endif // PLAYER_H
