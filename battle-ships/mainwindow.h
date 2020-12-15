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

#include "constant.h"
#include "board.h"
#include "player.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void resizeEvent(QResizeEvent* evt) override;

private slots:

    // --- mainPage ---

    void on_buttonNewGame_clicked();

    void on_buttonRules_clicked();

    void on_buttonAuthors_clicked();

    void on_buttonExit_clicked();


    // --- optionGamePage ---

    void on_buttonBackToMenu_clicked();
    void on_buttonBackToMenu2_clicked();

    void fillSpinBoxes();


    // --- rulesPage ---

    void on_buttonBackToMenuFromRules_clicked();

    void on_buttonStartGame_clicked();


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

private:
    Ui::MainWindow *ui;
    Player user;
    Player bot;
    QBasicTimer timer;
    int count;

};

#endif // MAINWINDOW_H
