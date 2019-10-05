/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Koi-Koi Hanafuda - Card Game
 * Copyright (C) 2019  nightsky30 @ github
 */

#include "koikoi.h"
#include "preferences.h"
#include "about.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <iostream>
#include <chrono>  // Sleep Time
#include <thread>  //Thread Sleep
#include "ui_koikoi.h"
#include <QVector>
#include <QString>
#include <QPushButton>
#include <QIntegerForSize>
#include <QIcon>
#include <QThread>
#include <QPixmap>
#include <QTimer>

/*
 * Constructor
 */
KoiKoi::KoiKoi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KoiKoi)
{
    //Set up deck
    Deck m_gameDeck {Deck()};

    //Set up players and gameboard
    //Human
    Player m_player1 {Player()};
    //Comp
    Player m_player2 {Player()};
    //Game hand
    Hand m_gameHand {Hand()};
    //Oya Hand
    Hand m_oyaHand {Hand()};

    //Set game variables
    this->m_rounds = 12;
    this->m_currentRound = 0;
    this->m_gameStatus = false;

    ui->setupUi(this);

    //Title and Application Icon
    this->setWindowTitle("Koi-Koi Hanafuda");
    this->setWindowIcon(QIcon(QString(":/icon/koi-2.svg")));

    //Set up menus so they are connected with SIGNALS and SLOTS
    connect(ui->actionNew_Game, &QAction::triggered, this, &KoiKoi::onNewGameClicked, Qt::UniqueConnection);
    connect(ui->actionQuit_Game, &QAction::triggered, this, &KoiKoi::onQuitGameClicked, Qt::UniqueConnection);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close, Qt::UniqueConnection);
    connect(ui->actionPreferences, &QAction::triggered, this, &KoiKoi::onPreferencesClicked, Qt::UniqueConnection);
    connect(ui->actionAbout, &QAction::triggered, this, &KoiKoi::onAboutClicked, Qt::UniqueConnection);

    //Set up CPU game cards defaults in GUI
    for(int i{0};i<8;i++)
    {
        QString buttonName = "cpuButton_" + QString::number(i);
        QPushButton *button = new QPushButton(buttonName, this);
        button->setObjectName(buttonName);
        button->setMinimumSize(120,168);
        button->setMaximumSize(120,168);
        button->setText("");
        button->setIcon(QIcon(":/deck/Hanafuda_koi-2.svg"));
        button->setIconSize(QSize(120,168));
        button->setFlat(true);
        button->setEnabled(true);
        button->setVisible(true);
        button->show();
        ui->cpuHLayout->addWidget(button);
        this->guiCPUCards.push_back(button);
    }

    //Set up game board game cards defaults in GUI
    //Special ordering of cards to match 4 sets of 4
    for(int j{0};j<16;j++)
    {
        QString buttonName = "gameButton_" + QString::number(j);
        QPushButton *button = new QPushButton(buttonName, this);
        button->setObjectName(buttonName);
        button->setMinimumSize(120,168);
        button->setMaximumSize(120,168);
        button->setText("");
        button->setIcon(QIcon(":/deck/Hanafuda_koi-2.svg"));
        button->setIconSize(QSize(120,168));
        button->setFlat(true);
        button->setEnabled(true);
        button->setVisible(true);
        button->show();
        if (j<4)
        {
            switch(j)
            {
            case 0:
                ui->gameHandGridLayout_0->addWidget(button, 0, 0);
                break;
            case 1:
                ui->gameHandGridLayout_0->addWidget(button, 0, 1);
                break;
            case 2:
                ui->gameHandGridLayout_0->addWidget(button, 1, 0);
                break;
            case 3:
                ui->gameHandGridLayout_0->addWidget(button, 1, 1);
                break;
            }
        } else if (j >= 4 && j < 8)
        {
            switch(j)
            {
            case 4:
                ui->gameHandGridLayout_1->addWidget(button, 0, 0);
                break;
            case 5:
                ui->gameHandGridLayout_1->addWidget(button, 0, 1);
                break;
            case 6:
                ui->gameHandGridLayout_1->addWidget(button, 1, 0);
                break;
            case 7:
                ui->gameHandGridLayout_1->addWidget(button, 1, 1);
                break;
            }
        } else if (j >= 8 && j < 12)
        {
            switch(j)
            {
            case 8:
                ui->gameHandGridLayout_2->addWidget(button, 0, 0);
                break;
            case 9:
                ui->gameHandGridLayout_2->addWidget(button, 0, 1);
                break;
            case 10:
                ui->gameHandGridLayout_2->addWidget(button, 1, 0);
                break;
            case 11:
                ui->gameHandGridLayout_2->addWidget(button, 1, 1);
                break;
            }
        } else if (j >= 12 && j < 16)
        {
            switch(j)
            {
            case 12:
                ui->gameHandGridLayout_3->addWidget(button, 0, 0);
                break;
            case 13:
                ui->gameHandGridLayout_3->addWidget(button, 0, 1);
                break;
            case 14:
                ui->gameHandGridLayout_3->addWidget(button, 1, 0);
                break;
            case 15:
                ui->gameHandGridLayout_3->addWidget(button, 1, 1);
                break;
            }
        } else
        {
            std::cout << "Problem:  Too many cards on the gameboard." << std::endl;;
        }
        this->guiGameHandCards.append(button);
    }

    //Set up Player game cards defaults in GUI
    for(int k{0};k<8;k++)
    {
        QString buttonName = "playerButton_" + QString::number(k);
        QPushButton *button = new QPushButton(buttonName, this);
        button->setObjectName(buttonName);
        button->setMinimumSize(120,168);
        button->setMaximumSize(120,168);
        button->setText("");
        button->setIcon(QIcon(":/deck/Hanafuda_koi-2.svg"));
        button->setIconSize(QSize(120,168));
        button->setFlat(true);
        button->setEnabled(true);
        button->setVisible(true);
        button->show();
        ui->playerHLayout->addWidget(button);
        this->guiPlayerCards.push_back(button);
    }

    //Set up Player yaku cards defaults in GUI
    for(int i{0};i<5;i++)
    {
        QString yakuLabelName = "player_light_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->playerLightHLayout->addWidget(label);
        this->guiPlayerLightYaku.push_back(label);
    }

    for(int i{0};i<9;i++)
    {
        QString yakuLabelName = "player_animal_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->playerAnimalHLayout->addWidget(label);
        this->guiPlayerAnimalYaku.push_back(label);
    }

    for(int i{0};i<10;i++)
    {
        QString yakuLabelName = "player_ribbon_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->playerRibbonHLayout->addWidget(label);
        this->guiPlayerRibbonYaku.push_back(label);
    }

    for(int i{0};i<24;i++)
    {
        QString yakuLabelName = "player_plain_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->playerPlainHLayout->addWidget(label);
        this->guiPlayerPlainYaku.push_back(label);
    }

    //Set up CPU yaku cards defaults in GUI
    for(int i{0};i<5;i++)
    {
        QString yakuLabelName = "cpu_light_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->cpuLightHLayout->addWidget(label);
        this->guiCPULightYaku.push_back(label);
    }

    for(int i{0};i<9;i++)
    {
        QString yakuLabelName = "cpu_animal_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->cpuAnimalHLayout->addWidget(label);
        this->guiCPUAnimalYaku.push_back(label);
    }

    for(int i{0};i<10;i++)
    {
        QString yakuLabelName = "cpu_ribbon_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->cpuRibbonHLayout->addWidget(label);
        this->guiCPURibbonYaku.push_back(label);
    }

    for(int i{0};i<24;i++)
    {
        QString yakuLabelName = "cpu_plain_" + QString::number(i);
        QLabel *label = new QLabel(yakuLabelName, this);
        label->setObjectName(yakuLabelName);
        label->setMinimumSize(30,42);
        label->setMaximumSize(30,42);
        label->setText("");
        label->setPixmap(QPixmap(":/deck/Hanafuda_koi-2.svg"));
        label->setScaledContents(true);
        label->setVisible(false);
        ui->cpuPlainHLayout->addWidget(label);
        this->guiCPUPlainYaku.push_back(label);
    }

    //Set up SLOT/SIGNAL for oya selection
    connect(ui->oyaButton_0, SIGNAL (released()), this, SLOT(determineOyaPlayer()), Qt::UniqueConnection);
    connect(ui->oyaButton_1, SIGNAL (released()), this, SLOT(determineOyaPlayer()), Qt::UniqueConnection);

    //Set up SLOT/SIGNAL for koikoi selection
    connect(ui->yesButton, SIGNAL (released()), this, SLOT(requestKoiKoi()), Qt::UniqueConnection);
    connect(ui->noButton, SIGNAL (released()), this, SLOT(requestKoiKoi()), Qt::UniqueConnection);

    //Set up SLOT/SIGNAL for tally score screen
    connect(ui->newGameButton, SIGNAL (released()), this, SLOT(onNewGameClicked()), Qt::UniqueConnection);
    connect(ui->continueButton, SIGNAL (released()), this, SLOT(nextRound()), Qt::UniqueConnection);

    showTitleScreen();
}

