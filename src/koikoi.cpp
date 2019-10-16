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
#include "ui_koikoi.h"
#include "preferences.h"
#include "ui_preferences.h"
#include "about.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <iostream>
#include <chrono>  // Sleep Time
#include <thread>  //Thread Sleep
#include <QVector>
#include <QString>
#include <QPushButton>
#include <QIntegerForSize>
#include <QIcon>
#include <QThread>
#include <QPixmap>
#include <QTimer>
#include <QRegularExpression>
#include <QDir>
#include <QPainter>
#include <QSettings>
#include <QSpinBox>

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

    ui->setupUi(this);

    this->setStyleSheet("QLabel"
                        "{"
                        "background-color: rgba(42, 42, 42, 191);"
                        "border-radius: 10px;"
                        "}");

    //Load settings
    loadSettings();

    //Title and Application Icon
    this->setWindowTitle(tr("Koi-Koi Hanafuda"));
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
        button->setIcon(QIcon(m_deckArt));
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
        button->setIcon(QIcon(m_deckArt));
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
        button->setIcon(QIcon(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
        label->setPixmap(QPixmap(m_deckArt));
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
    this->m_player1.setKoikoi(false);
    this->m_player2.setKoikoi(false);
    this->m_player1.setKoikoiNum(0);
    this->m_player2.setKoikoiNum(0);
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
        this->m_player1.setKoikoi(false);
        this->m_player2.setKoikoi(false);
        this->m_player1.setKoikoiNum(0);
        this->m_player2.setKoikoiNum(0);
        updateKoiKoi();
        resetYaku();
        resetTally();

        //Testing
        ui->deckButton->setIcon(QIcon(m_deckArt));
        m_gameDeck.setDeckIcon(m_deckArt.toStdString());

        //Set Round Label
        ui->gameRoundLabel->setText(QString(tr("Round: %1 / %2")).arg(m_currentRound).arg(m_rounds));

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

            ui->playerOya->setVisible(true);
            ui->cpuOya->setVisible(false);

            //Make sure at end of player's turn when drawing card and
            //possibly matching with game hand to kick off next cpu turn...
        }
        else
        {
            //cpu is oya
            disconnectPlayerHand();
            disconnectGameHand();
            disconnectDeck();

            ui->playerOya->setVisible(false);
            ui->cpuOya->setVisible(true);

            //call cpu/ai functions to facilitate cpu turns
            //At end of cpu turn, make sure stage is set for player...
            //Testing
            //waitABit();
            cpuSelectFromHand();
        }
    }
    else
    {
        if(m_player1.getOya() == true)
        {
            //end game
            //don't think it should get here...
            this->m_gameStatus = false;
            tallyPoints(1);
        }
        else
        {
            //end game
            //don't think it should get here...
            this->m_gameStatus = false;
            tallyPoints(2);
        }
    }
}

/*
 * Tally the points for each player at the end of the round.
 */
