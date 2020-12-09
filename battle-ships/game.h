#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QApplication>
#include <QTableWidget>
#include <QDebug>
#include <board.h>
#include "ships.h"

class Game : public QObject
{
    Q_OBJECT

private:
    QTableWidget *myBoard;
    int boardWidth;
    int boardHeight;

public:
    Game(QTableWidget *, int, int);
    //explicit Game(QObject *parent = nullptr);
    void showMyItem(QTableWidgetItem *pItem);

    ~Game();



signals:


};

#endif // GAME_H
