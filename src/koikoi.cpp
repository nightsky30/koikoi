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
#include <QPushButton>
#include <QIntegerForSize>
#include <QIcon>
#include <QList>
#include <QDebug>

// Using a type alias
using index_t = std::vector<Card>::size_type;

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
    connect(ui->actionNew_Game, &QAction::triggered, this, &KoiKoi::onNewGameClicked);
    connect(ui->actionQuit_Game, &QAction::triggered, this, &KoiKoi::onQuitGameClicked);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    connect(ui->actionPreferences, &QAction::triggered, this, &KoiKoi::onPreferencesClicked);
    connect(ui->actionAbout, &QAction::triggered, this, &KoiKoi::onAboutClicked);

    //Set up game cards defaults in GUI
    for(int i{0};i<8;i++)
    {
        QString buttonName = "cpuButton_" + QString::number(i);
        QPushButton *button = new QPushButton(buttonName, this);
        button->setMinimumSize(120,168);
        button->setMaximumSize(120,168);
        button->setText("");
        button->setIcon(QIcon(":/deck/Hanafuda_koi-2.svg"));
        button->setIconSize(QSize(120,168));
        button->setFlat(true);
        button->setVisible(true);
        button->show();
        ui->cpuHLayout->addWidget(button);
        this->guiCPUCards.push_back(button);
    }

    for(int j{0};j<16;j++)
    {
        QString buttonName = "gameButton_" + QString::number(j);
        QPushButton *button = new QPushButton(buttonName, this);
        button->setMinimumSize(120,168);
        button->setMaximumSize(120,168);
        button->setText("");
        button->setIcon(QIcon(":/deck/Hanafuda_koi-2.svg"));
        button->setIconSize(QSize(120,168));
        button->setFlat(true);
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
            qDebug() << "Problem:  Too many cards on the gameboard.";
        }
        this->guiGameHandCards.append(button);
    }

    for(int k{0};k<8;k++)
    {
        QString buttonName = "playerButton_" + QString::number(k);
        QPushButton *button = new QPushButton(buttonName, this);
        button->setMinimumSize(120,168);
        button->setMaximumSize(120,168);
        button->setText("");
        button->setIcon(QIcon(":/deck/Hanafuda_koi-2.svg"));
        button->setIconSize(QSize(120,168));
        button->setFlat(true);
        button->setVisible(true);
        button->show();
        ui->playerHLayout->addWidget(button);
        this->guiPlayerCards.push_back(button);
    }

    //QLABELS DO NOT HAVE A CLICKED FUNCTION
    //USE BUTTONS STYLED DIFFERENTLY OR EXTEND THE QLABEL WITH A SUBCLASS THAT IMPLEMENTS THE CLICKABLE SIGNAL/SLOT JUNK
    connect(ui->oyaButton_0, SIGNAL (released()), this, SLOT(determineOyaPlayer()));
    connect(ui->oyaButton_1, SIGNAL (released()), this, SLOT(determineOyaPlayer()));


    showTitleScreen();
}

KoiKoi::~KoiKoi()
{
    delete ui;
}

Deck* KoiKoi::getDeck()
{
    Deck *gameDeck;
    gameDeck = &m_gameDeck;
    return gameDeck;
}

Player* KoiKoi::getPlayer(int playerNum)
{
    Player *requestedPlayer;
    switch (playerNum)
    {
    case 1:
        requestedPlayer = &m_player1;
        return requestedPlayer;
        break;
    case 2:
        requestedPlayer = &m_player2;
        return requestedPlayer;
        break;
    default:
        std::cout << "Invalid player number. You must specify a value of 1 or 2. Returning player 1 by default." << std::endl;
        requestedPlayer = &m_player1;
        return requestedPlayer;
        break;
    }
}

Hand* KoiKoi::getGameHand()
{
    Hand *gameHand;
    gameHand = &m_gameHand;
    return gameHand;
}

int KoiKoi::getNumRounds()
{
    return m_rounds;
}

int KoiKoi::getCurrentRound()
{
    return m_currentRound;
}

bool KoiKoi::getGameStatus()
{
    return m_gameStatus;
}

void KoiKoi::startGame()
{
    this->m_player1.getHand()->resetHand();
    this->m_player2.getHand()->resetHand();
    this->m_gameHand.resetHand();
    this->m_gameDeck.resetDeck();
    this->m_gameDeck.shuffleDeck();
    this->m_oyaHand.resetHand();
    generateOyaCard();
}

