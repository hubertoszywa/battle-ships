/*!
*@file mainwindow.cpp
*@brief Funkcje z tej biblioteki zawierają mechanizmy pozwalające na detekcję ruchów gracza oraz decydowanie o tym czyja jest kolej na oddanie strzału - gracza czy bota. Również tutaj ustalane są efekty dźwiękowe oraz działanie menu gry.
*/


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
    ui->table1->verticalHeader()->setStyleSheet("QHeaderView { qproperty-defaultAlignment: AlignHCenter; }");
    ui->table2->verticalHeader()->setStyleSheet("QHeaderView { qproperty-defaultAlignment: AlignHCenter; }");
}



MainWindow::~MainWindow()
{
    delete ui;
}



/* Ustalenie sciezek dzwiekowych */
void MainWindow::setMusic()
{
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/resources/assets/music/menu-music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music1->setPlaylist(playlist);

    music1->play();

    QMediaPlaylist *playlist2 = new QMediaPlaylist();
    playlist2->addMedia(QUrl("qrc:/resources/assets/music/game-music.mp3"));
    playlist2->setPlaybackMode(QMediaPlaylist::Loop);
    music2->setPlaylist(playlist2);

    waterSound->setMedia(QUrl("qrc:/resources/assets/sounds/water-sound.mp3"));
    hitSound->setMedia(QUrl("qrc:/resources/assets/sounds/hit-sound.mp3"));
    sinkSound->setMedia(QUrl("qrc:/resources/assets/sounds/sink-sound.mp3"));
}




/* Wyświetlanie i dopasowanie obrazka w tle */
void MainWindow::resizeEvent(QResizeEvent* evt)
{
    QPixmap bkgnd(":/resources/assets/img/main-photo.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;

    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    setMusic();

    QMainWindow::resizeEvent(evt); // call inherited implementation
}



/* Uruchomienie licznika czasu na starcie gry */
void MainWindow::timerEvent(QTimerEvent *event)
{
    count++;
    ui->clock->display(count/10.0);
}





/* Opóźnienie w ruchu bota */
void MainWindow::delay(int secs)
{
    QTime dieTime= QTime::currentTime().addSecs(secs);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



/* ------------ main window ------------*/


void MainWindow::on_buttonNewGame_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->optionGamePage);
    fillSpinBoxes();
    setPreviewColor();
}



bool scoreCompare(QPair<QString, int> score1, QPair<QString, int> score2)
{
    return score1.second > score2.second;
}

void MainWindow::on_buttonBestScores_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->bestScoresPage);
    QFile file("scores.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        ui->labelBestScores->setText("Brak wyników do wyświetlenia.");
    }

    QTextStream in(&file);
    QString line;
    QString line1;
    QString line2;
    QList<QPair<QString,int>> items;
    QPair<QString,int> pair;


    while(!in.atEnd()) {
        line1 = in.readLine();
        line2 = in.readLine();


        pair.first = line1;
        pair.second = line2.toInt();
        items.append(pair);
    }

    if(items.isEmpty())
        ui->labelBestScores->setText("Brak wyników do wyświetlenia.");
    else
    {
        std::sort(items.begin(), items.end(), scoreCompare);
        int i = 1;
        foreach(auto &x,items)
        {
            line.append(QString::number(i) + ". " + QString::number(x.second) + " / " + x.first + "\n");
            i++;
            if(i == 11)
                break;
        }
        ui->labelBestScores->setText(line);
    }

    file.close();
}


void MainWindow::on_buttonRules_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->rulesPage);
}

void MainWindow::on_buttonAuthors_clicked()
{
    QString authorsText = "Hubert Oszywa - 12A \nHubert Michnicki - 12A \nJarosław Majecherczyk - 12A";
    QMessageBox::about(this, "Autorzy", authorsText);
}

void MainWindow::on_buttonExit_clicked()
{
    QString exitGameString = "Czy na pewno chcesz zakończyć grę Bitwa w Statki?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Zakończyć grę?", exitGameString, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
         QApplication::quit();
}





