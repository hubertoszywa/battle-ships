#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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



void MainWindow::preparingToPlay() {

    // generowanie tabeli na podstawie ustalonych wartości
    int width = ui->spinBoxWidth->value();
    int height = ui->spinBoxHeight->value();
    QString tmp = QString::number(height);
    QString tmp2 = QString::number(width);

    ui->heightGame->setText(QString(tmp));
    ui->widthGame->setText(QString(tmp2));


    ui->table1->setRowCount(width);
    ui->table1->setColumnCount(height);

    ui->table2->setRowCount(width);
    ui->table2->setColumnCount(height);

//    for(int r=0; r<height; r++)
//    {
//        for(int c=0; c<width; c++)
//        {
//            QModelIndex index = ui->table1->model()->index(r,c, QModelIndex());
//            index.data()=2;
//            // Do something with the QVariant that index.data() returns
//            //qDebug() << r << c << index.data().toString();
//        }
//    }

//    game_ = startGame(this, width, length);
//    game_->controller->initialStateOfBoard();
//    placeShips(*(game_->controller), *(game_->desk), 1);
//    placeShips(*(game_->controller), *(game_->desk), 2);
//    prepareGameBoards();
}
