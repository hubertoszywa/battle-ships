#include "mainwindow.h"
#include "board.h"
#include "game.h"
#include "player.h"
#include "ui_mainwindow.h"



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


void MainWindow::timerEvent(QTimerEvent *event)
{
    count++;
    ui->clock->display(count/10.0);
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

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->optionGamePage);
    fillSpinBoxes();
}


/*  after game  */

void MainWindow::showSummaryPage()
{
    timer.stop();
    ui->stackedWidget->setCurrentWidget(ui->summaryPage);
    ui->lcd_botAllShots->display(bot.numberOfShots);
    ui->lcd_botGoodShots->display(bot.hitShots);
    ui->lcd_botBadShots->display(bot.missShots);
    ui->lcd_bot10Shots->display(bot.sunkShips);

    ui->lcd_userAllShots->display(user.numberOfShots);
    ui->lcd_userGoodShots->display(user.hitShots);
    ui->lcd_userBadShots->display(user.missShots);
    ui->lcd_user10shots->display(user.sunkShips);

    ui->lcd_gameTime->display(count/10.0);

}


/*  before game  */

void MainWindow::preparingToPlay() {
    srand(time(NULL));

    // pobranie wartości z ustaloną szerokością i wysokością
    int width = ui->spinBoxWidth->value();
    int height = ui->spinBoxHeight->value();

    //przygotowanie tablicy statystyk dla użytkownika
    ui->lcdNumber_1->display(0);
    ui->lcdNumber_2->display(0);
    ui->lcdNumber_3->display(0);
    ui->lcdNumber_4->display(0);
    user.playerStart();


    //przygotowanie tablicy statystyk dla bota
    ui->lcdNumber_5->display(0);
    ui->lcdNumber_6->display(0);
    ui->lcdNumber_7->display(0);
    ui->lcdNumber_8->display(0);
    bot.playerStart();


    // wygenerowanie tablicy dla gracza i bota
    Board myBoard1(width, height, ui->table1);
    Board myBoard2(width, height, ui->table2);
    myBoard1.createBoard();
    myBoard2.createBoard();


    // wygenerowanie i rozmieszczenie statków na planszy
    myBoard1.addShipsToBoard();
    myBoard2.addShipsToBoard();


    //uruchomienie zegara
    count = 0;
    timer.start(60,this);


    // wylosowanie gracza do pierwszego ruchu (bot czy user)
    int random = rand()%2;
    if(random == 1)
    {
        QPalette myPallete;
        myPallete.setColor(QPalette::Window, qRgb(255,255,0));
        myPallete.setColor(QPalette::WindowText, Qt::black);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Twój ruch...");
    }
    else
    {
        QPalette myPallete;
        myPallete.setColor(QPalette::Window, Qt::gray);
        myPallete.setColor(QPalette::WindowText, Qt::white);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Strzela bot...");
        botMove();
    }

}




void MainWindow::botMove()
{
    delay(3);

    QPalette myPallete;
    myPallete.setColor(QPalette::Window, Qt::gray);
    myPallete.setColor(QPalette::WindowText, Qt::white);
    ui->infoBox->setPalette(myPallete);
    ui->infoBox->setText("Strzela bot...");

    QTableWidgetItem *botShot;
    botShot = ui->table2->item(rand()%ui->table2->columnCount()+0, rand()%ui->table2->rowCount()+0 );
    Game move(ui->table2, botShot);
    int shot = move.gameMove(&bot);
    ui->lcdNumber_5->display(bot.numberOfShots);
    ui->lcdNumber_6->display(bot.hitShots);
    ui->lcdNumber_7->display(bot.missShots);
    ui->lcdNumber_8->display(bot.sunkShips);

    if(shot == 1)
    {
        myPallete.setColor(QPalette::Window, Qt::blue);
        myPallete.setColor(QPalette::WindowText, Qt::white);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Bot trafił w Twój statek! Bot strzela ponownie...");
        botMove();
    }
    else if(shot == 10)
    {
        if(bot.playerWin() == true)
        {
            myPallete.setColor(QPalette::Window, Qt::red);
            myPallete.setColor(QPalette::WindowText, Qt::white);
            ui->infoBox_3->setPalette(myPallete);
            ui->infoBox_3->setText("Bot wygrywa! Niestety, przegrałeś...");
            showSummaryPage();
        }
        else
        {
            myPallete.setColor(QPalette::Window, Qt::red);
            myPallete.setColor(QPalette::WindowText, Qt::white);
            ui->infoBox->setPalette(myPallete);
            ui->infoBox->setText("Bot zatopił Twój statek! Bot strzela ponownie...");
            botMove();
        }

    }
    else if(shot == -1)
    {
        botMove();
    }
    else
    {
        myPallete.setColor(QPalette::Window, qRgb(255,255,0));
        myPallete.setColor(QPalette::WindowText, Qt::black);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Twój ruch...");
    }
}





/* the game */

void MainWindow::theGame( QTableWidgetItem *userShot )
{
    QPalette myPallete;
    Game move(ui->table1, userShot);
    int shot = move.gameMove(&user);
    ui->lcdNumber_1->display(user.numberOfShots);
    ui->lcdNumber_2->display(user.hitShots);
    ui->lcdNumber_3->display(user.missShots);
    ui->lcdNumber_4->display(user.sunkShips);

    if(shot == 1)
    {
        myPallete.setColor(QPalette::Window, Qt::blue);
        myPallete.setColor(QPalette::WindowText, Qt::white);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Trafiłeś w statek przeciwnika!");

        delay(2);

        myPallete.setColor(QPalette::Window, qRgb(255,255,0));
        myPallete.setColor(QPalette::WindowText, Qt::black);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Kontynuuj... Twój ruch!");
    }
    else if(shot == 10)
    {
        myPallete.setColor(QPalette::Window, Qt::green);
        myPallete.setColor(QPalette::WindowText, Qt::white);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Zatopiłeś statek przeciwnika!");

        if(user.playerWin() == true)
        {
            myPallete.setColor(QPalette::Window, Qt::green);
            myPallete.setColor(QPalette::WindowText, Qt::white);
            ui->infoBox_3->setPalette(myPallete);
            ui->infoBox_3->setText("Wygrywasz grę!");
            showSummaryPage();
        }
        else
        {
            delay(2);
            myPallete.setColor(QPalette::Window, qRgb(255,255,0));
            myPallete.setColor(QPalette::WindowText, Qt::black);
            ui->infoBox->setPalette(myPallete);
            ui->infoBox->setText("Kontynuuj... Twój ruch!");
        }
    }
    else if(shot == -1)
    {
        myPallete.setColor(QPalette::Window, qRgb(255,255,0));
        myPallete.setColor(QPalette::WindowText, Qt::black);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Już tu strzelałeś... Spróbuj ponownie!");
    }
    else
    {
        myPallete.setColor(QPalette::Window, Qt::gray);
        myPallete.setColor(QPalette::WindowText, Qt::white);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Strzela bot...");
        botMove();
    }
}



void MainWindow::delay(int secs)
{
    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}




void MainWindow::on_buttonBackToMenu_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->optionGamePage);
    fillSpinBoxes();
}