/*
 * Default Destructor
 */
KoiKoi::~KoiKoi()
{
    delete ui;
}

/*
 * Returns a pointer to the game Deck.
 */
Deck* KoiKoi::getDeck()
{
    Deck *gameDeck;
    gameDeck = &m_gameDeck;
    return gameDeck;
}

/*
 * Returns a pointer to the Player requested.
 * Input specified by int value of either 1 or 2.
 */
Player* KoiKoi::getPlayer(int playerNum)
{
    Player *requestedPlayer;
    switch (playerNum)
    {
    case 1:
        requestedPlayer = &m_player1;
        return requestedPlayer;
    case 2:
        requestedPlayer = &m_player2;
        return requestedPlayer;
    default:
        std::cout << "Invalid player number. You must specify a value of 1 or 2. Returning player 1 by default." << std::endl;
        requestedPlayer = &m_player1;
        return requestedPlayer;
    }
}

/*
 * Returns a pointer to the game Hand.
 */
Hand* KoiKoi::getGameHand()
{
    Hand *gameHand;
    gameHand = &m_gameHand;
    return gameHand;
}

/*
 * Returns the number of game rounds as an integer.
 */
int KoiKoi::getNumRounds()
{
    return m_rounds;
}

/*
 * Returns the current round as an integer.
 */
int KoiKoi::getCurrentRound()
{
    return m_currentRound;
}

/*
 * Returns the game status as a boolean.
 * True indicates an ongoing game.
 * False indicated the game is complete.
 */
bool KoiKoi::getGameStatus()
{
    return m_gameStatus;
}

/*
 * Starts a new game.
 * Must reset deck, hands, yaku, etc.
 */
void KoiKoi::startGame()
{
    this->m_currentRound = 0;
    this->m_gameStatus = false;
    this->m_gameDeck.resetDeck();
    this->m_gameDeck.shuffleDeck();
    this->m_gameHand.resetHand();
    this->m_oyaHand.resetHand();
    this->m_player1.getHand()->resetHand();
    this->m_player2.getHand()->resetHand();
    this->m_player1.setScore(30);
    this->m_player2.setScore(30);
    resetYaku();
    resetTally();
    generateOyaCard();
}

/*
 * Generates a random 2 card hand used by players to determine
 * who is the oya player which takes the first turn.  It then compares
 * card months.  The earlier card is the oya card.
 * It sets the variable within the hand to indicate
 * which card is the oya card.
 */
void KoiKoi::generateOyaCard()
{
    //Not removed from deck because they are only used to determine dealer
    m_oyaHand.acceptCard(*m_gameDeck.getRandCard());
    m_oyaHand.acceptCard(*m_gameDeck.getRandCard());

    Card* oyaCard1;
    oyaCard1 = m_oyaHand.getCard(0);

    Card* oyaCard2;
    oyaCard2 = m_oyaHand.getCard(1);

    int month1 = oyaCard1->getMonth();
    int month2 = oyaCard2->getMonth();

    //Ensure months are different to avoid issues
    if (month1 == month2)
    {
        while (month1 == month2)
        {
            m_oyaHand.removeCard(1);
            m_oyaHand.acceptCard(*m_gameDeck.getRandCard());
            oyaCard2 = m_oyaHand.getCard(1);
            month2 = oyaCard2->getMonth();
        }
    }

    //Determine Oya card and set value in hand
    if (month1 < month2)
    {
        m_oyaHand.setOyaCard(0);
    }
    else
    {
        m_oyaHand.setOyaCard(1);
    }

    //***************************************
    //Display cards here
    //Wait for player to select cards
    //***************************************
    showOyaScreen();
}

/*
 * Deals hands for both players as well as the gameboard.
 */
void KoiKoi::deal()
{
    int fourCount {0};

    Hand *playHand1 = m_player1.getHand();  // Had to use pointers
    Hand *playHand2 = m_player2.getHand();
    //Already have access to game hand

    //2 rounds of dealing 4 cards to each hand in sequential order
    for (fourCount = 0; fourCount < 2; fourCount++)
    {
        for (int i {0}; i < 3; i++)
        {
            for(int j {0}; j < 4; j++)
            {
                switch (i)
                {
                case 0:
                    playHand1->acceptCard(*m_gameDeck.dealCard());  // -> used when accessing members with a pointer (playerHand1), but use . with m_gameDeck
                    break;
                case 1:
                    playHand2->acceptCard(*m_gameDeck.dealCard());
                    break;
                case 2:
                    m_gameHand.acceptCard(*m_gameDeck.dealCard());
                    break;
                }
            }
        }
    }
}

/*
 * Starts a round.
 */
void KoiKoi::startRound()
{
    if(this->m_currentRound < m_rounds)
    {
        //start round
        this->m_currentRound = this->m_currentRound + 1;
        this->m_gameStatus = true;

        this->m_gameDeck.resetDeck();
        this->m_gameDeck.shuffleDeck();
        this->m_gameHand.resetHand();
        this->m_player1.getHand()->resetHand();
        this->m_player2.getHand()->resetHand();
        resetYaku();
        resetTally();

        deal();
        updateYaku();
        updateCards();
        updateScores();
        showGameScreen();

        if(m_player1.getOya() == true)
        {
            //player is oya
            connectPlayerHand();
            disconnectGameHand();
            disconnectDeck();

            //Make sure at end of player's turn when drawing card and
            //possibly matching with game hand to kick off next cpu turn...
        }
        else
        {
            //cpu is oya
            disconnectPlayerHand();
            disconnectGameHand();
            disconnectDeck();

            //call cpu/ai functions to facilitate cpu turns
            //At end of cpu turn, make sure stage is set for player...
            cpuSelectFromHand();
        }
    }
    else
    {
        //end game
        this->m_gameStatus = false;
        tallyPoints();
    }
}

/*
 * Tally the points for each player at the end of the round.
 */
