#ifndef BOARD_H
#define BOARD_H

#include <QApplication>
#include <QObject>
#include "constant.h"
#include "mainwindow.h"
#include "game.h"
#include <QDebug>


class Board : public QTableWidget
{
private:
    int boardWidth;
    int boardHeight;
    QTableWidget *myTable;
    int eluwina;

    void makeWater();
    bool addShip(int shipLength);

public:
    Board(int, int, QTableWidget *);

    void createBoard();
    void addShipsToBoard();

    ~Board();
};

#endif // BOARD_H
