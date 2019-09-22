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
#include <QString>
#include <QPushButton>
#include <QIntegerForSize>
#include <QIcon>
#include <QThread>
#include <QPixmap>

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
    connect(ui->actionNew_Game, &QAction::triggered, this, &KoiKoi::onNewGameClicked, Qt::UniqueConnection);
    connect(ui->actionQuit_Game, &QAction::triggered, this, &KoiKoi::onQuitGameClicked, Qt::UniqueConnection);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close, Qt::UniqueConnection);
    connect(ui->actionPreferences, &QAction::triggered, this, &KoiKoi::onPreferencesClicked, Qt::UniqueConnection);
    connect(ui->actionAbout, &QAction::triggered, this, &KoiKoi::onAboutClicked, Qt::UniqueConnection);

    //Set up game cards defaults in GUI
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

    //Set up player yaku cards defaults in GUI
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

    //Set player yaku labels invisible
    ui->player_ameshiko_yaku->setVisible(false);
    ui->player_goku_yaku->setVisible(false);
    ui->player_sanko_yaku->setVisible(false);
    ui->player_shiko_yaku->setVisible(false);
    ui->player_inoshikacho_yaku->setVisible(false);
    ui->player_tane_yaku->setVisible(false);
    ui->player_akatan_yaku->setVisible(false);
    ui->player_aotan_yaku->setVisible(false);
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
    ui->cpu_inoshikacho_yaku->setVisible(false);
    ui->cpu_tane_yaku->setVisible(false);
    ui->cpu_akatan_yaku->setVisible(false);
    ui->cpu_aotan_yaku->setVisible(false);
    ui->cpu_tanzaku_yaku->setVisible(false);
    ui->cpu_bake_fuda_yaku->setVisible(false);
    ui->cpu_kasu_yaku->setVisible(false);
    ui->cpu_oya_ken_yaku->setVisible(false);
    ui->cpu_tsuki_fuda_yaku->setVisible(false);

    connect(ui->oyaButton_0, SIGNAL (released()), this, SLOT(determineOyaPlayer()), Qt::UniqueConnection);
    connect(ui->oyaButton_1, SIGNAL (released()), this, SLOT(determineOyaPlayer()), Qt::UniqueConnection);

    showTitleScreen();
}

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
 */
void KoiKoi::startGame()
{
    this->m_player1.getHand()->resetHand();
    this->m_player2.getHand()->resetHand();
    this->m_player1.getLightMatch()->resetHand();
    this->m_player1.getAnimalMatch()->resetHand();
    this->m_player1.getRibbonMatch()->resetHand();
    this->m_player1.getPlainMatch()->resetHand();
    this->m_player2.getLightMatch()->resetHand();
    this->m_player2.getAnimalMatch()->resetHand();
    this->m_player2.getRibbonMatch()->resetHand();
    this->m_player2.getPlainMatch()->resetHand();
    this->m_gameHand.resetHand();
    this->m_gameDeck.resetDeck();
    this->m_gameDeck.shuffleDeck();
    this->m_oyaHand.resetHand();
    generateOyaCard();
}

/*
 * Generates a random 2 card hand used by players to determine
 * who is the oya player and takes first turn.  It then compares
 * card months and sets the variable within the hand to indicate
 * which card is the oya card.
 */
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

/*
 * Deals hands for both players as well as the gameboard.
 */
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

/*
 * Starts a round.
 */