void KoiKoi::tallyPoints(int playerNum)
{
    //Set round number in UI
    ui->roundLabel->setText(QString(tr("Round:  %1")).arg(m_currentRound));  //Using .arg() with argument substitution to convert/append integer to part of a QString

    //Get current player and opponent
    Player *currentPlayer = this->getPlayer(playerNum);
    Player *opponent;

    if(playerNum == 1)
    {
        opponent = this->getPlayer(2);
    }
    else
    {
        opponent = this->getPlayer(1);
    }

    //Tally points - Subtotals
    int playerSubTotal {0};
    int cpuSubTotal {0};

    //m_player1.printYaku();
    //m_player2.printYaku();

    if(playerNum == 1)
    {
        for (int i {0}; i < currentPlayer->getYakuSize();i++)
        {
            if(currentPlayer->getYaku(i) == true)
            {
                playerSubTotal = playerSubTotal + acceptableYaku[i].getPointValue();
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
                    ui->tally_goko_player_points->setText(QString("%1").arg(acceptableYaku[i].getPointValue()));
                    break;
                default:
                    break;
                }
            }
        }
        ui->tally_subtotal_player_points->setText(QString("%1").arg(playerSubTotal));
    }
    else
    {
        for (int j {0}; j < currentPlayer->getYakuSize();j++)
        {
            if(currentPlayer->getYaku(j) == true)
            {
                cpuSubTotal = cpuSubTotal + acceptableYaku[j].getPointValue();
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
                    ui->tally_goko_cpu_points->setText(QString("%1").arg(acceptableYaku[j].getPointValue()));
                    break;
                default:
                    break;
                }
            }
        }
        ui->tally_subtotal_cpu_points->setText(QString("%1").arg(cpuSubTotal));
    }

    //Get koikoi
    bool currentKoiKoi = currentPlayer->getKoikoi();
    bool opponentKoiKoi = opponent->getKoikoi();

    //Set default koikoi amount
    int currentKoikoiTotal {0};
    int opponentKoikoiTotal {0};

    //If koikoi, get points for each koikoi (1 per koikoi)
    if(currentKoiKoi == true)
    {
        //Get koikoi amount
        currentKoikoiTotal = currentPlayer->getKoikoiNum();
    }

    //If koikoi, get points for each koikoi (1 per koikoi)
    if(opponentKoiKoi == true)
    {
        //Get koikoi amount
        opponentKoikoiTotal = opponent->getKoikoiNum();
    }

    //Add koikoi amount to subtotal
    //If opponent had koikoi as well, currentPlayer's points from current round are doubled
    if(playerNum == 1)
    {
        ui->tally_koikoi_player_points->setText(QString("%1").arg(currentKoikoiTotal));
        ui->tally_koikoi_cpu_points->setText(QString("%1").arg(opponentKoikoiTotal));
        if(opponentKoiKoi == true)
        {
            currentPlayer->setScore(currentPlayer->getScore() + ((playerSubTotal + currentKoikoiTotal) * 2));
            opponent->setScore(opponent->getScore() - ((playerSubTotal + currentKoikoiTotal) * 2));
            ui->tally_koikoi_player_double->setText(QString("%1").arg("x2"));
            ui->tally_koikoi_cpu_double->setText(QString("%1").arg("N/A"));
        }
        else
        {
            currentPlayer->setScore(currentPlayer->getScore() + (playerSubTotal + currentKoikoiTotal));
            opponent->setScore(opponent->getScore() - (playerSubTotal + currentKoikoiTotal));
            ui->tally_koikoi_player_double->setText(QString("%1").arg("N/A"));
            ui->tally_koikoi_cpu_double->setText(QString("%1").arg("N/A"));
        }
    }
    else
    {
        ui->tally_koikoi_cpu_points->setText(QString("%1").arg(currentKoikoiTotal));
        ui->tally_koikoi_player_points->setText(QString("%1").arg(opponentKoikoiTotal));
        if(opponentKoiKoi == true)
        {
            currentPlayer->setScore(currentPlayer->getScore() + ((cpuSubTotal + currentKoikoiTotal) * 2));
            opponent->setScore(opponent->getScore() - ((cpuSubTotal + currentKoikoiTotal) * 2));
            ui->tally_koikoi_cpu_double->setText(QString("%1").arg("x2"));
            ui->tally_koikoi_player_double->setText(QString("%1").arg("N/A"));
        }
        else
        {
            currentPlayer->setScore(currentPlayer->getScore() + (cpuSubTotal + currentKoikoiTotal));
            opponent->setScore(opponent->getScore() - (cpuSubTotal + currentKoikoiTotal));
            ui->tally_koikoi_cpu_double->setText(QString("%1").arg("N/A"));
            ui->tally_koikoi_player_double->setText(QString("%1").arg("N/A"));
        }
    }

    //Total points should equal (current score + ((subtotal + koikoi amount) * 2))) if opponent had koikoi
    //Or current score - currentPlayer's ((subtotal + koikoi amount) * 2))) if you are the opponent and round loser

    ui->tally_total_player_points->setText(QString("%1").arg(m_player1.getScore()));
    ui->tally_total_cpu_points->setText(QString("%1").arg(m_player2.getScore()));

    //Show Tally Points frame/screen
    showTallyScreen();
    if(m_currentRound == m_rounds || m_player1.getScore() >= 60 || m_player2.getScore() >= 60)
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
        }
        else
        {
            //CPU has Oya
            m_player1.setOya(false);
            m_player2.setOya(true);
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
            button->setIcon(QIcon(m_deckArt));
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
            button->setIcon(QIcon(m_deckArt));
            button->setEnabled(false);
            button->setVisible(false);
        }
        else
        {
            if (k>playerHand->getNumCards()-1)
            {
                button->setIcon(QIcon(m_deckArt));
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
    ui->cpuScore->setText(QString(tr("Score:  %1")).arg(m_player2.getScore()));
    ui->playerScore->setText(QString(tr("Score:  %1")).arg(m_player1.getScore()));
}

void KoiKoi::updateKoiKoi()
{
    ui->playerKoiKoi->setText(QString(tr("Koi-Koi: x%1")).arg(this->m_player1.getKoikoiNum()));
    ui->cpuKoiKoi->setText(QString(tr("Koi-Koi: x%1")).arg(this->m_player2.getKoikoiNum()));
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
    ui->player_goko_yaku->setVisible(false);
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
    ui->cpu_goko_yaku->setVisible(false);
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
    ui->tally_goko_player_points->setText(QString("%1").arg(0));
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
    ui->tally_goko_cpu_points->setText(QString("%1").arg(0));
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
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
            label->setPixmap(m_deckArt);
            label->setVisible(false);
        }
        else
        {
            label->setPixmap(QString(cpuPlainHand->getCard(q)->getImageStr()));
            label->setVisible(true);
        }
    }
}