/*  ------------ optionGamePage ------------ */

void MainWindow::fillSpinBoxes()
{
    ui->spinBoxWidth->setRange(MIN_WIDTH, MAX_WIDTH);
    ui->spinBoxWidth->setValue(DEFAULT_WIDTH);
    ui->spinBoxHeight->setRange(MIN_LENGTH, MAX_LENGTH);
    ui->spinBoxHeight->setValue(DEFAULT_LENGTH);
}


void MainWindow::setPreviewColor()
{
    QPalette pal = ui->shipsColor1->palette();
    pal.setColor(QPalette::Window, QColor(c1));
    ui->shipsColor1->setPalette(pal);

    pal = ui->shipsColor2->palette();
    pal.setColor(QPalette::Window, QColor(c2));
    ui->shipsColor2->setPalette(pal);

    pal = ui->shipsColor3->palette();
    pal.setColor(QPalette::Window, QColor(c3));
    ui->shipsColor3->setPalette(pal);

    pal = ui->shipsColor4->palette();
    pal.setColor(QPalette::Window, QColor(c4));
    ui->shipsColor4->setPalette(pal);

}


void MainWindow::on_buttonBackToMenu_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->mainPage);

}

void MainWindow::on_buttonStartGame_clicked()
{

    music1->stop();
    music2->play();
    ui->stackedWidget->setCurrentWidget(ui->gamePage);
    preparingToPlay();

}

void MainWindow::on_pushButton_clicked()
{
    QString exitPlay = "Czy na pewno chcesz zakończyć aktualną rozgrywkę?";
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Zakończyć grę?", exitPlay, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        music2->stop();
        music1->play();
        ui->stackedWidget->setCurrentWidget(ui->optionGamePage);
        fillSpinBoxes();
        setPreviewColor();
    }
    else { qDebug() << "Użytkownik chciał opuścic rozgrywkę, ale tego nie zrobił"; }
}





/*  ------------ rulesPage ------------ */

void MainWindow::on_buttonBackToMenuFromRules_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mainPage);
}



/* ------------ before game ------------ */

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
    Board myBoard1(width, height, ui->table1, true);
    Board myBoard2(width, height, ui->table2, false);
    myBoard1.createBoard();
    myBoard2.createBoard();


    // wygenerowanie i rozmieszczenie statków na planszy
    myBoard1.addShipsToBoard(c1);
    myBoard2.addShipsToBoard(c1);


    //uruchomienie zegara
    count = 0;
    timer.start(60,this);


    //ustalenie poczatkowych wartosci dla zmiennej przychowujacej informacje o ostanim ruchu
    prevShotField.col = -1;
    prevShotField.row = -1;


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



/* ------------ after game ------------  */

