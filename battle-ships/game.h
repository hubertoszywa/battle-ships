#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QApplication>
#include <QTableWidget>
#include <QDebug>
#include <board.h>
#include "ships.h"
#include "player.h"

class Game : public QObject
{
    Q_OBJECT

private:
    QTableWidget *myBoard;
    int boardWidth, boardHeight;
    int itemVal, itemX, itemY;
    QVector<Point>hitted;
    Point hittedCoordinates;


public:
    Game(QTableWidget *z, QTableWidgetItem *pItem);
    int gameMove(Player *player);
    void gameCheckFields();

    ~Game();


signals:


};

#endif // GAME_H
