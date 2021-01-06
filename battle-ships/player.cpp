#include "player.h"

Player::Player(){}

void Player::playerStart()
{
    numberOfShots = 0;
    hitShots = 0;
    missShots = 0;
    sunkShips = 0;
}


void Player::playerShot(int hit)
{
    numberOfShots++;

    if(hit == 10)
    {
       hitShots++;
       sunkShips++;
    }

    if(hit == 1)
        hitShots++;


    if(hit == 0)
        missShots++;
}


bool Player::playerWin()
{
    if(sunkShips == numberOfShips)
        return true;
    else
        return false;
}


void Player::countScore(Player bott, int time, int lvl)
{
    score = hitShots*100 - missShots*10 - bott.hitShots*10 - time;
    if (score < 0) score = 0;

    if(lvl == -2) level = "Łatwy";
    if(lvl == -3) level = "Średni";
    if(lvl == -4) level = "Trudny";

    QString filename = "scores.txt";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
            QTextStream stream(&file);
            stream << level << Qt::endl << score << Qt::endl;
        }
    file.close();
}