void KoiKoi::generateOyaCard()
{
    //Ask human player to select 1 of 2 random cards
    //Compare cards
    //Earliest card is the Oya and has advantage of going first

    //Use m_oyaHand...
    //Card 1 and 2
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

void KoiKoi::determineOyaPlayer()
{
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();

    index_t oyaCard = m_oyaHand.getOyaCard();
    QChar buttonNum = (buttonName.at(buttonName.size()-1));

    if (buttonNum.digitValue() == (int)oyaCard)
        //if (true)
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
    startRound();//deal and showGameScreen in startRound
}

void KoiKoi::deal()
{
    index_t fourCount {0};

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

void KoiKoi::startRound()
{
    deal();
    updateCards();
    showGameScreen();

    //    bool firstTurn {true};
    //    bool roundOver {false};
    //    int playerTurn {0};

    //    Player *player1;
    //    player1 = &m_player1;
    //    Player *player2;
    //    player2 = &m_player2;

    //    while(roundOver == false)
    //    {
    //        if (firstTurn == true)
    //        {
    //            if (player1->getOya() == true)
    //            {
    //                //Player 1's turn
    //                playerTurn = 1;
    //                takeTurn(*player1, playerTurn);
    //            }
    //            else
    //            {
    //                //CPU's turn
    //                playerTurn = 2;
    //                takeTurn(*player2, playerTurn);
    //            }
    //            firstTurn = false;
    //        }
    //        else
    //        {
    //            switch (playerTurn)
    //            {
    //            case 1:
    //                takeTurn(*player1, playerTurn);
    //                break;
    //            case 2:
    //                takeTurn(*player2, playerTurn);
    //                break;
    //            case 0:
    //                roundOver = true;
    //                break;
    //            default:
    //                std::cout << "There was an issue with the turn system..." << std::endl;
    //                break;
    //            }
    //        }
    //    }
    //    std::cout << std::endl;
    //    std::cout << std::endl;
    //    std::cout << "Round " << m_currentRound << " Complete" << std::endl;
    //    std::cout << std::endl;
    //    std::cout << std::endl;
    //    tallyPoints();
    //    m_currentRound++;
}

void KoiKoi::takeTurn(Player &currentPlayer, int &currentTurn) //pass by pointer and ref, no need to return values
{
    bool turnComplete {false};
    //Do Stuff
    while (turnComplete == false)
    {
        currentPlayer.printHand();
        //m_gameHand.printHand();
        std::this_thread::sleep_for(std::chrono::milliseconds(7000));
        //Call select card from hand
        //Call select card in game hand
        //compare cards
        //if they match, store in player's wonCards
        turnComplete = true;
    }
    switch (currentTurn)
    {
    case 1:
        //do stuff
        currentTurn = 2;
        break;
    case 2:
        //do stuff
        currentTurn = 1;
        break;
    case 0:
        std::cout << "There was an issue with the turn system..." << std::endl;
        break;
    default:
        std::cout << "There was an issue with the turn system..." << std::endl;
        break;
    }
}

bool KoiKoi::compareCards(Card card1, Card card2)
{
    std::cout << "Match: " << card1.getMonth() << std::endl;
    std::cout << "Match: " << card2.getMonth() << std::endl;
    return true;
}

void KoiKoi::tallyPoints() //??  Player currentPlayer, Player nextPlayer
{
    //Do stuff
}

void KoiKoi::printNumRounds()
{
    std::cout << "The number of rounds set for the current game are: " << m_rounds << std::endl;
}

void KoiKoi::printCurrentRound()
{
    std::cout << "The current round is: " << m_currentRound << std::endl;
}

void KoiKoi::printGameStatus()
{
    std::cout << "The game's current status is: " << m_gameStatus << std::endl;
}

void KoiKoi::showTitleScreen()
{
    ui->titleFrame->show();
    ui->gameFrame->setHidden(true);
    ui->oyaFrame->setHidden(true);
}

void KoiKoi::showGameScreen()
{
    ui->titleFrame->setHidden(true);
    ui->gameFrame->show();
    ui->oyaFrame->setHidden(true);
}

void KoiKoi::showOyaScreen()
{
    ui->titleFrame->setHidden(true);
    ui->gameFrame->setHidden(true);
    ui->oyaFrame->show();
}

void KoiKoi::updateCards()
{
    //******************************************
    //Update and show all dealt cards (not CPU)
    //******************************************

    Hand *playerHand = m_player1.getHand();
    Hand *cpuHand = m_player2.getHand();
    //Already have gameHand

    //*****************************************
    //Set ALL invisible and default deck style
    //OR ensure visible and update image
    //*****************************************

    for(int i{0};i<guiCPUCards.size();i++)
    {
        QPushButton *button = guiCPUCards.at(i);
        if (i>cpuHand->getNumCards()-1)
        {
            button->setVisible(false);
        }
        else {
            button->setVisible(true);
        }
    }

    for(int j{0};j<guiGameHandCards.size();j++)
    {
        QPushButton *button = guiGameHandCards.at(j);
        if (j>m_gameHand.getNumCards()-1)
        {
            button->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
            button->setVisible(false);
        }
        else {
            button->setIcon(QIcon(m_gameHand.getCard(j)->getImageStr()));
            button->setVisible(true);
        }
    }

    for(int k{0};k<guiPlayerCards.size();k++)
    {
        QPushButton *button = guiPlayerCards.at(k);
        if (k>playerHand->getNumCards()-1)
        {
            button->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
            button->setVisible(false);
        }
        else {
            button->setIcon(QIcon(playerHand->getCard(k)->getImageStr()));
            button->setVisible(true);
        }
    }
}

void KoiKoi::onNewGameClicked()
{
    //Create game
    startGame();
}

void KoiKoi::onQuitGameClicked()
{
    //Quit Game
    showTitleScreen();
}

void KoiKoi::onPreferencesClicked()
{
    //Open preferences dialog
    Preferences *prefs = new Preferences();
    prefs->setAttribute(Qt::WA_DeleteOnClose);
    prefs->show();
}

void KoiKoi::onAboutClicked()
{
    //Open about dialog
    About *about = new About();
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->show();
}