void MainWindow::showSummaryPage()
{
    music2->stop();
    music1->play();

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
    user.countScore(bot, count/10.0, ui->buttonGroup->checkedId());
    ui->lcd_gameScore->display(user.score);
    qDebug() << "Poziom trudnosci = " << user.level;


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



/* ------------ ruch bota ------------*/

void MainWindow::botMove()
{
    delay(2); //sztuczne opóźnienie ruchu bota

    QPalette myPallete;
    QTableWidgetItem *botShot;
    Point currShotField;
    int btn_id = 0;

    myPallete.setColor(QPalette::Window, Qt::gray);
    myPallete.setColor(QPalette::WindowText, Qt::white);
    ui->infoBox->setPalette(myPallete);
    ui->infoBox->setText("Strzela bot...");

    btn_id = ui->buttonGroup->checkedId(); // pobranie ID wybranego poziomu trudności
    currShotField = fieldBasedLvl(btn_id); // wylosowanie współrzędnych pola do strzału
    botShot = ui->table2->item(currShotField.row, currShotField.col);

    Game move(ui->table2, botShot);
    int shot = move.gameMove(&bot, c2, c3, c4);

    ui->lcdNumber_5->display(bot.numberOfShots);
    ui->lcdNumber_6->display(bot.hitShots);
    ui->lcdNumber_7->display(bot.missShots);
    ui->lcdNumber_8->display(bot.sunkShips);


    // podjęcie decyzji w zależności od tego czy strzał był celny (statek trafiony lub zatopiony) czy niecelny
    if(shot == 1)
    {
        myPallete.setColor(QPalette::Window, Qt::blue);
        myPallete.setColor(QPalette::WindowText, Qt::white);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Bot trafił w Twój statek! Bot strzela ponownie...");
        hitSound->play();
        prevShotField.col = currShotField.col;
        prevShotField.row = currShotField.row;
        if(firstShotInShip)
        {
            tempField.col = currShotField.col;
            tempField.row = currShotField.row;
            firstShotInShip = false;
        }
        botMove();
    }
    else if(shot == 10)
    {
        prevShotField.col = -1; prevShotField.row = -1;
        firstShotInShip = true;
        sinkSound->play();
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
    else
    {
        myPallete.setColor(QPalette::Window, qRgb(255,255,0));
        myPallete.setColor(QPalette::WindowText, Qt::black);
        ui->infoBox->setPalette(myPallete);
        ui->infoBox->setText("Twój ruch...");
        waterSound->play();
    }
}



/* ------------ ruch gracza ------------ */

void MainWindow::theGame( QTableWidgetItem *userShot )
{
    QPalette myPallete;
    Game move(ui->table1, userShot);
    int shot = move.gameMove(&user, c2, c3, c4);
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
        hitSound->play();

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
        sinkSound->play();

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
        waterSound->play();
        botMove();
    }
}


/* wybranie odpowiedniego pola strzalu dla bota w zaleznosci od poziomu trudnosci*/


Point MainWindow::fieldBasedLvl(int level)
{
    srand(time(NULL));
    Point temp;
    QTableWidgetItem * a;
    int whatIn;

    //POZIOM ŁATWY
    if(level == -2)
    {
        while(1)
        {
            temp.col = rand()%ui->table2->columnCount()+0;
            temp.row = rand()%ui->table2->rowCount()+0;
            a = ui->table2->item(temp.row , temp.col); whatIn = a->text().toInt();
            if(whatIn <= 0 || (whatIn >= 1 && whatIn <=9)) break;
        }

        return temp;
    }




    //POZIOM NORMALNY
    else if (level == -3)
    {
        //jeżeli poprzedni strzał był niecelny, wybierz nowe pole losowo
        if(prevShotField.col == -1)
        {
            while(1)
            {
                temp.col = rand()%ui->table2->columnCount()+0;
                temp.row = rand()%ui->table2->rowCount()+0;
                a = ui->table2->item(temp.row , temp.col); whatIn = a->text().toInt();
                if(whatIn < 0 || (whatIn >= 1 && whatIn <=9)) break;
            }

            return temp;
        }

        //jeżeli poprzedni strzał byl celny, strzelaj niedaleko...
        else
        {
            int x, y;
            bool stillwhile = false;

            do
            {
                //losowanie kierunku strzału
                bool direction = false ; // false - poziomo, true - pionowo
                int r = rand()%2; if(r == 0) direction = true;


                //losowanie pola strzału (w lewo lub w prawo lub w górę lub w dół)
                r = rand()%2;
                if(direction == false)
                {
                    if(r == 0) {x = prevShotField.col; y = prevShotField.row + 1; } //w prawo
                    else {x = prevShotField.col; y = prevShotField.row - 1; } //w lewo
                }
                else
                {
                    if(r == 0) { x = prevShotField.col + 1; y = prevShotField.row; } //w górę
                    else { x = prevShotField.col - 1; y = prevShotField.row; } //w dół
                }


                //weryfikacja czy po przesunieciu nie wyszliśmy spoza planszy
                if(x >= ui->spinBoxWidth->value()) x = prevShotField.col - 1;
                if(x < 0) x = prevShotField.col + 1;
                if(y >= ui->spinBoxHeight->value()) y = prevShotField.row - 1;
                if(y < 0) y = prevShotField.row + 1;


                a = ui->table2->item(y, x);
                whatIn = a->text().toInt();
                stillwhile = false;

                if(whatIn > 10 && whatIn < 1000 )
                {
                    prevShotField.col = x;
                    prevShotField.row = y;
                    stillwhile = true;
                }

                if(whatIn == 1000) stillwhile = true;

            } while(stillwhile);

            temp.col = x;
            temp.row = y;

            return temp;
        }
    }



    //POZIOM TRUDNY
    else
    {
       //jeżeli poprzedni strzał był niecelny, wybierz nowe pole losowo
        if(prevShotField.col == -1)
        {
            while(1)
            {
                temp.col = rand()%ui->table2->columnCount()+0;
                temp.row = rand()%ui->table2->rowCount()+0;
                a = ui->table2->item(temp.row , temp.col); whatIn = a->text().toInt();
                if(whatIn < 0 || (whatIn >= 1 && whatIn <=9)) break;
            }

            return temp;
        }

        //jeżeli poprzedni strzał byl celny, zestrzel statek...
        else
        {
            int x, y;

            while(1)
            {
                x = prevShotField.col; y = prevShotField.row + 1;
                if(y >= ui->spinBoxHeight->value()) y = prevShotField.row - 1;
                if(y < 0) y = prevShotField.row + 1;
                a = ui->table2->item(y, x); whatIn = a->text().toInt();
                if(whatIn > 1 && whatIn < 10) break;

                x = prevShotField.col; y = prevShotField.row - 1;
                if(y >= ui->spinBoxHeight->value()) y = prevShotField.row - 1;
                if(y < 0) y = prevShotField.row + 1;
                a = ui->table2->item(y, x); whatIn = a->text().toInt();
                if(whatIn > 1 && whatIn < 10) break;

                x = prevShotField.col + 1; y = prevShotField.row;
                if(x >= ui->spinBoxWidth->value()) x = prevShotField.col - 1;
                if(x < 0) x = prevShotField.col + 1;
                a = ui->table2->item(y, x); whatIn = a->text().toInt();
                if(whatIn > 1 && whatIn < 10) break;

                x = prevShotField.col - 1; y = prevShotField.row;
                if(x >= ui->spinBoxWidth->value()) x = prevShotField.col - 1;
                if(x < 0) x = prevShotField.col + 1;
                a = ui->table2->item(y, x); whatIn = a->text().toInt();
                if(whatIn > 1 && whatIn < 10) break;

                prevShotField.col = tempField.col;
                prevShotField.row = tempField.row;
            }

            temp.col = x;
            temp.row = y;

            return temp;
        }
    }
}





/* ------------ najlepsze wyniki ------------ */

void MainWindow::on_buttonBackToMenu_5_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->mainPage);


}