void KoiKoi::startRound()
{
    //startTurn
    deal();
    updateYaku();
    updateCards();
    showGameScreen();
    checkGameHand();

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

//void KoiKoi::matchCard(Player &currentPlayer, int &currentTurn) //pass by pointer and ref, no need to return values
//{
//    bool turnComplete {false};
//    //Do Stuff
//    while (turnComplete == false)
//    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(7000));
//        //Call select card from hand
//        //Call select card in game hand
//        //compare cards
//        //if they match, store in player's wonCards
//        turnComplete = true;
//    }
//    switch (currentTurn)
//    {
//    case 1:
//        //do stuff
//        currentTurn = 2;
//        break;
//    case 2:
//        //do stuff
//        currentTurn = 1;
//        break;
//    case 0:
//        std::cout << "There was an issue with the turn system..." << std::endl;
//        break;
//    default:
//        std::cout << "There was an issue with the turn system..." << std::endl;
//        break;
//    }
//}

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
    //Already have deck

    //***********************************************************
    //Set ALL invisible, default deck style
    //OR ensure visible, update image
    //
    //This is kept separate from connections and disconnections
    //***********************************************************

    for(int i{0};i<guiCPUCards.size();i++)
    {
        QPushButton *button = guiCPUCards.at(i);
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

    //Iterate like update cards...

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

    //    if (yaku)
    //    {
    //        //Set player yaku labels visible
    //        ui->player_ameshiko_yaku->setVisible(true);
    //        ui->player_goku_yaku->setVisible(true);
    //        ui->player_sanko_yaku->setVisible(true);
    //        ui->player_shiko_yaku->setVisible(true);
    //        ui->player_inoshikacho_yaku->setVisible(true);
    //        ui->player_tane_yaku->setVisible(true);
    //        ui->player_akatan_yaku->setVisible(true);
    //        ui->player_aotan_yaku->setVisible(true);
    //        ui->player_tanzaku_yaku->setVisible(true);
    //        ui->player_bake_fuda_yaku->setVisible(true);
    //        ui->player_kasu_yaku->setVisible(true);
    //        ui->player_oya_ken_yaku->setVisible(true);
    //        ui->player_tsuki_fuda_yaku->setVisible(true);

    //        //Set cpu yaku labels visible
    //        ui->cpu_ameshiko_yaku->setVisible(true);
    //        ui->cpu_goku_yaku->setVisible(true);
    //        ui->cpu_sanko_yaku->setVisible(true);
    //        ui->cpu_shiko_yaku->setVisible(true);
    //        ui->cpu_inoshikacho_yaku->setVisible(true);
    //        ui->cpu_tane_yaku->setVisible(true);
    //        ui->cpu_akatan_yaku->setVisible(true);
    //        ui->cpu_aotan_yaku->setVisible(true);
    //        ui->cpu_tanzaku_yaku->setVisible(true);
    //        ui->cpu_bake_fuda_yaku->setVisible(true);
    //        ui->cpu_kasu_yaku->setVisible(true);
    //        ui->cpu_oya_ken_yaku->setVisible(true);
    //        ui->cpu_tsuki_fuda_yaku->setVisible(true);
    //    }

}

/*
 * Function checks game hand for matching cards in the current player's hand.
 * Enables cards corresponding buttons that match while disabling the buttons
 * for cards that do not match.
 */
void KoiKoi::checkGameHand()
{
    Hand *playerHand = m_player1.getHand();
    Hand *cpuHand = m_player2.getHand();
    //Already have gameHand
    Card *currentGameCard;
    Card *currentPlayerCard;
    QPushButton *currentGameButton;

    //For each game card
    for(int i{0};i<m_gameHand.getNumCards();i++)
    {
        //Get game card
        currentGameCard = m_gameHand.getCard(i);
        //Get game button
        currentGameButton = guiGameHandCards.at(i);
        //Disable gui game button
        currentGameButton->setDisabled(true);
        //Compare to each card in player hand
        for(int j{0};j<playerHand->getNumCards();j++)
        {
            currentPlayerCard = playerHand->getCard(j);
            if(currentGameCard->getMonth() == currentPlayerCard->getMonth())
            {
                currentGameButton->setDisabled(false);
            }
        }
    }
    //Connect player hand cards to enable selection
    connectPlayerHand();
    disconnectDeck();
}

void KoiKoi::connectDeck()
{
    connect(ui->deckButton, SIGNAL(released()), this, SLOT(drawCard()), Qt::UniqueConnection);
}

void KoiKoi::connectGameHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    connect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()), Qt::UniqueConnection);
}

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

void KoiKoi::connectPlayerHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    connect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()), Qt::UniqueConnection);
}

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

void KoiKoi::disconnectDeck()
{
    disconnect(ui->deckButton, SIGNAL(released()), this, SLOT(drawCard()));
}

void KoiKoi::disconnectGameHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()));
}

void KoiKoi::disconnectGameHand()
{
    for(int j{0};j<guiGameHandCards.size();j++)
    {
        QPushButton *currentButton = guiGameHandCards.at(j);
        disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromGameHand()));
    }
}

void KoiKoi::disconnectPlayerHand(QPushButton *button)
{
    QPushButton *currentButton = button;
    disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()));
}

void KoiKoi::disconnectPlayerHand()
{
    for(int k{0};k<guiPlayerCards.size();k++)
    {
        QPushButton *currentButton = guiPlayerCards.at(k);
        disconnect(currentButton, SIGNAL(released()), this, SLOT(selectFromHand()));
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

void KoiKoi::determineOyaPlayer()
{
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();

    index_t oyaCard = m_oyaHand.getOyaCard();
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
    startRound();//deal and showGameScreen in startRound
}

void KoiKoi::selectFromHand()
{
    Hand *playerHand = m_player1.getHand();
    Hand *cpuHand = m_player2.getHand();

    //get calling parent object name
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();
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

        //disconnect all playerhand cards
        disconnectPlayerHand();
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
        //Disconnect player hand
        disconnectPlayerHand();
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

void KoiKoi::selectFromGameHand()
{
    /*
     * Could match from deck or player hand.
     * Check both.
     */
    //get calling parent object name
    QObject *senderButton = sender();
    QString buttonName = senderButton->objectName();
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
        //connect all playerhand cards
        connectPlayerHand();
        //disconnect all game hand cards
        disconnectGameHand();
        //disconnect deck
        disconnectDeck();
        //call updateCards
        updateCards();
        //call updatePlayerYaku
        updateYaku();
        ui->deckButton->setIcon(QIcon(QString(":/deck/Hanafuda_koi-2.svg")));
        m_gameDeck.setDeckIcon(":/deck/Hanafuda_koi-2.svg");
        checkGameHand();
        //**********************************************************
        //allows to click player hand card to call selectFromHand
        //**********************************************************
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
        //disconnect all game hand cards
        disconnectGameHand();
        //connect deck
        connectDeck();
        //call updateCards
        updateCards();
        //call updatePlayerYaku
        updateYaku();
        //***************************************
        //allows to click deck to call drawCard
        //***************************************
    }
    //check for yaku
    //if yaku
    //then request koikoi
    //if koikoi
    //then finish turn
    //else finish round
}

//void KoiKoi::drawCard(Player &currentPlayer, int &currentTurn) //pass by pointer and ref, no need to return values
void KoiKoi::drawCard()
{
    //Shows next card for deck
    //Connects button
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
        //Connect playerhand
        connectPlayerHand();
        //call updateCards
        updateCards();
        checkGameHand();
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
    disconnectDeck();
}