/*
 * Determines if player has obtained specific yaku, and assigns values appropriately.
 * It then displays the yaku in the UI.  The player is specified by passing an int of 1 or 2.
 * 1 - Player 1, Human
 * 2 - Player 2, CPU
 */
void KoiKoi::checkYaku(int playerNum)
{
    Player *currentPlayer = this->getPlayer(playerNum);
    Hand *playerLightHand = currentPlayer->getLightMatch();
    Hand *playerAnimalHand = currentPlayer->getAnimalMatch();
    Hand *playerRibbonHand = currentPlayer->getRibbonMatch();
    Hand *playerPlainHand = currentPlayer->getPlainMatch();

    //Yaku UI QLabels
    QLabel *ameshiko_yaku;
    QLabel *goko_yaku;
    QLabel *sanko_yaku;
    QLabel *shiko_yaku;
    QLabel *hanami_de_ippai_yaku;
    QLabel *tsukimi_de_ippai_yaku;
    QLabel *inoshikacho_yaku;
    QLabel *tane_yaku;
    QLabel *akatan_yaku;
    QLabel *aotan_yaku;
    QLabel *akatan_aotan_no_chofuku_yaku;
    QLabel *tanzaku_yaku;
    QLabel *bake_fuda_yaku;
    QLabel *kasu_yaku;
    QLabel *oya_ken_yaku;
    QLabel *tsuki_fuda_yaku;

    if(playerNum == 1)
    {
        ameshiko_yaku = ui->player_ameshiko_yaku;
        goko_yaku = ui->player_goko_yaku;
        sanko_yaku = ui->player_sanko_yaku;
        shiko_yaku = ui->player_shiko_yaku;
        hanami_de_ippai_yaku = ui->player_hanami_de_ippai_yaku;
        tsukimi_de_ippai_yaku = ui->player_tsukimi_de_ippai_yaku;
        inoshikacho_yaku = ui->player_inoshikacho_yaku;
        tane_yaku = ui->player_tane_yaku;
        akatan_yaku = ui->player_akatan_yaku;
        aotan_yaku = ui->player_aotan_yaku;
        akatan_aotan_no_chofuku_yaku = ui->player_akatan_aotan_no_chofuku_yaku;
        tanzaku_yaku = ui->player_tanzaku_yaku;
        bake_fuda_yaku = ui->player_bake_fuda_yaku;
        kasu_yaku = ui->player_kasu_yaku;
        oya_ken_yaku = ui->player_oya_ken_yaku;
        tsuki_fuda_yaku = ui->player_tsuki_fuda_yaku;
    }
    else
    {
        ameshiko_yaku = ui->cpu_ameshiko_yaku;
        goko_yaku = ui->cpu_goko_yaku;
        sanko_yaku = ui->cpu_sanko_yaku;
        shiko_yaku = ui->cpu_shiko_yaku;
        hanami_de_ippai_yaku = ui->cpu_hanami_de_ippai_yaku;
        tsukimi_de_ippai_yaku = ui->cpu_tsukimi_de_ippai_yaku;
        inoshikacho_yaku = ui->cpu_inoshikacho_yaku;
        tane_yaku = ui->cpu_tane_yaku;
        akatan_yaku = ui->cpu_akatan_yaku;
        aotan_yaku = ui->cpu_aotan_yaku;
        akatan_aotan_no_chofuku_yaku = ui->cpu_akatan_aotan_no_chofuku_yaku;
        tanzaku_yaku = ui->cpu_tanzaku_yaku;
        bake_fuda_yaku = ui->cpu_bake_fuda_yaku;
        kasu_yaku = ui->cpu_kasu_yaku;
        oya_ken_yaku = ui->cpu_oya_ken_yaku;
        tsuki_fuda_yaku = ui->cpu_tsuki_fuda_yaku;
    }

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
    //Goko, 10pts
    bool foundRain {false};
    switch (playerLightHand->getNumCards())
    {
    case 3:
        if(currentPlayer->getYaku(12) != true)
        {
            //Sanko, 5pts
            currentPlayer->setYaku(12, true);
            sanko_yaku->setVisible(true);
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
            if(currentPlayer->getYaku(13) != true)
            {
                currentPlayer->setYaku(13, true);
                ameshiko_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        else
        {
            if(currentPlayer->getYaku(14) != true)
            {
                currentPlayer->setYaku(14, true);
                shiko_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        break;
    case 5:
        if(currentPlayer->getYaku(15) != true)
        {
            //Goko, 10pts
            currentPlayer->setYaku(15, true);
            goko_yaku->setVisible(true);
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
                    if(currentPlayer->getYaku(10) != true)
                    {
                        currentPlayer->setYaku(10, true);
                        tsukimi_de_ippai_yaku->setVisible(true);
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
                    if(currentPlayer->getYaku(11) != true)
                    {
                        currentPlayer->setYaku(11, true);
                        hanami_de_ippai_yaku->setVisible(true);
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
        if(currentPlayer->getYaku(4) != true)
        {
            currentPlayer->setYaku(4, true);
            tane_yaku->setVisible(true);
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
                                if(currentPlayer->getYaku(5) != true)
                                {
                                    currentPlayer->setYaku(5, true);
                                    inoshikacho_yaku->setVisible(true);
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
            if(currentPlayer->getYaku(7) != true)
            {
                currentPlayer->setYaku(7, true);
                akatan_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        //Aotan, 5pts
        if(numBlueRibbons >= 3)
        {
            if(currentPlayer->getYaku(8) != true)
            {
                currentPlayer->setYaku(8, true);
                aotan_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
        //Akatan Aotan No Chofuku, 10pts
        if(numRedPoems >= 3 && numBlueRibbons >= 3)
        {
            if(currentPlayer->getYaku(9) != true)
            {
                currentPlayer->setYaku(9, true);
                akatan_aotan_no_chofuku_yaku->setVisible(true);
                obtainedYaku = true;
            }
        }
    }

    //Tanzaku, 1pt
    if(playerRibbonHand->getNumCards() >= 5)
    {
        if(currentPlayer->getYaku(6) != true)
        {
            currentPlayer->setYaku(6, true);
            tanzaku_yaku->setVisible(true);
            obtainedYaku = true;
        }
    }

    //Kasu, 1pt
    if (playerPlainHand->getNumCards() >=10)
    {
        if(currentPlayer->getYaku(0) != true)
        {
            currentPlayer->setYaku(0, true);
            kasu_yaku->setVisible(true);
            obtainedYaku = true;
        }
    }

    if(obtainedYaku == true)
    {
        if(playerNum == 1)
        {
            //Call function to ask if player wants to declare koikoi
            showKoiKoiScreen();
        }
        else
        {
            //Call function to determine if cpu declares koikoi
            cpuRequestKoiKoi();
        }
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
    Preferences *prefs = new Preferences(this);
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
    }
    else
    {
        //CPU has Oya
        m_player1.setOya(false);
        m_player2.setOya(true);
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
    //Get card number
    int cardNum {0};

    QRegularExpression regEx("(\\d{2}|\\d{1})");
    QRegularExpressionMatch match = regEx.match(buttonName);
    if (match.hasMatch())
    {
        //Get card number
        QString matchedString = match.captured(1);
        cardNum = matchedString.toInt();
    }
    else
    {
        std::cout << "There were issues matching regex with the sender button to obtain the button number..." << std::endl;
    }

    //disconnect all game hand cards
    disconnectGameHand();

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
    if(m_gameDeck.getDeckIcon() != m_deckArt.toStdString())
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
            std::cout << "Area 1" << std::endl;
            std::cout << m_gameDeck.getDeckIcon() << std::endl;
            std::cout << m_deckArt.toStdString() << std::endl;
            std::cout << "" << std::endl;
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
        ui->deckButton->setIcon(QIcon(m_deckArt));
        m_gameDeck.setDeckIcon(m_deckArt.toStdString());
        //call checkYaku
        checkYaku(1);

        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            //Testing
            //waitABit();
            //Turn is ending
            cpuSelectFromHand();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints(1);
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
            std::cout << "Area 2" << std::endl;
        }
        else
        {
            //Need to store card matches from the deck and game hand in players' special match hands
            CardType currentGameCardType = currentGameCard->getCardType();
            CardType playerHandCardType = playerHandCard->getCardType();
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
        //call updateYaku
        updateYaku();
        //call checkYaku
        checkYaku(1);

        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            //Testing
            //waitABit();
            //Turn is ending
            cpuSelectFromHand();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints(1);
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
        tallyPoints(1);
    }
    else
    {
        /*
             * Check for end of round (if player has cards)
             *
             * The check might need to be done before requesting koikoi
             */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            m_player1.setKoikoi(true);
            m_player1.setKoikoiNum(m_player1.getKoikoiNum()+1);
            updateKoiKoi();
            showGameScreen();
            //checkYaku -> showKoiKoiScreen -> yes_button -> requestKoiKoi -> continue on to cpu turn...
            //cpuSelectFromHand();
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints(1);
        }
    }
}

/*
 * Public slot used to start the next round.
 * Triggered and called by the Continue Button on the tally screen.
 */
void KoiKoi::nextRound()
{
    startRound();
}

/*
 * Function for the CPU hand which determines the CPU's card selection.
 * It then determines if there are matching cards in the game hand
 * on the game board.  If there are matches it will randomly select
 * a matching card from the game board.  If there aren't matches, then it will
 * discard the CPU's selected card, and allow the CPU to draw
 * a card from the deck.
 */
void KoiKoi::cpuSelectFromHand()
{
    Hand *cpuHand = m_player2.getHand();

    //Get card number, randomly
    int cardNum {0};
    srand(time(nullptr));
    //cardNum = ((int)std::rand() % (m_numCards-1));
    cardNum = ((int)std::rand() % cpuHand->getNumCards());

    //Get cpu card
    Card *currentCPUCard = cpuHand->getCard(cardNum);

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
    //See if there are any month matches
    if(matchingCard == false)
    {
        //discard selected card from cpuhand
        //accept in gamehand
        m_gameHand.acceptCard(*cpuHand->getCard(cardNum));
        cpuHand->removeCard(cardNum);

        //call updateCards
        updateCards();
        //******************
        //call cpuDrawCard
        //******************
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
        //*****************************
        //call cpuSelectFromGameHand
        //*****************************
        cpuSelectFromGameHand();
    }
}

/*
 * Function for the game hand which determines the CPU's selection.
 * It then determines if there are matching cards in the CPU hand
 * or deck.  If there are matches it will move the cards to the
 * appropriate yaku hands.
 *
 * This function helps maintain turn flow with connections and
 * disconnections from various buttons in the GUI under certain
 * circumstances for the human player as well as calling required
 * functions for the CPU.
 */
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

    //search through gameHand objects
    for(int i{0};i<guiGameHandCards.size();i++)
    {
        if (guiGameHandCards[i]->isEnabled() == true)
        {
            //Store numbers of found enabled cards
            a.push_back(i);
            cardFound = true;
        }
    }

    //Get card number randomly from stored selection
    int tempCardNum {0};
    int cardNum {0};
    srand(time(nullptr));
    tempCardNum = ((int)std::rand() % a.size());
    cardNum = a[tempCardNum];

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
    if(m_gameDeck.getDeckIcon() != m_deckArt.toStdString())
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
            std::cout << "Area 3" << std::endl;
            std::cout << m_gameDeck.getDeckIcon() << std::endl;
            std::cout << m_deckArt.toStdString() << std::endl;
            std::cout << "" << std::endl;
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
        connectPlayerHand();
        //disconnect deck
        disconnectDeck();
        //call updateCards
        updateCards();
        //call updateYaku
        updateYaku();
        ui->deckButton->setIcon(QIcon(m_deckArt));
        m_gameDeck.setDeckIcon(m_deckArt.toStdString());
        //call checkYaku
        checkYaku(2);

        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            //Turn is ending
        }
        else
        {
            //Player out of cards
            //End round, show tally screen
            tallyPoints(2);
        }
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
            std::cout << "Area 4" << std::endl;
        }
        else
        {
            //Need to store card matches from the deck and game hand in players' special match hands
            CardType currentGameCardType = currentGameCard->getCardType();
            CardType cpuHandCardType = cpuHandCard->getCardType();
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
    //See if there are any month matches
    if(matchingCard == false)
    {
        //deal deck card
        //accept in gamehand
        m_gameHand.acceptCard(*m_gameDeck.dealCard());

        //call updateCards
        updateCards();
        updateYaku();
        checkYaku(2);

        /*
         * Check for end of round (if player has cards)
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
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
            tallyPoints(2);
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
        cpuSelectFromGameHand();
    }
}

/*
 * Function for the CPU to determine if it is declaring koi-koi
 * or shobu after obtaining yaku.
 */
void KoiKoi::cpuRequestKoiKoi()
{
    //Randomly select yes or no for koikoi
    //Get number randomly
    int koikoiDecision {0};
    srand(time(nullptr));
    koikoiDecision = ((int)std::rand() % 2);

    if(koikoiDecision == 0)
    {
        tallyPoints(2);
    }
    else
    {
        /*
         * Check for end of round (if player has cards)
         *
         * The check might need to be done before requesting koikoi
         */
        if((m_player1.getHand()->getNumCards() > 0) && (m_player2.getHand()->getNumCards() > 0))
        {
            m_player2.setKoikoi(true);
            m_player2.setKoikoiNum(m_player2.getKoikoiNum()+1);
            updateKoiKoi();
            showGameScreen();
            //Set up connections for player??
        }
        else
        {
            //player out of cards
            //End round, show tally screen
            tallyPoints(2);
        }
    }

}

void KoiKoi::waitABit()
{
    QThread::sleep(1);
    std::cout << "Waited..." << std::endl;
}

/*
 * Allows the setting of a custom background image from the resource collection.
 */
void KoiKoi::setBG()
{
    QObject *senderButton = sender();

    if(senderButton == nullptr)
    {
        //BG has been set from settings file, just wait
    }
    else
    {
        QString buttonName = senderButton->objectName();

        //std::cout << buttonName.toStdString() << std::endl;

        //Get card number
        int buttonNum {0};

        QRegularExpression regEx("(\\d{2}|\\d{1})");
        QRegularExpressionMatch match = regEx.match(buttonName);
        if (match.hasMatch())
        {
            //Get card number
            QString matchedString = match.captured(1);
            buttonNum = matchedString.toInt();
        }
        else
        {
            std::cout << "There were issues matching regex with the sender button to obtain the button number..." << std::endl;
        }

        QDir *backResource = new QDir(":/backgrounds/");

        QString resBGFilename = QString(":/backgrounds/" + backResource->entryList().at(buttonNum));

        this->m_bkgnd = QPixmap(resBGFilename);

        if (resBGFilename == nullptr)
        {
            //We got issues
        }
        else
        {
            if(!settings.isWritable())
            {
                //We got issues
            }
            else
            {
                this->settings.setValue("background", resBGFilename);
                this->settings.setValue("bgRadio", buttonName);
                this->settings.sync();
                this->settings.status();
            }
        }
    }
    //Ensure scaled
    this->m_bkgnd = this->m_bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    //Sends paintEvent()
    this->repaint();
}

void KoiKoi::setDeck()
{
    QObject *senderButton = sender();

    if(senderButton == nullptr)
    {
        //Deck has been set from settings file, just wait
    }
    else
    {
        QString buttonName = senderButton->objectName();

        //Get card number
        int buttonNum {0};

        QRegularExpression regEx("(\\d{2}|\\d{1})");
        QRegularExpressionMatch match = regEx.match(buttonName);
        if (match.hasMatch())
        {
            //Get card number
            QString matchedString = match.captured(1);
            buttonNum = matchedString.toInt();
        }
        else
        {
            std::cout << "There were issues matching regex with the sender button to obtain the button number..." << std::endl;
        }

        QDir *deckResource = new QDir(":/decks/");

        QString resDeckFilename = QString(":/decks/" + deckResource->entryList().at(buttonNum));

        this->m_deckArt = resDeckFilename;

        if (resDeckFilename == nullptr)
        {
            //We got issues
        }
        else
        {
            if(!settings.isWritable())
            {
                //We got issues
            }
            else
            {
                this->settings.setValue("deck", resDeckFilename);
                this->settings.setValue("deckRadio", buttonName);
                this->settings.sync();
                this->settings.status();
            }
        }
    }

    /*
     * Figure out how to go about setting the deck art
     * for game deck, oya cards, and CPU hand
     */
    ui->oyaButton_0->setIcon(QIcon(m_deckArt));
    ui->oyaButton_1->setIcon(QIcon(m_deckArt));
    ui->deckButton->setIcon(QIcon(m_deckArt));
    for(int i{0};i<guiCPUCards.size();i++)
    {
        guiCPUCards.at(i)->setIcon(QIcon(m_deckArt));
    }
}

void KoiKoi::setRounds(int numRounds)
{
    QObject *senderButton = sender();

    if(senderButton == nullptr)
    {
        //Rounds has been set from settings file, just wait
    }
    else
    {
        if(!settings.isWritable())
        {
            //We got issues
        }
        else
        {
            this->settings.setValue("rounds", numRounds);
            this->settings.sync();
            this->settings.status();
        }
    }

    /*
     * Figure out how to go about setting the rounds
     * Rounds should not be changed while a game is in progress
     */
    if(!settings.isWritable())
    {
        //We got issues
    }
    else
    {
        switch (this->settings.value("rounds", "").toInt())
        {
        case 6:
        case 12:
            this->m_rounds = this->settings.value("rounds", "").toInt();
            if(m_currentRound > 0)
            {
                onQuitGameClicked();
            }
            break;
        default:
            this->m_rounds = 12;
            break;
        }
    }
}

/*
 * Used to enforce painting of the custom background pixmap.
 * QPainter and paintEvent had to be used as opposed to using QPalette due
 * to the fact that setting the background with QPalette affected the menubar negatively.
 * The menubar colors were not respected, and there was no way to force the pixmap to begin
 * painting in the window below the menubar.
 */
void KoiKoi::paintEvent(QPaintEvent *pe)
{
    //width - x
    //height - y

    int relativeWidth = this->width();
    int relativeHeight = this->height() - ui->menubar->height();

    int pixWidth = m_bkgnd.width();
    int pixHeight = m_bkgnd.height();

    int diffWidth {0};
    int diffHeight {0};

    QPainter paint(this);

    //Centers pixmap
    if (pixWidth < relativeWidth)
    {
        //then center horizontally
        diffWidth = relativeWidth - pixWidth;
        paint.drawPixmap(0+(diffWidth/2), 0+ui->menubar->height(), m_bkgnd);
    }
    else if(pixHeight < relativeHeight)
    {
        //then center vertically
        diffHeight = relativeHeight -pixHeight;
        paint.drawPixmap(0, 0+(diffHeight/2)+ui->menubar->height(), m_bkgnd);
    }
}

void KoiKoi::loadSettings()
{
    if(!settings.isWritable())
    {
        //We got issues
    }
    else
    {
        //BG
        QString resBGFilename = this->settings.value("background", "").toString();
        if (resBGFilename != nullptr) {
            this->m_bkgnd = QPixmap(resBGFilename);
            setBG();
        }
        //Deck
        QString resDeckFilename = this->settings.value("deck", "").toString();
        if (resDeckFilename != nullptr) {
            this->m_deckArt = resDeckFilename;
            setDeck();
        }
        //Rounds, had to supply a value to match the slot...
        //The setRounds() ensures the saved value or a default is loaded
        setRounds(m_rounds);
    }
}
