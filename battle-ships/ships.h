/*!
*@file ships.h
*@brief Plik nagłówkowy przechowujący strukturę dla konkretnego punktu na planszy.
*/


#ifndef SHIPS_H
#define SHIPS_H

/*!
 * \brief Struktura punktu. Służy do przechowywania współrzędnych konkrentego punktu na planszy.
 */
struct Point {
    //Point(int col, int row);

    /** Współrzędna x */
    int col;

    /** Współrzędna y */
    int row;
};



#endif // SHIPS_H
