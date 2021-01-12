/*!
*@file game.cpp
*@brief Funkcje z tej biblioteki zawierają mechanizmy do obsługi rozgrywki - sprawdzanie sytuacji, w których statek został trafiony, nietrafiony lub zatopiony.
*/

#include "game.h"







//------------ PUBLIC ------------


Game::Game(QTableWidget *z, QTableWidgetItem *pItem){
    myBoard = z;
    boardHeight = myBoard->rowCount();
    boardWidth = myBoard->columnCount();
    itemX = pItem->row();
    itemY = pItem->column();

    QTableWidgetItem *a = myBoard->item(itemX, itemY);
    itemVal = a->text().toInt();
}


void Game::gameCheckFields()
{
    QTableWidgetItem *b;
    int whatIn;

    //sprawdzanie zatopionych masztów na prawo od trafionego masztu
    for(int i=1; i < itemVal; ++i)
    {
        if(itemY+i <= boardHeight-1)
        {
            //pobranie zawartości komórki po prawej stronie
            b = myBoard->item(itemX, itemY+i);
            whatIn = b->text().toInt();
            if(whatIn == 0)
                break;
            if(whatIn == itemVal*10)
            {
                hittedCoordinates.row = itemX;
                hittedCoordinates.col = itemY+i;
                hitted.push_back(hittedCoordinates);
            }
        }
    }


    //sprawdzanie zatopionych masztów na lewo od trafionego masztu
    for(int i=1; i < itemVal; ++i)
    {
        if(itemY-i >= 0)
        {
            //pobranie zawartości komórki po prawej stronie
            b = myBoard->item(itemX, itemY-i);
            whatIn = b->text().toInt();
            if(whatIn == 0)
                break;
            if(whatIn == itemVal*10)
            {
                hittedCoordinates.row = itemX;
                hittedCoordinates.col = itemY-i;
                hitted.push_back(hittedCoordinates);
            }
        }
    }


    //sprawdzanie zatopionych masztów w dół od trafionego masztu
    for(int i=1; i < itemVal; ++i)
    {
        if(itemX+i <= boardWidth-1)
        {
            //pobranie zawartości komórki po prawej stronie
            b = myBoard->item(itemX+i,itemY);
            whatIn = b->text().toInt();
            if(whatIn == 0)
                break;
            if(whatIn == itemVal*10)
            {
                hittedCoordinates.row = itemX+i;
                hittedCoordinates.col = itemY;
                hitted.push_back(hittedCoordinates);
            }
        }
    }


    //sprawdzanie zatopionych masztów w górę od trafionego masztu
    for(int i=1; i < itemVal; ++i)
    {
        if(itemX-i >= 0)
        {
            //pobranie zawartości komórki po prawej stronie
            b = myBoard->item(itemX-i, itemY);
            whatIn = b->text().toInt();
            if(whatIn == 0)
                break;
            if(whatIn == itemVal*10)
            {
                hittedCoordinates.row = itemX-i;
                hittedCoordinates.col = itemY;
                hitted.push_back(hittedCoordinates);
            }
        }
    }
}





int Game::gameMove(Player *player, QColor c2, QColor c3, QColor c4)
{
    if(itemVal == 1)
    {
        myBoard->setItem(itemX, itemY, new QTableWidgetItem(QString::number(100)));
        myBoard->item(itemX,itemY)->setBackground(c3);
        myBoard->item(itemX,itemY)->setFlags(Qt::ItemIsEditable);
        player->playerShot(10);
        return 10;
    }

    else if (itemVal == -1 || itemVal == 0)
    {
        myBoard->setItem(itemX, itemY, new QTableWidgetItem(QString::number(1000)));
        myBoard->item(itemX,itemY)->setBackground(c4);
        player->playerShot(0);
        return 0;
    }

    else if (itemVal < 10 && itemVal > 1)
    {
        Point temp;

        myBoard->setItem(itemX,itemY, new QTableWidgetItem(QString::number(itemVal*10)));
        myBoard->item(itemX,itemY)->setBackground(c2);

        hittedCoordinates.row = itemX;
        hittedCoordinates.col = itemY;
        hitted.push_back(hittedCoordinates);

        gameCheckFields();

        //jeśli trafionych pól jest tyle, ilu masztowy jest statek...
        if(hitted.size() == itemVal)
        {
            //...wówczas zaznacz jako trafiony-zatopiony
            for(int i=0; i < hitted.size(); ++i)
            {
                temp = hitted[i];
                myBoard->setItem(temp.row, temp.col, new QTableWidgetItem(QString::number(itemVal*100)));
                myBoard->item(temp.row,temp.col)->setBackground(c3);
                myBoard->item(temp.row,temp.col)->setFlags(Qt::ItemIsEditable);
            }
            player->playerShot(10);
            return 10;
        }
        player->playerShot(1);
        return 1;
    }
    else
    {
       return -1;
    }
}




Game::~Game()
{
    hitted.clear();
}
