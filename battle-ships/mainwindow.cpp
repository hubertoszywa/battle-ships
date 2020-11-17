#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    Dodanie zdjęcia
//    QPixmap pix("C:/Users/huber/OneDrive/Pulpit/battle-ships/battle-ships/assets/main-photo.png");
//    ui->label_pic->setPixmap(pix.scaled(800,600,Qt::KeepAspectRatio));

    ui->statusbar2->showMessage("Battle Ships v1.1.4", 5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Wyświetlanie i dopasowanie obrazka w tle */
void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/resources/assets/img/main-photo.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    Board game;
    QMainWindow::resizeEvent(evt); // call inherited implementation
}


void MainWindow::on_buttonNewGame_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->optionGamePage);
    fillSpinBoxes();
}

void MainWindow::on_buttonRules_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->rulesPage);
}

void MainWindow::on_buttonAuthors_clicked()
{
    QString authorsText = "Hubert Oszywa - 12A \nHubert Michnicki - 12 \nJarosław Majecherczyk - 12A";
    QMessageBox::about(this, "Autorzy", authorsText);
}

void MainWindow::on_buttonExit_clicked()
{
    QString exitGameString = "Czy na pewno chcesz zakończyć grę Bitwa w Statki?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Zakończyć grę?", exitGameString, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
         QApplication::quit();
}



/*  optionGamePage   */

void MainWindow::fillSpinBoxes()
{
    ui->spinBoxWidth->setRange(MIN_WIDTH, MAX_WIDTH);
    ui->spinBoxWidth->setValue(DEFAULT_WIDTH);
    ui->spinBoxHeight->setRange(MIN_LENGTH, MAX_LENGTH);
    ui->spinBoxHeight->setValue(DEFAULT_LENGTH);
}


void MainWindow::on_buttonBackToMenu_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->mainPage);
}






/*  rulesPage   */

void MainWindow::on_buttonBackToMenuFromRules_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_buttonStartGame_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    preparingToPlay();
}





/*  before game  */


void MainWindow::makeWater(int width, int height)
{
    for(int i=0; i < width; i++)
        for(int j=0; j < height; j++)
           ui->table1->setItem(i,j,new QTableWidgetItem(QString::number(0)));
}


void MainWindow::addShipsToBoard(int width, int height)
{
    for(int i=0; i<numberOfShips; ++i)
    {
        while(!addShip(width, height, ships[i]));
    }
}


bool MainWindow::addShip(int width, int height, int shipLength)
{
    //losowanie kierunku, w którą ma być układany statek
    bool direction = rand()%2; //0 = poziomo, 1 = pionowo

    //losowanie współrzędnych pola, od którego ma zacząć się dodawanie statku
    //z jednoczesnym ograniczeniem planszy (tak, żeby statek nie wyszedł "po za"
    int x = rand()%(direction ? width : (1+width-shipLength));
    int y = rand()%(direction ? (1+height-shipLength) : height);

    //sprawdzanie czy pola które ma zająć statek są dozwolone (czyli czy nie są 1 lub 2)
    for(int i = 0; i<shipLength; ++i)
    {
        int val;
        QTableWidgetItem *a = ui->table1->item(x+(direction ? 0 : i), y+(direction ? i : 0));
        val = a->text().toInt();
        if(val > 0)
            return false;
    }

    for(int i = 0; i<shipLength; ++i)
    {
        ui->table1->setItem(x+(direction ? 0 : i), y+(direction ? i : 0), new QTableWidgetItem(QString::number(666)));
    }
    //TESTOWO dodanie pola
    //ui->table1->setItem(x,y,new QTableWidgetItem(QString::number(1)));

    return true;

}



void MainWindow::preparingToPlay() {
    // generowanie tabeli na podstawie ustalonych wartości
    int width = ui->spinBoxWidth->value();
    int height = ui->spinBoxHeight->value();

    ui->table1->setRowCount(width);
    ui->table1->setColumnCount(height);


    QHeaderView *headerView = ui->table1->horizontalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);
    headerView = ui->table1->verticalHeader();
    headerView->setSectionResizeMode(QHeaderView::Stretch);



    makeWater(width, height);
    addShipsToBoard(width, height);

}