void KoiKoi::tallyPoints()
{
    ui->roundLabel->setText(QString("Round:  %1").arg(m_currentRound));  //Using .arg() with argument substitution to convert/append integer to part of a QString

    //Tally points
    //Take into account player koikoi statuses
    //Players can have multiple koikois and if one player gets one after another
    //had declared it, then the other player gets no points

    //bool playerKoiKoi = m_player1.getKoikoi();
    //bool cpuKoiKoi = m_player2.getKoikoi();

    int playerSubTotal {0};
    int cpuSubTotal {0};

    //m_player1.printYaku();
    //m_player2.printYaku();

    for (int i {0}; i < m_player1.getYakuSize();i++)
    {
        if(m_player1.getYaku(i) == true)
        {
            playerSubTotal = playerSubTotal + acceptableYaku[i].getPointValue();
            m_player1.setScore(m_player1.getScore() + acceptableYaku[i].getPointValue());
            switch (i)
            {
            case 0:
                ui->tally_kasu_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 1:
                //Not used
                break;
            case 2:
                //Not used
                break;
            case 3:
                //Not used
                break;
            case 4:
                ui->tally_tane_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 5:
                ui->tally_inoshikacho_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 6:
                ui->tally_tanzaku_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 7:
                ui->tally_akatan_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 8:
                ui->tally_aotan_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 9:
                ui->tally_akatanaotannochofuku_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 10:
                ui->tally_tsukimideippai_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 11:
                ui->tally_hanamideippai_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 12:
                ui->tally_sanko_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 13:
                ui->tally_ameshiko_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 14:
                ui->tally_shiko_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            case 15:
                ui->tally_goku_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                break;
            default:
                break;
            }
        }
    }

    for (int j {0}; j < m_player2.getYakuSize();j++)
    {
        if(m_player2.getYaku(j) == true)
        {
            cpuSubTotal = cpuSubTotal + acceptableYaku[j].getPointValue();
            m_player2.setScore(m_player2.getScore() + acceptableYaku[j].getPointValue());
            switch (j)
            {
            case 0:
                ui->tally_kasu_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 1:
                //Not used
                break;
            case 2:
                //Not used
                break;
            case 3:
                //Not used
                break;
            case 4:
                ui->tally_tane_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 5:
                ui->tally_inoshikacho_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 6:
                ui->tally_tanzaku_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 7:
                ui->tally_akatan_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 8:
                ui->tally_aotan_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 9:
                ui->tally_akatanaotannochofuku_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 10:
                ui->tally_tsukimideippai_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 11:
                ui->tally_hanamideippai_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 12:
                ui->tally_sanko_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 13:
                ui->tally_ameshiko_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 14:
                ui->tally_shiko_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            case 15:
                ui->tally_goku_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                break;
            default:
                break;
            }
        }
    }

    //Revisit this as koi-koi may cause negative points
    ui->tally_subtotal_player_points->setText(QString("%1").arg(playerSubTotal));
    ui->tally_subtotal_cpu_points->setText(QString("%1").arg(cpuSubTotal));

    ui->tally_total_player_points->setText(QString("%1").arg(m_player1.getScore()));
    ui->tally_total_cpu_points->setText(QString("%1").arg(m_player2.getScore()));



    //Show Tally Points frame/screen
    showTallyScreen();
    if(m_currentRound == 12 || m_player1.getScore() >= 60 || m_player2.getScore() >= 60)
    {
        //End game
        //Display label that asks to "Play again?"
        ui->playAgainLabel->setVisible(true);
        //Display New Game button
        ui->newGameButton->setVisible(true);
        //Hide continue button
        ui->continueButton->setVisible(false);
    }
    else
    {
        //Continue game
        //Set oya for next round
        if (playerSubTotal >= cpuSubTotal)
        {
            //Human has Oya
            m_player1.setOya(true);
            m_player2.setOya(false);
            std::cout << "player is oya!" << std::endl;
        }
        else
        {
            //CPU has Oya
            m_player1.setOya(false);
            m_player2.setOya(true);
            std::cout << "cpu is oya!" << std::endl;
        }

        //Hide label that asks to "Play again?"
        ui->playAgainLabel->setVisible(false);
        //Hide New Game button
        ui->newGameButton->setVisible(false);
        //Display continue button
        ui->continueButton->setVisible(true);
        //Wait for player to click contine button which should call startRound();
    }
}

/*
 * Prints the number of rounds to the console.
 */
void KoiKoi::printNumRounds()
{
    std::cout << "The number of rounds set for the current game are: " << m_rounds << std::endl;
}

/*
 * Prints the current round to the console.
 */
void KoiKoi::printCurrentRound()
{
    std::cout << "The current round is: " << m_currentRound << std::endl;
}

/*
 * Prints the current game status to the console.
 */
void KoiKoi::printGameStatus()
{
    std::cout << "The game's current status is: " << m_gameStatus << std::endl;
}

/*
 * Displays the title screen within the GUI.
 */
void KoiKoi::showTitleScreen()
{
    ui->titleFrame->show();
    ui->gameFrame->setHidden(true);
    ui->oyaFrame->setHidden(true);
    ui->koikoiFrame->setHidden(true);
    ui->tallyFrame->setHidden(true);
}

/*
 * Displays the game screen within the GUI.
 */
void KoiKoi::showGameScreen()
{
    ui->titleFrame->setHidden(true);
    ui->gameFrame->show();
    ui->oyaFrame->setHidden(true);
    ui->koikoiFrame->setHidden(true);
    ui->tallyFrame->setHidden(true);
}

/*
 * Displays the oya selection screen within the GUI.
 */
void KoiKoi::showOyaScreen()
{
    ui->titleFrame->setHidden(true);
    ui->gameFrame->setHidden(true);
    ui->oyaFrame->show();
    ui->koikoiFrame->setHidden(true);
    ui->tallyFrame->setHidden(true);
}

/*
 * Displays the Koi-Koi selection screen within the GUI.
 */
void KoiKoi::showKoiKoiScreen()
{
    ui->titleFrame->setHidden(true);
    ui->gameFrame->setHidden(true);
    ui->oyaFrame->setHidden(true);
    ui->koikoiFrame->show();
    ui->tallyFrame->setHidden(true);
}

/*
 * Displays the Tally score screen within the GUI.
 */
void KoiKoi::showTallyScreen()
{
    ui->titleFrame->setHidden(true);
    ui->gameFrame->setHidden(true);
    ui->oyaFrame->setHidden(true);
    ui->koikoiFrame->setHidden(true);
    ui->tallyFrame->show();
}

/*
 * Updates and shows all dealt cards (not CPU).
 *
 * Set unused cards in the GUI as invisible, default deck style.
 * Or if the cards are currently being used, ensures they are
 * visible within the GUI, and updates the images.
 *
 * This is kept separate from connections and disconnections
 */
void KoiKoi::updateCards()
{
    Hand *playerHand = m_player1.getHand();
    Hand *cpuHand = m_player2.getHand();
    //Already have gameHand
    //Already have deck

    //Set used/unused cards in the GUI
    for(int i{0};i<guiCPUCards.size();i++)
    {
        QPushButton *button = guiCPUCards.at(i);
        if(cpuHand->getNumCards() == 0)
        {
            button->setEnabled(false);
            button->setVisible(false);
        }
        else
        {
            if (i>cpuHand->getNumCards()-1)
            {
                button->setEnabled(false);
                button->setVisible(false);
            }
            else {
                button->setEnabled(true);
                button->setVisible(true);
            }
        }
    }

    for(int j{0};j<guiGameHandCards.size();j++)
    {
        QPushButton *button = guiGameHandCards.at(j);
        if (j>m_gameHand.getNumCards()-1)
        {
            button->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
            button->setEnabled(false);
            button->setVisible(false);
        }
        else
        {
            button->setIcon(QIcon(m_gameHand.getCard(j)->getImageStr()));
            button->setEnabled(true);
            button->setVisible(true);
        }
    }

    for(int k{0};k<guiPlayerCards.size();k++)
    {
        QPushButton *button = guiPlayerCards.at(k);
        if(playerHand->getNumCards() == 0)
        {
            button->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
            button->setEnabled(false);
            button->setVisible(false);
        }
        else
        {
            if (k>playerHand->getNumCards()-1)
            {
                button->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
                button->setEnabled(false);
                button->setVisible(false);
            }
            else
            {
                button->setIcon(QIcon(playerHand->getCard(k)->getImageStr()));
                button->setEnabled(true);
                button->setVisible(true);
            }
        }
    }
}

/*
 * Updates the scores for all players on the gameboard GUI.
 * This is called at the start of each round.
 */
void KoiKoi::updateScores()
{
    ui->cpuScore->setText(QString("CPU:  %1").arg(m_player2.getScore()));
    ui->playerScore->setText(QString("Player:  %1").arg(m_player1.getScore()));
}

/*
 * Resets yaku status for all players both at the
 * variable level as well as visual status within the GUI.
 */
