#ifndef BOARD_H
#define BOARD_H

#include <QApplication>
#include "constant.h"
#include "mainwindow.h"
#include <cstdlib>




class Board
{

public:
    Board();
    ~Board();
    int boardHeight;
    int boardWidth;
    void addShipsToBoard();
    bool addShip(int shipLength);

};

#endif // BOARD_H
