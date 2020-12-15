#include "board.h"


Board::Board(int x, int y, QTableWidget *z)
{   
    boardWidth = x;
    boardHeight = y;
    myTable = z;
}



void Board::createBoard()
{
    myTable->setRowCount(boardWidth);
    myTable->setColumnCount(boardHeight);
    myTable->setFocusPolicy(Qt::NoFocus);
    myTable->setSelectionMode(QAbstractItemView::NoSelection);
    myTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *headerView = myTable->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    headerView = myTable->verticalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);


    makeWater();
}

void Board::makeWater()
{
    for(int i=0; i < boardWidth; i++)
        for(int j=0; j < boardHeight; j++)
            myTable->setItem(i,j,new QTableWidgetItem(QString::number(-1)));
}

void Board::addShipsToBoard()
{
    for(int i=0; i < numberOfShips; ++i)
    {
        while(!addShip(ships[i]));

    }
}


bool Board::addShip(int shipLength)
{
    //losowanie kierunku, w którą ma być układany statek
    bool direction = rand()%2; //0 = poziomo, 1 = pionowo

    //losowanie współrzędnych pola, od którego ma zacząć się dodawanie statku
    //z jednoczesnym ograniczeniem planszy (tak, żeby statek nie wyszedł "po za"
    int x = rand()%(direction ? boardWidth : (1+boardWidth-shipLength));
    int y = rand()%(direction ? (1+boardHeight-shipLength) : boardHeight);

    //sprawdzanie czy pola które ma zająć statek są dozwolone (czyli czy nie są 1 lub 2)
    for(int i = 0; i<shipLength; ++i)
    {
        int val;
        QTableWidgetItem *a = myTable->item(x+(direction ? 0 : i), y+(direction ? i : 0));
        val = a->text().toInt();
        if(val >= 0)
            return false;
    }

    //dodanie statku do planszy i oznaczenie pól wokół jako nieaktywne
    int ship;
    QTableWidgetItem *b;

    for(int i = 0; i<shipLength; i++)
    {
        myTable->setItem((direction ? x : x+i), (direction ? y+i : y), new QTableWidgetItem(QString::number(shipLength)));
        myTable->item((direction ? x : x+i), (direction ? y+i : y))->setBackground(Qt::red);

        for(int k = (direction ? x-1 : x+i-1); k <= (direction ? x+1 : x+i+1); k++)
        {
            if(k < 0) k++;
            if(k > boardWidth-1) break;
            for(int l = (direction ? y+i-1 : y-1); l <= (direction ? y+i+1 : y+1); l++)
            {
                if(l < 0) l++;
                if(l > boardHeight-1) break;

                b = myTable->item(k, l);
                ship = b->text().toInt();
                if(ship != shipLength && ship != 0)
                    myTable->setItem(k, l, new QTableWidgetItem(QString::number(0)));
            }
        }
    }
    return true;
}


Board::~Board()
{

}
