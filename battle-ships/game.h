/*!
*@file game.h
*@brief Plik nagłówkowy do biblioteki game.cpp, przechowuje deklaracje funkcji.
*/

#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QApplication>
#include <QTableWidget>
#include <QDebug>
#include <board.h>
#include "ships.h"
#include "player.h"


/*!
 * \brief W klasie Game zostały zawarte pola i metody służące do obsługi rozgrywki - sprawdzania sytuacji, w których statek został trafiony lub zatopiony.
 */
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
    /*!
     * \brief Game - Konstruktor klasy Game
     * \param z - Tabela w graficznym interfejsie użytkownika
     * \param pItem - Komórka w tabli w graficznym interfejsie użytkownika
     */
    Game(QTableWidget *z, QTableWidgetItem *pItem);



    /*!
     * \brief gameMove - Sprawdza jakie pole zostało trafione (statek trafiony, zatopiony czy pudło) i w zależności od tego zmienia widok pola na planszy
     * \param player - Informacja czy ruch wykonał gracz czy bot
     * \param QColor - Kolor statku trafionego
     * \param QColor - Kolor statku zatopionego
     * \param QColor - Kolor pudła
     * \return Zwraca nową wartość liczbową dla pola w tabeli
     */
    int gameMove(Player *player, QColor, QColor, QColor);



    /*!
     * \brief gameCheckFields - Sprawdza pola wokół trafionego punktu. W przypadku gdy istnieją inne trafione pola, współrzędne punktu dodawane są do wektora QVector.
     */
    void gameCheckFields();


    /*!
     *\brief Destruktor klasy Game
     */
    ~Game();
};

#endif // GAME_H
