#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/huber/OneDrive/Pulpit/battle-ships/battle-ships/assets/main-photo.png");
    ui->label_pic->setPixmap(pix.scaled(800,600,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_2_clicked()
{
    rules = new Rules(this);
    rules->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString exitGameString = "Czy na pewno chcesz zakończyć grę Bitwa w Statki?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Zakończyć grę?", exitGameString, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
         QApplication::quit();
}
