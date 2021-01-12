/*!
*@file constant.h
*@brief Plik zawierający najważniejsze stałe, niezbędne do prawidłowego działania aplikacji. To tutaj prgramista w łatwy sposób, od strony backendu może zmieniać najważniejsze parametry rozgrywki.
*/

#ifndef CONSTANT_H
#define CONSTANT_H


//------------ USTAWIENIA PLANSZY ------------

/** Minimalna szerokość planszy */
const int MIN_WIDTH = 10;

/** Maksymalna szerokość planszy  */
const int MAX_WIDTH = 20;

/** Domyślna szerokość planszy */
const int DEFAULT_WIDTH = 12;

/** Minimalna wysokość planszy */
const int MIN_LENGTH = 10;

/** Maksymalna wysokość planszy */
const int MAX_LENGTH = 20;

/** Domyślna wysokość planszy */
const int DEFAULT_LENGTH = 12;





//------------ USTAWIENIA STATKÓW ------------

/** Liczba statków do rozmieszczenia na planszy
    UWAGA! Przy zmianie wartości dodaj rodzaje statków
*/
const int NUMBEROFSHIPS = 9;

/** Rodzaje statków - Ilu masztowe? */
const int SHIPS[NUMBEROFSHIPS] = {5, 4, 3, 3, 2, 2, 1, 1, 1};


#endif // CONSTANT_H