void KoiKoi::resetYaku()
{
    this->m_player1.getLightMatch()->resetHand();
    this->m_player1.getAnimalMatch()->resetHand();
    this->m_player1.getRibbonMatch()->resetHand();
    this->m_player1.getPlainMatch()->resetHand();
    this->m_player2.getLightMatch()->resetHand();
    this->m_player2.getAnimalMatch()->resetHand();
    this->m_player2.getRibbonMatch()->resetHand();
    this->m_player2.getPlainMatch()->resetHand();

    this->m_player1.resetYaku();
    this->m_player2.resetYaku();

    //Set player yaku labels invisible
    ui->player_ameshiko_yaku->setVisible(false);
    ui->player_goku_yaku->setVisible(false);
    ui->player_sanko_yaku->setVisible(false);
    ui->player_shiko_yaku->setVisible(false);
    ui->player_hanami_de_ippai_yaku->setVisible(false);
    ui->player_tsukimi_de_ippai_yaku->setVisible(false);
    ui->player_inoshikacho_yaku->setVisible(false);
    ui->player_tane_yaku->setVisible(false);
    ui->player_akatan_yaku->setVisible(false);
    ui->player_aotan_yaku->setVisible(false);
    ui->player_akatan_aotan_no_chofuku_yaku->setVisible(false);
    ui->player_tanzaku_yaku->setVisible(false);
    ui->player_bake_fuda_yaku->setVisible(false);
    ui->player_kasu_yaku->setVisible(false);
    ui->player_oya_ken_yaku->setVisible(false);
    ui->player_tsuki_fuda_yaku->setVisible(false);

    //Set cpu yaku labels invisible
    ui->cpu_ameshiko_yaku->setVisible(false);
    ui->cpu_goku_yaku->setVisible(false);
    ui->cpu_sanko_yaku->setVisible(false);
    ui->cpu_shiko_yaku->setVisible(false);
    ui->cpu_hanami_de_ippai_yaku->setVisible(false);
    ui->cpu_tsukimi_de_ippai_yaku->setVisible(false);
    ui->cpu_inoshikacho_yaku->setVisible(false);
    ui->cpu_tane_yaku->setVisible(false);
    ui->cpu_akatan_yaku->setVisible(false);
    ui->cpu_aotan_yaku->setVisible(false);
    ui->cpu_akatan_aotan_no_chofuku_yaku->setVisible(false);
    ui->cpu_tanzaku_yaku->setVisible(false);
    ui->cpu_bake_fuda_yaku->setVisible(false);
    ui->cpu_kasu_yaku->setVisible(false);
    ui->cpu_oya_ken_yaku->setVisible(false);
    ui->cpu_tsuki_fuda_yaku->setVisible(false);
}

/*
 * Resets the yaku point indicators for all players on the tally screen.
 * This is called at the start of each round.
 */
void KoiKoi::resetTally()
{
    ui->tally_kasu_player_points->setText(QString("%1").arg(0));
    ui->tally_tane_player_points->setText(QString("%1").arg(0));
    ui->tally_inoshikacho_player_points->setText(QString("%1").arg(0));
    ui->tally_tanzaku_player_points->setText(QString("%1").arg(0));
    ui->tally_akatan_player_points->setText(QString("%1").arg(0));
    ui->tally_aotan_player_points->setText(QString("%1").arg(0));
    ui->tally_akatanaotannochofuku_player_points->setText(QString("%1").arg(0));
    ui->tally_tsukimideippai_player_points->setText(QString("%1").arg(0));
    ui->tally_hanamideippai_player_points->setText(QString("%1").arg(0));
    ui->tally_sanko_player_points->setText(QString("%1").arg(0));
    ui->tally_ameshiko_player_points->setText(QString("%1").arg(0));
    ui->tally_shiko_player_points->setText(QString("%1").arg(0));
    ui->tally_goku_player_points->setText(QString("%1").arg(0));
    ui->tally_subtotal_player_points->setText(QString("%1").arg(0));
    ui->tally_total_player_points->setText(QString("%1").arg(0));

    ui->tally_kasu_cpu_points->setText(QString("%1").arg(0));
    ui->tally_tane_cpu_points->setText(QString("%1").arg(0));
    ui->tally_inoshikacho_cpu_points->setText(QString("%1").arg(0));
    ui->tally_tanzaku_cpu_points->setText(QString("%1").arg(0));
    ui->tally_akatan_cpu_points->setText(QString("%1").arg(0));
    ui->tally_aotan_cpu_points->setText(QString("%1").arg(0));
    ui->tally_akatanaotannochofuku_cpu_points->setText(QString("%1").arg(0));
    ui->tally_tsukimideippai_cpu_points->setText(QString("%1").arg(0));
    ui->tally_hanamideippai_cpu_points->setText(QString("%1").arg(0));
    ui->tally_sanko_cpu_points->setText(QString("%1").arg(0));
    ui->tally_ameshiko_cpu_points->setText(QString("%1").arg(0));
    ui->tally_shiko_cpu_points->setText(QString("%1").arg(0));
    ui->tally_goku_cpu_points->setText(QString("%1").arg(0));
    ui->tally_subtotal_cpu_points->setText(QString("%1").arg(0));
    ui->tally_total_cpu_points->setText(QString("%1").arg(0));
}

/*
 * Updates yaku status for all players both at the
 * variable level as well as visual status within the GUI.
 */
