/*!
*@file board.h
*@brief Plik nagłówkowy do biblioteki board.cpp, przechowuje deklaracje funkcji.
*/

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




/*!
 * \brief W klasie Board zostały zawarte pola i metody służące do obsługi planszy gry zarówno dla bota jak i dla gracza.
 */
class Board: public QTableWidget
{
private:
    int boardWidth;
    int boardHeight;
    QTableWidget *myTable;
    bool userTable;
    QColor colorNormal;

    /*!
     * \brief Wypełnia plansze pustymi polami
     */
    void makeWater();

    /*!
     * \brief Generuje losowe współrzędne na planszy i sprawdza czy na tych współrzędnych (lub w pobliżu) nie znajduje się już inny statek. Jeżeli pola są wolne, dodawany jest tam nowy statek.
     * \param int - Długość statku
     * \return bool - True - dodano statek, False - nie udało się dodać statku
     */
    bool addShip(int shipLength);



public:
    /*!
     * \brief Konstruktor dla klasy Board
     *
     * \param int - Szerokość planszy
     * \param int - Wysokość planszy
     * \param QTableWidget - Tabela w graficznym interfejsie użytkownika
     * \param bool - True - tablica użytkownika (gracza), False - tablica bota
     */
    Board(int, int, QTableWidget *, bool);



    /*!
     * \brief Tworzy planszę o konkretnych wymiarach, ustawia jej właściwości wizualne oraz wywołuje funkcję wypełniającą planszę pustymi polami
     */
    void createBoard();




    /*!
     * \brief Funkcja sprawdza wszystkie statki do dodania, wywołuje funkcję generującą losowe współrzędne na planszy i sprawdzającą czy na tych współrzędnych (lub w pobliżu) nie znajduje się już inny statek. Jeżeli pola są wolne, dodaje tam nowy statek.
     *
     * \param QColor - Kolor statku na planszy
     */
    void addShipsToBoard(QColor);




    /*!
     * \brief Destruktor klasy Board
     */
    ~Board();
};

#endif // BOARD_H
