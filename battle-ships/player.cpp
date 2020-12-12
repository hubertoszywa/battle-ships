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
