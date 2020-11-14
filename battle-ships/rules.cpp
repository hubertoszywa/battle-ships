#include "rules.h"
#include "ui_rules.h"
#include "mainwindow.h"

Rules::Rules(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rules)
{
    ui->setupUi(this);
}

Rules::~Rules()
{
    delete ui;
}

void Rules::on_backFromRules_clicked()
{
    hide();
    MainWindow w;
    w.show();
}