void MainWindow::on_pushButton_3_clicked()
{

    c1 = QColorDialog::getColor(Qt::red, this, "Wybierz kolor");
    if(c1.isValid())
    {
        QPalette pal = ui->shipsColor1->palette();
        pal.setColor(QPalette::Window, QColor(c1));
        ui->shipsColor1->setPalette(pal);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    c2 = QColorDialog::getColor(Qt::yellow, this, "Wybierz kolor");
    if(c1.isValid())
    {
        QPalette pal = ui->shipsColor2->palette();
        pal.setColor(QPalette::Window, QColor(c2));
        ui->shipsColor2->setPalette(pal);
    }
}




void MainWindow::on_pushButton_5_clicked()
{
    c3 = QColorDialog::getColor(Qt::green, this, "Wybierz kolor");
    if(c1.isValid())
    {
        QPalette pal = ui->shipsColor3->palette();
        pal.setColor(QPalette::Window, QColor(c3));
        ui->shipsColor3->setPalette(pal);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    c4 = QColorDialog::getColor(Qt::gray, this, "Wybierz kolor");
    if(c1.isValid())
    {
        QPalette pal = ui->shipsColor4->palette();
        pal.setColor(QPalette::Window, QColor(c4));
        ui->shipsColor4->setPalette(pal);
    }
}