void KoiKoi::updateYaku()
{
    Hand *playerLightHand = m_player1.getLightMatch();
    Hand *playerAnimalHand = m_player1.getAnimalMatch();
    Hand *playerRibbonHand = m_player1.getRibbonMatch();
    Hand *playerPlainHand = m_player1.getPlainMatch();

    Hand *cpuLightHand = m_player2.getLightMatch();
    Hand *cpuAnimalHand = m_player2.getAnimalMatch();
    Hand *cpuRibbonHand = m_player2.getRibbonMatch();
    Hand *cpuPlainHand = m_player2.getPlainMatch();

    /*
     * If the number of cards in each yaku GUI QVector exceed
     * the number in each yaku hand, then set the default card
     * image and hide.
     */
    for(int i{0};i<guiPlayerLightYaku.size();i++)
    {
        QLabel *label = guiPlayerLightYaku.at(i);
        if (i>=playerLightHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(playerLightHand->getCard(i)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int j{0};j<guiPlayerAnimalYaku.size();j++)
    {
        QLabel *label = guiPlayerAnimalYaku.at(j);
        if (j>=playerAnimalHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(playerAnimalHand->getCard(j)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int k{0};k<guiPlayerRibbonYaku.size();k++)
    {
        QLabel *label = guiPlayerRibbonYaku.at(k);
        if (k>=playerRibbonHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(playerRibbonHand->getCard(k)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int l{0};l<guiPlayerPlainYaku.size();l++)
    {
        QLabel *label = guiPlayerPlainYaku.at(l);
        if (l>=playerPlainHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(playerPlainHand->getCard(l)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int m{0};m<guiCPULightYaku.size();m++)
    {
        QLabel *label = guiCPULightYaku.at(m);
        if (m>=cpuLightHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(cpuLightHand->getCard(m)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int n{0};n<guiCPUAnimalYaku.size();n++)
    {
        QLabel *label = guiCPUAnimalYaku.at(n);
        if (n>=cpuAnimalHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(cpuAnimalHand->getCard(n)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int p{0};p<guiCPURibbonYaku.size();p++)
    {
        QLabel *label = guiCPURibbonYaku.at(p);
        if (p>=cpuRibbonHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(cpuRibbonHand->getCard(p)->getImageStr()));
            label->setVisible(true);
        }
    }

    for(int q{0};q<guiCPUPlainYaku.size();q++)
    {
        QLabel *label = guiCPUPlainYaku.at(q);
        if (q>=cpuPlainHand->getNumCards())
        {
            label->setPixmap(QString(":/deck/Hanafuda_koi-2.svg"));
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(cpuPlainHand->getCard(q)->getImageStr()));
            label->setVisible(true);
        }
    }
}

void KoiKoi::checkYaku()
{
    Hand *playerLightHand = m_player1.getLightMatch();
    Hand *playerAnimalHand = m_player1.getAnimalMatch();
    Hand *playerRibbonHand = m_player1.getRibbonMatch();
    Hand *playerPlainHand = m_player1.getPlainMatch();

    //    Hand *cpuLightHand = m_player2.getLightMatch();
    //    Hand *cpuAnimalHand = m_player2.getAnimalMatch();
    //    Hand *cpuRibbonHand = m_player2.getRibbonMatch();
    //    Hand *cpuPlainHand = m_player2.getPlainMatch();

    bool obtainedYaku {false};

    /*
     * Add yaku to player via bool vector.
     * List as acquired in GUI.
     *
     * The following Yaku have not been implemented code-wise:
     *
     * 1 Yaku(1, "Bake-Fuda (Wild Card)", "The animal card of Chrysanthemum can be regarded as a plain card as well. If you have this, 9 plain cards and this card will be the Yaku of Kasu."),
     * 2 Yaku(4, "Tsuki-fuda (Monthly Cards)", "All four cards in one group shown right on screen. 4 points."),
     * 3 Yaku(6, "Oya-Ken (Dealer's Privilege)", "If neither gets any Yaku, Dealer wins 6 points."),
     */

    //Sanko, 5pts
    //Shiko, without Rain, 8pts
    //Ame Shiko, with rain, 7pts
    //Goku, 10pts
    bool foundRain {false};
    switch (playerLightHand->getNumCards())
    {
    case 3:
        if(m_player1.getYaku(12) != true)
        {
            //Sanko, 5pts
            m_player1.setYaku(12, true);
            ui->player_sanko_yaku->setVisible(true);
            obtainedYaku = true;
        }
        break;
    case 4:
        //Shiko, without Rain, 8pts
        //Ame Shiko, with rain, 7pts
        for (int i {0};i<playerLightHand->getNumCards();i++)
        {
            switch (playerLightHand->getCard(i)->getCardType2())
            {
            case RAIN:
                foundRain = true;
                break;
            default:
                break;
            }
        }
        if(foundRain == true)
        {
            if(m_player1.getYaku(13) != true)
            {
                m_player1.setYaku(13, true);
                ui->player_ameshiko_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        else
        {
            if(m_player1.getYaku(14) != true)
            {
                m_player1.setYaku(14, true);
                ui->player_shiko_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        break;
    case 5:
        if(m_player1.getYaku(15) != true)
        {
            //Goku, 10pts
            m_player1.setYaku(15, true);
            ui->player_goku_yaku->setVisible(true);
            obtainedYaku = true;
        }
        break;
    default:
        break;
    }

    //Sake Cup is in animal hand...
    //Tsukimi De Ippai, 5 Pts
    //Hanami De Ippai, 5 Pts
    for (int i {0};i<playerLightHand->getNumCards();i++)
    {
        switch (playerLightHand->getCard(i)->getCardType2())
        {
        case MOON:
            for(int j {0};j<playerAnimalHand->getNumCards();j++)
            {
                if (playerAnimalHand->getCard(j)->getCardType2() == SAKE_CUP)
                {
                    if(m_player1.getYaku(10) != true)
                    {
                        m_player1.setYaku(10, true);
                        ui->player_tsukimi_de_ippai_yaku->setVisible(true);
                        obtainedYaku = true;
                    }
                }
            }
            break;
        case CURTAIN:
            for(int j {0};j<playerAnimalHand->getNumCards();j++)
            {
                if (playerAnimalHand->getCard(j)->getCardType2() == SAKE_CUP)
                {
                    if(m_player1.getYaku(11) != true)
                    {
                        m_player1.setYaku(11, true);
                        ui->player_hanami_de_ippai_yaku->setVisible(true);
                        obtainedYaku = true;
                    }
                }
            }
            break;
        default:
            break;
        }
    }

    //Tane, 1pt
    if (playerAnimalHand->getNumCards() >= 5)
    {
        if(m_player1.getYaku(4) != true)
        {
            m_player1.setYaku(4, true);
            ui->player_tane_yaku->setVisible(true);
            obtainedYaku = true;
        }
    }

    //Inoshikacho, 5pts
    if (playerAnimalHand->getNumCards() >= 3)
    {
        for(int i{0};i<playerAnimalHand->getNumCards();i++)
        {
            if(playerAnimalHand->getCard(i)->getCardType2() == BOAR)
            {
                for(int j{0};j<playerAnimalHand->getNumCards();j++)
                {
                    if(playerAnimalHand->getCard(j)->getCardType2() == DEER)
                    {
                        for(int k{0};k<playerAnimalHand->getNumCards();k++)
                        {
                            if(playerAnimalHand->getCard(k)->getCardType2() == BUTTERFLIES)
                            {
                                if(m_player1.getYaku(5) != true)
                                {
                                    m_player1.setYaku(5, true);
                                    ui->player_inoshikacho_yaku->setVisible(true);
                                    obtainedYaku = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int numRedPoems {0};
    int numBlueRibbons {0};

    //Akatan, 5pts
    //Aotan, 5pts
    //Akatan Aotan No Chofuku, 10pts
    if(playerRibbonHand->getNumCards() >= 3)
    {
        for (int i {0};i<playerRibbonHand->getNumCards();i++)
        {
            switch (playerRibbonHand->getCard(i)->getCardType2())
            {
            case RED_POEM:
                numRedPoems++;
                break;
            case BLUE_RIBBON:
                numBlueRibbons++;
                break;
            default:
                break;
            }
        }
        //Akatan, 5pts
        if(numRedPoems >= 3)
        {
            if(m_player1.getYaku(7) != true)
            {
                m_player1.setYaku(7, true);
                ui->player_akatan_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        //Aotan, 5pts
        if(numBlueRibbons >= 3)
        {
            if(m_player1.getYaku(8) != true)
            {
                m_player1.setYaku(8, true);
                ui->player_aotan_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        //Akatan Aotan No Chofuku, 10pts
        if(numRedPoems >= 3 && numBlueRibbons >= 3)
        {
            if(m_player1.getYaku(9) != true)
            {
                m_player1.setYaku(9, true);
                ui->player_akatan_aotan_no_chofuku_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
    }

    //Tanzaku, 1pt
    if(playerRibbonHand->getNumCards() >= 5)
    {
        if(m_player1.getYaku(6) != true)
        {
            m_player1.setYaku(6, true);
            ui->player_tanzaku_yaku->setVisible(true);
            obtainedYaku = true;
        }
    }

    //Kasu, 1pt
    if (playerPlainHand->getNumCards() >=10)
    {
        if(m_player1.getYaku(0) != true)
        {
            m_player1.setYaku(0, true);
            ui->player_kasu_yaku->setVisible(true);
            obtainedYaku = true;
        }
    }

    if(obtainedYaku == true)
    {
        //Call function to ask if player wants to declare koikoi
        showKoiKoiScreen();
    }
}

/*
 * Connects the SIGNAL/SLOT for the game deck card button in the GUI so players may draw cards.
 */
void KoiKoi::connectDeck()
{
    connect(ui->deckButton, SIGNAL(released()), this, SLOT(drawCard()), Qt::UniqueConnection);
}

/*
 * Connects the SIGNAL/SLOT for individual card buttons in the GUI for the game board
 * hand so players may select cards to match.
 */
void KoiKoi::connectGameHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    connect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()), Qt::UniqueConnection);
}

/*
 * Connects the SIGNAL/SLOT for all card buttons in the GUI for the game board
 * hand if they have corresponding game hand cards.  This is so players
 * may select cards to match.
 */
void KoiKoi::connectGameHand()
{
    for(int j{0};j<guiGameHandCards.size();j++)
    {
        QPushButton *currentButton = guiGameHandCards.at(j);
        if (j>m_gameHand.getNumCards()-1)
        {
            //Not used
            disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()));
        }
        else
        {
            connect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()), Qt::UniqueConnection);
        }
    }
}

/*
 * Connects the SIGNAL/SLOT for individual card buttons in the GUI for the player
 * hand so players may select cards to match.
 */
void KoiKoi::connectPlayerHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    connect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()), Qt::UniqueConnection);
}

/*
 * Connects the SIGNAL/SLOT for all card buttons in the GUI for the player
 * hand if they have corresponding player hand cards.  This is so players
 * may select cards to match.
 */
void KoiKoi::connectPlayerHand()
{
    Hand *playerHand = m_player1.getHand();

    for(int k{0};k<guiPlayerCards.size();k++)
    {
        QPushButton *currentButton = guiPlayerCards.at(k);
        if (k>playerHand->getNumCards()-1)
        {
            //Not used
            disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()));
        }
        else
        {
            connect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()), Qt::UniqueConnection);
        }
    }
}

/*
 * Disconnects the SIGNAL/SLOT for the game deck card button in the GUI so players may NOT draw cards.
 */
void KoiKoi::disconnectDeck()
{
    disconnect(ui->deckButton, SIGNAL(released()), this, SLOT(drawCard()));
}

/*
 * Disconnects the SIGNAL/SLOT for individual card buttons in the GUI for the game board
 * hand so players may NOT select cards to match.
 */
void KoiKoi::disconnectGameHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()));
}

/*
 * Disconnects the SIGNAL/SLOT for all card buttons in the GUI for the game board
 * hand if they have corresponding game hand cards.  This is so players
 * may NOT select cards to match.
 */
void KoiKoi::disconnectGameHand()
{
    for(int j{0};j<guiGameHandCards.size();j++)
    {
        QPushButton *currentButton = guiGameHandCards.at(j);
        disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()));
    }
}

/*
 * Disconnects the SIGNAL/SLOT for individual card buttons in the GUI for the player
 * hand so players may NOT select cards to match.
 */
void KoiKoi::disconnectPlayerHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()));
}

/*
 * Disconnects the SIGNAL/SLOT for all card buttons in the GUI for the player
 * hand if they have corresponding player hand cards.  This is so players
 * may NOT select cards to match.
 */
void KoiKoi::disconnectPlayerHand()
{
    for(int k{0};k<guiPlayerCards.size();k++)
    {
        QPushButton *currentButton = guiPlayerCards.at(k);
        disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()));
    }
}

/*
 * Slot function for the menu item which calls the
 * function to start a new game.
 */
void KoiKoi::onNewGameClicked()
{
    //Create game
    startGame();
}

/*
 * Slot function for the menu item which calls the
 * function to quit the current game.
 */
void KoiKoi::onQuitGameClicked()
{
    //Quit Game
    showTitleScreen();
}

/*
 * Slot function for the menu item which calls the
 * function to open the preferences dialog.
 */
void KoiKoi::onPreferencesClicked()
{
    //Open preferences dialog
    Preferences *prefs = new Preferences();
    prefs->setAttribute(Qt::WA_DeleteOnClose);
    prefs->show();
}

/*
 * Slot function for the menu item which calls the
 * function to open the about dialog.
 */
void KoiKoi::onAboutClicked()
{
    //Open about dialog
    About *about = new About();
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->show();
}

/*
 * Slot function for the oya card buttons in the GUI which
 * determine the oya player based on the player's card selection.
 * It then calls the function to start the initial round.
 */
void KoiKoi::determineOyaPlayer()
{
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();

    int oyaCard = m_oyaHand.getOyaCard();
    QChar buttonNum = (buttonName.at(buttonName.size()-1));

    //Compare selected sender object card with predetermined oya
    if (buttonNum.digitValue() == (int)oyaCard)
    {
        //Human has Oya
        m_player1.setOya(true);
        m_player2.setOya(false);
        std::cout << "player is oya!" << std::endl;
    }
    else
    {
        //CPU has Oya
        m_player1.setOya(false);
        m_player2.setOya(true);
        std::cout << "cpu is oya!" << std::endl;
    }
    startRound();
}

/*
 * Slot function for the player hand card buttons in the GUI which
 * determine the player's card selection.
 * It then determines if there are matching cards in the game hand
 * on the game board.  If there are matches it will enable them and
 * connect the buttons allowing the player to then select a matching
 * card from the game board.  If there aren't matches, then it will
 * discard the player's selected card, and allow the player to draw
 * a card from the deck.
 */
void KoiKoi::selectFromHand()
{
    Hand *playerHand = m_player1.getHand();

    //get calling parent object name
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();

    //disconnect all playerhand cards
    disconnectPlayerHand();

    //Get card number
    int cardNum = buttonName.at(buttonName.size()-1).digitValue();
    //Get player card
    Card *currentPlayerCard = playerHand->getCard(cardNum);

    //get month of card button
    CardMonth currentCardMonth = currentPlayerCard->getMonth();

    bool matchingCard {false};

    //compare with gameHand objects
    for(int i{0};i<m_gameHand.getNumCards();i++)
    {
        if (m_gameHand.getCard(i)->getMonth() != currentCardMonth)
        {
            //Disable gamehand card
            guiGameHandCards[i]->setDisabled(true);
        }
        else
        {
            matchingCard = true;
            //connect the matching game hand cards
            connectGameHand(guiGameHandCards[i]);
        }
    }
    //See if there are any month matches
    if(matchingCard == false)
    {
        //discard selected card from playerhand
        //accept in gamehand
        m_gameHand.acceptCard(*playerHand->getCard(cardNum));
        playerHand->removeCard(cardNum);

        //disconnect all game hand cards
        disconnectGameHand();
        //Connect deck
        connectDeck();
        //call updateCards
        updateCards();
        //***************************************
        //allows to click deck to call drawCard
        //***************************************
    }
    else
    {
        //Disable all cards in playerhand except current selected card
        for(int k {0};k<playerHand->getNumCards();k++)
        {
            if(k != cardNum)
            {
                guiPlayerCards[k]->setDisabled(true);
            }
        }
        //**********************************************************
        //allows to click game hand card to call selectFromGameHand
        //**********************************************************
        //Wait for user to select from gamehand as there may have been multiple match possibilities
    }
}

/*
 * Slot function for the game hand card buttons in the GUI which
 * determine the player's card selection.
 * It then determines if there are matching cards in the player hand
 * or deck.  If there are matches it will move the cards to the
 * appropriate yaku hands.
 *
 * This function helps maintain turn flow with connections and
 * disconnections from various buttons in the GUI under certain
 * circumstances.
 */
void KoiKoi::selectFromGameHand()
{
    /*
     * Could match from deck or player hand.
     * Check both.
     */
    //get calling parent object name
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();

    //disconnect all game hand cards
    disconnectGameHand();

    //Already have gameHand
    //Get card number
    int cardNum = buttonName.at(buttonName.size()-1).digitValue();
    //Get game hand card
    Card *currentGameCard = m_gameHand.getCard(cardNum);
    //get month of card button
    CardMonth currentCardMonth = currentGameCard->getMonth();

    /*
     * If the deck was recently clicked and there was a match
     * then there should be an icon of the next card image.
     * Otherwise it should just be the normal deck image
     * indicating the check should be made with the player's hand.
     *
     * Perhaps in the future with turn based stuff, pass in
     * the player, and some sort of turn state variable
     */
    if(m_gameDeck.getDeckIcon() != ":/deck/Hanafuda_koi-2.svg")
    {
        //Get next card
        Card *nextCard = m_gameDeck.getCard(m_gameDeck.getNumCards()-1);
        //Get next card month
        CardMonth nextCardMonth = nextCard->getMonth();
        if(currentCardMonth != nextCardMonth)
        {
            std::cout << "There was an issue with the cards matching..." << std::endl;
            std::cout << "The current card month:" << currentCardMonth << std::endl;
            std::cout << "The next card month:" << nextCardMonth << std::endl;
        }
        else
        {
            //Need to store card matches from the deck and game hand in players' special match hands
            CardType currentGameCardType = currentGameCard->getCardType();
            CardType nextCardType = nextCard->getCardType();
            Hand *playerLight = m_player1.getLightMatch();
            Hand *playerAnimal = m_player1.getAnimalMatch();
            Hand *playerRibbon = m_player1.getRibbonMatch();
            Hand *playerPlain = m_player1.getPlainMatch();
            switch (currentGameCardType)
            {
            case LIGHT:
                playerLight->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case ANIMAL:
                playerAnimal->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case RIBBON:
                playerRibbon->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case PLAIN:
                playerPlain->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
            switch (nextCardType)
            {
            case LIGHT:
                playerLight->acceptCard(*m_gameDeck.dealCard());
                break;
            case ANIMAL:
                playerAnimal->acceptCard(*m_gameDeck.dealCard());
                break;
            case RIBBON:
                playerRibbon->acceptCard(*m_gameDeck.dealCard());
                break;
            case PLAIN:
                playerPlain->acceptCard(*m_gameDeck.dealCard());
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
        }
        //disconnect deck
        disconnectDeck();
        //call updateCards
        updateCards();
        //call updateYaku
        updateYaku();
        ui->deckButton->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
        m_gameDeck.setDeckIcon(":/deck/Hanafuda_koi-2.svg");
        //check for yaku
        checkYaku();

        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            //Turn is ending
            cpuSelectFromHand();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints();
        }
    }
    else
    {
        int playerCardNum {0};
        for(int i {0};i<guiPlayerCards.size();i++)
        {
            if(guiPlayerCards[i]->isEnabled() == true)
            {
                playerCardNum = i;
            }
        }
        Hand *playerHand = m_player1.getHand();
        //Get player hand card
        Card *playerHandCard = playerHand->getCard(playerCardNum);
        //Get player card month
        CardMonth playerCardMonth = playerHandCard->getMonth();
        if(currentCardMonth != playerCardMonth)
        {
            std::cout << "There was an issue with the cards matching..." << std::endl;
            std::cout << "The current card month:" << currentCardMonth << std::endl;
            std::cout << "The player card month:" << playerCardMonth << std::endl;
        }
        else
        {
            //Need to store card matches from the deck and game hand in players' special match hands
            CardType currentGameCardType = currentGameCard->getCardType();
            CardType playerHandCardType = playerHandCard->getCardType();
            Hand *playerHand = m_player1.getHand();
            Hand *playerLight = m_player1.getLightMatch();
            Hand *playerAnimal = m_player1.getAnimalMatch();
            Hand *playerRibbon = m_player1.getRibbonMatch();
            Hand *playerPlain = m_player1.getPlainMatch();
            switch (currentGameCardType)
            {
            case LIGHT:
                playerLight->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case ANIMAL:
                playerAnimal->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case RIBBON:
                playerRibbon->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case PLAIN:
                playerPlain->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
            switch (playerHandCardType)
            {
            case LIGHT:
                playerLight->acceptCard(*playerHand->getCard(playerCardNum));
                playerHand->removeCard(playerCardNum);
                break;
            case ANIMAL:
                playerAnimal->acceptCard(*playerHand->getCard(playerCardNum));
                playerHand->removeCard(playerCardNum);
                break;
            case RIBBON:
                playerRibbon->acceptCard(*playerHand->getCard(playerCardNum));
                playerHand->removeCard(playerCardNum);
                break;
            case PLAIN:
                playerPlain->acceptCard(*playerHand->getCard(playerCardNum));
                playerHand->removeCard(playerCardNum);
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
        }
        //disconnect all playerhand cards
        disconnectPlayerHand();
        //connect deck
        connectDeck();
        //call updateCards
        updateCards();
        //call updateYaku
        updateYaku();
        //***************************************
        //allows to click deck to call drawCard
        //***************************************
    }
}

/*
 * Slot function for the deck card button in the GUI which
 * determines the player's card selection.
 * It then determines if there are matching cards in the game hand
 * on the game board.  If there are matches it will enable them and
 * connect the buttons allowing the player to then select a matching
 * card from the game board.  If there aren't matches, then it will
 * discard the player's selected card.  Then it will allow the next
 * player to start their turn and select a card from their hand.
 */
void KoiKoi::drawCard()
{
    //Shows next card for deck
    Card *nextCard = m_gameDeck.getCard(m_gameDeck.getNumCards()-1);
    CardMonth nextMonth = nextCard->getMonth();

    bool matchingCard {false};

    //compare with gameHand objects
    for(int i{0};i<m_gameHand.getNumCards();i++)
    {
        if (m_gameHand.getCard(i)->getMonth() != nextMonth)
        {
            //Disable gamehand card
            guiGameHandCards[i]->setDisabled(true);
        }
        else
        {
            matchingCard = true;
            //connect the matching game hand cards
            connectGameHand(guiGameHandCards[i]);
        }
    }

    //See if there are any month matches
    if(matchingCard == false)
    {
        //deal deck card
        //accept in gamehand
        m_gameHand.acceptCard(*m_gameDeck.dealCard());

        //disconnect deck
        disconnectDeck();
        //disconnect all game hand cards
        disconnectGameHand();
        //call updateCards
        updateCards();
        //Testing
        updateYaku();
        checkYaku();

        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            //Turn is ending
            cpuSelectFromHand();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints();
        }

        //**********************************************************
        //allows to click player hand card to call selectFromHand
        //**********************************************************
    }
    else
    {
        //Show next deck card image
        ui->deckButton->setIcon(QIcon(QString(nextCard->getImageStr())));
        m_gameDeck.setDeckIcon(nextCard->getImageStr().toStdString());
        //Disconnect deck
        disconnectDeck();
        //disconnect playerhand
        disconnectPlayerHand();
        //**********************************************************
        //allows to click game hand card to call selectFromGameHand
        //**********************************************************
        //Wait for user to select from gamehand as there may have been multiple match possibilities
    }
}

/*
 * Slot function for the koi-koi buttons in the GUI which
 * determine if the player is declaring koi-koi or shobu after obtaining yaku.
 */
void KoiKoi::requestKoiKoi()
{
    //yes or no buttons
    //get sender()
    QString theSender = sender()->objectName();

    if(theSender.toStdString() == "noButton")
    {
        //if no, then round over, tally points
        tallyPoints();
    }
    else
    {
        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            m_player1.setKoikoi(true);
            showGameScreen();
            //cpuSelectFromHand();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints();
        }
    }
}

void KoiKoi::nextRound()
{
    startRound();
}

void KoiKoi::cpuSelectFromHand()
{
    Hand *cpuHand = m_player2.getHand();

    std::cout << "" << std::endl;
    std::cout << "CPU Hand" << std::endl;
    cpuHand->printHand();
    std::cout << "" << std::endl;

    //Get card number, randomly
    int cardNum {0};
    srand(time(NULL));
    //cardNum = ((int)std::rand() % (m_numCards-1));
    cardNum = ((int)std::rand() % cpuHand->getNumCards());

    std::cout << "CardNum from hand is:  " << cardNum << std::endl;

    //Get cpu card
    Card *currentCPUCard = cpuHand->getCard(cardNum);

    std::cout << "" << std::endl;
    std::cout << "Current Selected CPU card:" << std::endl;
    currentCPUCard->printCard();
    std::cout << "" << std::endl;

    //get month of card button
    CardMonth currentCardMonth = currentCPUCard->getMonth();

    bool matchingCard {false};

    //compare with gameHand objects
    for(int i{0};i<m_gameHand.getNumCards();i++)
    {
        if (m_gameHand.getCard(i)->getMonth() != currentCardMonth)
        {
            //Disable gamehand card
            guiGameHandCards[i]->setDisabled(true);
        }
        else
        {
            matchingCard = true;
        }
    }
    std::cout << "" << std::endl;
    std::cout << "Matching card is:  " << matchingCard << std::endl;
    std::cout << "" << std::endl;
    //Sleep 3??
    QTimer::singleShot(2000, this, SLOT(waitABit()));
    //See if there are any month matches
    if(matchingCard == false)
    {
        //discard selected card from cpuhand
        //accept in gamehand
        m_gameHand.acceptCard(*cpuHand->getCard(cardNum));
        cpuHand->removeCard(cardNum);

        //call updateCards
        updateCards();
        //Sleep 3??
        QTimer::singleShot(2000, this, SLOT(waitABit()));
        //******************
        //call cpuDrawCard
        //******************
        std::cout << "" << std::endl;
        std::cout << "Updated CPU hand:" << std::endl;
        cpuHand->printHand();
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Updated game hand:" << std::endl;
        m_gameHand.printHand();
        std::cout << "" << std::endl;
        cpuDrawCard();
    }
    else
    {
        //Disable all cards in cpuhand except current selected card
        for(int k {0};k<cpuHand->getNumCards();k++)
        {
            if(k != cardNum)
            {
                guiCPUCards[k]->setDisabled(true);
            }
        }
        //Sleep 3??
        QTimer::singleShot(2000, this, SLOT(waitABit()));
        //*****************************
        //call cpuSelectFromGameHand
        //*****************************
        cpuSelectFromGameHand();
    }
}

void KoiKoi::cpuSelectFromGameHand()
{
    /*
     * Could match from deck or cpu hand.
     * Check both.
     */

    //Get random card that was enabled in the game hand
    //since the user can't click stuff the cpu must select somehow
    bool cardFound {false};
    QVector<int> a {};
    //while(cardFound == false)
    //{
    //search through gameHand objects
    for(int i{0};i<guiGameHandCards.size();i++)
    {
        if (guiGameHandCards[i]->isEnabled() == true)
        {
            //Store numbers of found enabled cards
            a.push_back(i);
            cardFound = true;
            std::cout << "a was pushed:  " << i << std::endl;
        }
    }
    //}

    std::cout << "a.size is:  " << a.size() << std::endl;

    //Get card number randomly from stored selection
    int tempCardNum {0};
    int cardNum {0};
    srand(time(NULL));
    //cardNum = ((int)std::rand() % (m_numCards-1));
    tempCardNum = ((int)std::rand() % a.size());
    cardNum = a[tempCardNum];

    std::cout << "tempCardNum from game hand is:  " << tempCardNum << std::endl;
    std::cout << "a's tempCardNum value (cardNum) is:  " << cardNum << std::endl;

    //Get game hand card
    Card *currentGameCard = m_gameHand.getCard(cardNum);
    //get month of card button
    CardMonth currentCardMonth = currentGameCard->getMonth();

    /*
     * If the deck was recently clicked and there was a match
     * then there should be an icon of the next card image.
     * Otherwise it should just be the normal deck image
     * indicating the check should be made with the player's hand.
     *
     * Perhaps in the future with turn based stuff, pass in
     * the player, and some sort of turn state variable
     */
    if(m_gameDeck.getDeckIcon() != ":/deck/Hanafuda_koi-2.svg")
    {
        //Get next card
        Card *nextCard = m_gameDeck.getCard(m_gameDeck.getNumCards()-1);
        //Get next card month
        CardMonth nextCardMonth = nextCard->getMonth();
        if(currentCardMonth != nextCardMonth)
        {
            std::cout << "There was an issue with the cards matching..." << std::endl;
            std::cout << "The current card month:" << currentCardMonth << std::endl;
            std::cout << "The next card month:" << nextCardMonth << std::endl;
        }
        else
        {
            //Need to store card matches from the deck and game hand in players' special match hands
            CardType currentGameCardType = currentGameCard->getCardType();
            CardType nextCardType = nextCard->getCardType();
            Hand *cpuLight = m_player2.getLightMatch();
            Hand *cpuAnimal = m_player2.getAnimalMatch();
            Hand *cpuRibbon = m_player2.getRibbonMatch();
            Hand *cpuPlain = m_player2.getPlainMatch();
            switch (currentGameCardType)
            {
            case LIGHT:
                cpuLight->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case ANIMAL:
                cpuAnimal->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case RIBBON:
                cpuRibbon->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case PLAIN:
                cpuPlain->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
            switch (nextCardType)
            {
            case LIGHT:
                cpuLight->acceptCard(*m_gameDeck.dealCard());
                break;
            case ANIMAL:
                cpuAnimal->acceptCard(*m_gameDeck.dealCard());
                break;
            case RIBBON:
                cpuRibbon->acceptCard(*m_gameDeck.dealCard());
                break;
            case PLAIN:
                cpuPlain->acceptCard(*m_gameDeck.dealCard());
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
        }
        //Connect all playerhand cards
        //This will change with CPU
        connectPlayerHand();
        //disconnect deck
        disconnectDeck();
        //call updateCards
        updateCards();
        //call updateYaku
        updateYaku();
        ui->deckButton->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
        m_gameDeck.setDeckIcon(":/deck/Hanafuda_koi-2.svg");
        //RE-ENABLE AFTER FIXING!!!
        //checkYaku();
        //**********************************************************
        //allows to click player hand card to call selectFromHand
        //**********************************************************
    }
    else
    {
        int cpuCardNum {0};
        for(int i {0};i<guiCPUCards.size();i++)
        {
            if(guiCPUCards[i]->isEnabled() == true)
            {
                cpuCardNum = i;
            }
        }
        Hand *cpuHand = m_player2.getHand();
        //Get player hand card
        Card *cpuHandCard = cpuHand->getCard(cpuCardNum);
        //Get player card month
        CardMonth cpuCardMonth = cpuHandCard->getMonth();
        if(currentCardMonth != cpuCardMonth)
        {
            std::cout << "There was an issue with the cards matching..." << std::endl;
            std::cout << "The current card month:" << currentCardMonth << std::endl;
            std::cout << "The player card month:" << cpuCardMonth << std::endl;
        }
        else
        {
            //Need to store card matches from the deck and game hand in players' special match hands
            CardType currentGameCardType = currentGameCard->getCardType();
            CardType cpuHandCardType = cpuHandCard->getCardType();
            Hand *cpuHand = m_player2.getHand();
            Hand *cpuLight = m_player2.getLightMatch();
            Hand *cpuAnimal = m_player2.getAnimalMatch();
            Hand *cpuRibbon = m_player2.getRibbonMatch();
            Hand *cpuPlain = m_player2.getPlainMatch();
            switch (currentGameCardType)
            {
            case LIGHT:
                cpuLight->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case ANIMAL:
                cpuAnimal->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case RIBBON:
                cpuRibbon->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            case PLAIN:
                cpuPlain->acceptCard(*m_gameHand.getCard(cardNum));
                m_gameHand.removeCard(cardNum);
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
            switch (cpuHandCardType)
            {
            case LIGHT:
                cpuLight->acceptCard(*cpuHand->getCard(cpuCardNum));
                cpuHand->removeCard(cpuCardNum);
                break;
            case ANIMAL:
                cpuAnimal->acceptCard(*cpuHand->getCard(cpuCardNum));
                cpuHand->removeCard(cpuCardNum);
                break;
            case RIBBON:
                cpuRibbon->acceptCard(*cpuHand->getCard(cpuCardNum));
                cpuHand->removeCard(cpuCardNum);
                break;
            case PLAIN:
                cpuPlain->acceptCard(*cpuHand->getCard(cpuCardNum));
                cpuHand->removeCard(cpuCardNum);
                break;
            default:
                std::cout << "It shouldn't get here..." << std::endl;
                break;
            }
        }
        //call updateCards
        updateCards();
        //call updateYaku
        updateYaku();
        //******************
        //call cpuDrawCard
        //******************
        cpuDrawCard();
    }
}

void KoiKoi::cpuDrawCard()
{
    //Shows next card for deck
    Card *nextCard = m_gameDeck.getCard(m_gameDeck.getNumCards()-1);
    CardMonth nextMonth = nextCard->getMonth();

    bool matchingCard {false};

    //compare with gameHand objects
    for(int i{0};i<m_gameHand.getNumCards();i++)
    {
        if (m_gameHand.getCard(i)->getMonth() != nextMonth)
        {
            //Disable gamehand card
            guiGameHandCards[i]->setDisabled(true);
        }
        else
        {
            matchingCard = true;
        }
    }
    //Sleep 3??
    QTimer::singleShot(2000, this, SLOT(waitABit()));
    //See if there are any month matches
    if(matchingCard == false)
    {
        //deal deck card
        //accept in gamehand
        m_gameHand.acceptCard(*m_gameDeck.dealCard());

        //call updateCards
        updateCards();
        //Testing
        updateYaku();
        checkYaku();

        /*
         * Check for end of round (if player has cards)
         */
        if(m_player2.getHand()->getNumCards() > 0)
        {
            //Turn is ending
            //Do it at the beginning of a new turn
            //Already done above, but as mentioned this will change with CPU
            connectPlayerHand();
            disconnectDeck();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen

            //Should probably show the last card not match
            //and have been added to the gameboard (sleep 2)

            tallyPoints();
        }

        //**********************************************************
        //allows to click player hand card to call selectFromHand
        //**********************************************************
    }
    else
    {
        //Show next deck card image
        ui->deckButton->setIcon(QIcon(QString(nextCard->getImageStr())));
        m_gameDeck.setDeckIcon(nextCard->getImageStr().toStdString());
        //****************************
        //call cpuSelectFromGameHand
        //****************************
        std::cout << "" << std::endl;
        std::cout << "Next deck card:" << std::endl;
        nextCard->printCard();
        std::cout << "" << std::endl;
        cpuSelectFromGameHand();
    }
}

/*
 * Slot function for the koi-koi buttons in the GUI which
 * determine if the player is declaring koi-koi or shobu after obtaining yaku.
 */
void KoiKoi::cpuRequestKoiKoi()
{
    //yes or no buttons
    //get sender()
    QString theSender = sender()->objectName();

    if(theSender.toStdString() == "noButton")
    {
        //if no, then round over, tally points
        tallyPoints();
    }
    else
    {
        //else yes, then round continues, but update player koikoi status
        //if opponent scores a yaku and declares shobu while player has called koikoi, they lose points
        m_player2.setKoikoi(true);
        //Switch to next player turn
        showGameScreen();
        //Do it at the beginning of a new turn
        //This will change with CPU
        //connectPlayerHand();
        //disconnectDeck();
    }
}

void KoiKoi::waitABit()
{
    std::cout << "Waited..." << std::endl;
}
