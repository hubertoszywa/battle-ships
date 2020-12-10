#include "game.h"

Game::Game(QTableWidget *z, int width, int height){
    myBoard = z;
    boardHeight = height;
    boardWidth = width;
}


void Game::showMyItem(QTableWidgetItem *pItem)
{

    int x = pItem->row();
    int y = pItem->column();

    int val, whatIn;
    QTableWidgetItem *a = myBoard->item(x, y);
    QTableWidgetItem *b;
    val = a->text().toInt();

    if(val == 1)
    {
        myBoard->setItem(x, y, new QTableWidgetItem(QString::number(100)));
        myBoard->item(x,y)->setBackground(Qt::green);
    }

    else if (val == -1 || val == 0)
    {
        myBoard->item(x,y)->setBackground(Qt::gray);
    }

    else if (val < 10 && val > 1)
    {
        QVector<Point>hitted;
        Point temp;

        myBoard->setItem(x, y, new QTableWidgetItem(QString::number(val*10)));
        myBoard->item(x,y)->setBackground(Qt::yellow);

        temp.row = x;
        temp.col = y;
        hitted.push_back(temp);


        //sprawdzanie na prawo od trafionego masztu
        for(int i=1; i < val; ++i)
        {
            if(y+i <= boardHeight-1)
            {
                //pobranie zawartości komórki po prawej stronie
                b = myBoard->item(x, y+i);
                whatIn = b->text().toInt();
                if(whatIn == 0)
                    break;
                if(whatIn == val*10)
                {
                    temp.row = x;
                    temp.col = y+i;
                    hitted.push_back(temp);
                }
            }
        }


        //sprawdzanie na lewo od trafionego masztu
        for(int i=1; i < val; ++i)
        {
            if(y-i >= 0)
            {
                //pobranie zawartości komórki po prawej stronie
                b = myBoard->item(x, y-i);
                whatIn = b->text().toInt();
                if(whatIn == 0)
                    break;
                if(whatIn == val*10)
                {
                    temp.row = x;
                    temp.col = y-i;
                    hitted.push_back(temp);
                }
            }
        }


        //sprawdzanie w dół od trafionego masztu
        for(int i=1; i < val; ++i)
        {
            if(x+i <= boardWidth-1)
            {
                //pobranie zawartości komórki po prawej stronie
                b = myBoard->item(x+i,y);
                whatIn = b->text().toInt();
                if(whatIn == 0)
                    break;
                if(whatIn == val*10)
                {
                    temp.row = x+i;
                    temp.col = y;
                    hitted.push_back(temp);
                }
            }
        }


        //sprawdzanie w górę od trafionego masztu
        for(int i=1; i < val; ++i)
        {
            if(x-i >= 0)
            {
                //pobranie zawartości komórki po prawej stronie
                b = myBoard->item(x-i, y);
                whatIn = b->text().toInt();
                if(whatIn == 0)
                    break;
                if(whatIn == val*10)
                {
                    temp.row = x-i;
                    temp.col = y;
                    hitted.push_back(temp);
                }
            }
        }


            //qDebug() << "XXX = " <<x <<" YYY = " <<y;

        //jeśli trafionych pól jest tyle ilu masztowy jest statek, wówczas zaznacz jako trafiony-zatopiony
        if(hitted.size() == val)
        {
            for(int i=0; i < hitted.size(); ++i)
            {
                temp = hitted[i];
                myBoard->setItem(temp.row, temp.col, new QTableWidgetItem(QString::number(val*100)));
                myBoard->item(temp.row,temp.col)->setBackground(Qt::green);
                myBoard->item(temp.row,temp.col)->setFlags(Qt::ItemIsEditable);
                //myBoard->item(temp.row,temp.col)->flags() & !Qt::ItemIsEditable
            }
        }

        hitted.clear();
    }

    else
    {
        return;
    }

        //qDebug() << "XXX = " <<x <<" YYY = " <<y;
}



Game::~Game()
{

}
