/*!
*@file player.h
*@brief Plik nagłówkowy do biblioteki player.cpp, przechowuje deklaracje klasy Player.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QString>
#include "constant.h"
#include <QFile>
#include <QTextStream>

/*!
 * \brief W klasie Player znalazły się pola i metody służące do przechowywania i zbierania informacji na temat statystyk danego gracza (lub bota)
 */
class Player
{
public:

    /** Zawiera całkowitą liczbę strzałów*/
    int numberOfShots;

    /** Zawiera liczbę strzałów celnych*/
    int hitShots;

    /** Zawiera liczbę strzałów spudłowanych*/
    int missShots;

    /** Zawiera liczbę statków zatopionych */
    int sunkShips;

    /** Zawiera wynik jaki osiągnął gracz */
    int score;

    /** Przechowuje informację o poziomie trudności */
    QString level;




    /*!
     * \brief Player - Konstruktor klasy
     */
    Player();


    /*!
     * \brief playerStart - Przypisuje początkowe wartości dla zmiennych zawierających statystyki rozgrywki
     */
    void playerStart();


    /*!
     * \brief playerShot - Dopisuje punkty do odpowiedniej statystki w zależności od tego czy strzał był celny lub niecelny
     * \param hit
     */
    void playerShot(int hit);



    /*!
     * \brief playerWin - Sprawuje kontrolę nad tym czy nie powinien nastąpić koniec gry (w przypadku zatomienia ostatniego statku)
     * \return True - koniec gry, False - kontynuacja gry
     */
    bool playerWin();


    /*!
     * \brief countScore - Oblicza wynik rozgrywki dla gracza i zapisuje go do pliku
     * \param bott - Obiekt bota
     * \param time - Czas gry w sekundach
     * \param lvl - Informacja o poziomie trudności
     */
    void countScore(Player bott, int time, int lvl);

};




#endif // PLAYER_H
