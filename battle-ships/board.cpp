#include "board.h"

Board::Board()
{

}

void Board::addShipsToBoard()
{

    for(int i=0; i<boardWidth; ++i)
        for(int j=0; j<boardHeight; ++j)
            //wypełnie pola tablicy wartością domyślną = 0




    for(int i=0; i<numberOfShips; ++i)
    {
        while(!addShip(ships[i]));
    }
}


bool Board::addShip(int shipLength)
{
    bool direction = rand()%2; //0 = poziomo, 1 = pionowo
    int x = rand()%(direction ? boardWidth : (1+boardWidth-shipLength));
    int y = rand()%(direction ? (1+boardHeight-shipLength) : boardHeight);


    return false;
}


Board::~Board()
{

}
