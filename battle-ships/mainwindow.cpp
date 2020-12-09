#include "mainwindow.h"
#include "board.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar2->showMessage("Battle Ships v1.1.4", 5000);
    connect( ui->table1, &Board::itemClicked, this, &MainWindow::theGame );
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

void MainWindow::preparingToPlay() {
    srand(time(NULL));
    // pobranie wartości z ustaloną szerokością i wysokością
    int width = ui->spinBoxWidth->value();
    int height = ui->spinBoxHeight->value();

    Board myBoard1(width, height, ui->table1);
    Board myBoard2(width, height, ui->table2);

    myBoard1.createBoard();
    myBoard2.createBoard();

    myBoard1.addShipsToBoard();
    myBoard2.addShipsToBoard();
}





void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->optionGamePage);
    fillSpinBoxes();
}





/* the game */


void MainWindow::theGame( QTableWidgetItem *pItem )
{
    Game a(ui->table1, ui->spinBoxWidth->value(), ui->spinBoxHeight->value());
    a.showMyItem(pItem);


}

