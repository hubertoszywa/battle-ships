/*!
*@file game.h
*@brief Plik nagłówkowy do biblioteki mainwindows.cpp, przechowuje deklaracje funkcji.
*/


/** @mainpage Programowanie w języku C 2 (projekt 2020/2021)
*@brief --- Politechnika Świętokrzyska 2020 / 2021, studia niestacjonarne - semestr III. ----
*@brief Wydział Elektrotechniki, Automatyki i Informatyki. Kierunek: Informatyka
*@brief Temat: Gra Statki. Przeciwnikiem komputer.
*@authors Hubert Oszywa (GR 2IZ12A), Hubert Michnicki (GR 2IZ12A), Jaroslaw Majcherczyk (GR 2IZ12A)
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableWidget>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QTime>
#include <QBasicTimer>
#include <QRgb>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QPair>
#include <QtAlgorithms>
#include <QColor>
#include <QColorDialog>
#include "constant.h"
#include "board.h"
#include "player.h"
#include "ships.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




/*!
 * \brief Klasa zawierająca główny silnik gry. Pozwala na detekcję ruchów gracza oraz decydowanie o tym czyja jest kolej na oddanie strzału - gracza czy bota.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    /*!
     * \brief MainWindow - Kontruktor klasy
     * \param parent
     */
    MainWindow(QWidget *parent = nullptr);


    /*!
    *\brief Dekonstruktor klasy
    */
    ~MainWindow();




    // ---------- ZMIENNE PUBLICZNE ----------

    /** Współrzędne ostatnio oddanego strzału*/
    Point prevShotField;

    /** Współrzędne tymczasowe (zmienna pomocnicza) */
    Point tempField;

    /** Zmienna przechowująca informację, czy oddawany strzał w statek był pierwszy czy nie: True - pierwszy strzał w statek, False - kolejne strzały w statek*/
    bool firstShotInShip = true;

    /** Kolor nietrafionego masztu */
    QColor c1 = Qt::red;

    /** Kolor trafionego masztu */
    QColor c2 = Qt::yellow;

    /** Kolor zatopionego statku */
    QColor c3 = Qt::green;

    /** Kolor pól gdzie nie ma statków (wody) */
    QColor c4 = Qt::gray;





    // ---------- METODY PUBLICZNE ----------
    /*!
     * \brief fieldBasedLvl - Funkcja losująca współrzędne punktu dla bota w zależności od wybranego poziomu trudności
     * \param level - Informacja o poziomie trudności
     * \return - Współrzędne wylosowanego punktu do strzału przez bota
     */
    Point fieldBasedLvl(int level);



protected:
    void resizeEvent(QResizeEvent* evt) override;

private slots:

    // --- mainPage ---

    void on_buttonNewGame_clicked();

    void on_buttonBestScores_clicked();

    void on_buttonRules_clicked();

    void on_buttonAuthors_clicked();

    void on_buttonExit_clicked();

    void setMusic();


    // --- optionGamePage ---

    void on_buttonBackToMenu_clicked();

    void fillSpinBoxes();

    void on_buttonStartGame_clicked();

    void setPreviewColor();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();




    // --- rulesPage ---

    void on_buttonBackToMenuFromRules_clicked();




    // --- before game ---

    void preparingToPlay();

    void on_pushButton_clicked();



    // --- game ---
    void theGame( QTableWidgetItem *userShot );

    void botMove();

    /* Opóźnienie ruchu dla bota symulujące, że się zastanawia... */
    void delay(int secs);

    void timerEvent(QTimerEvent *event);



    // --- after game ---
    void showSummaryPage();

    void on_buttonBackToMenu_2_clicked();

    void on_pushButton_2_clicked();



    // --- best scores page ---


    void on_buttonBackToMenu_5_clicked();





private:
    Ui::MainWindow *ui;
    Player user;
    Player bot;
    QBasicTimer timer;
    int count;
    QMediaPlayer * music1 = new QMediaPlayer();
    QMediaPlayer * music2 = new QMediaPlayer();
    QMediaPlayer * sinkSound = new QMediaPlayer();
    QMediaPlayer * hitSound = new QMediaPlayer();
    QMediaPlayer * waterSound = new QMediaPlayer();
};

#endif // MAINWINDOW_H
