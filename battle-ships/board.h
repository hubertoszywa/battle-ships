#ifndef BOARD_H
#define BOARD_H

#include <QApplication>
#include <QObject>
#include "constant.h"
#include "mainwindow.h"
#include "game.h"
#include <QDebug>
#include <QColor>
#include <QTableWidget>


class Board: public QTableWidget
{
private:
    int boardWidth;
    int boardHeight;
    QTableWidget *myTable;
    bool userTable;
    QColor colorNormal;

    void makeWater();
    bool addShip(int shipLength);

public:
    Board(int, int, QTableWidget *, bool);

    void createBoard();
    void addShipsToBoard(QColor);

    ~Board();
};

#endif // BOARD_H
