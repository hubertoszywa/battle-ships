#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constant.h"

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
    void fillSpinBoxes();


    // --- rulesPage ---

    void on_buttonBackToMenuFromRules_clicked();

    void on_buttonStartGame_clicked();


    // --- before game ---

    void preparingToPlay();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
