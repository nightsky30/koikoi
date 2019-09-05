#include "game.h"
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <iostream>
#include <chrono>  // Sleep Time
#include <thread>  //Thread Sleep

using index_t = std::vector<Card>::size_type;

Game::Game()
{
    //Set up deck
    Deck m_gameDeck {Deck()};
    this->m_gameDeck.shuffleDeck();

    //Set up players and gameboard
    //Human
    Player m_player1 {Player()};
    //Comp
    Player m_player2 {Player()};
    //Game hand
    Hand m_gameHand {Hand()};

    //Set game variables
    this->m_rounds = 12;
    this->m_currentRound = 0;
    this->m_gameStatus = false;
}

Game::~Game()
{
}

void Game::clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

void Game::startGame()
{

    bool quitGame {false};
    char selection {'0'};

    while (quitGame == false)
    {
        clearScreen();
        std::cout << "  Koi-koi  " << std::endl;
        std::cout << " Game Menu " << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << std::endl;
        std::cout << "1) Determine Oya" << std::endl;
        std::cout << std::endl;
        std::cout << "2) Quit" << std::endl;
        std::cout << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << "Enter a selection: " << std::endl;
        std::cin >> selection;

        switch (selection)
        {
        case '1':
            //Start Game
            determineOya();
            startRound();
            break;
        case '2':
            quitGame = true;
            break;
        default:
            break;
        }
    }

}

void Game::determineOya()
{
//Ask human player to select 1 of 2 random cards
//Compare cards
//Earliest card is the Oya and has advantage of going first

    int oyaCard {0};
    Card c1 = m_gameDeck.getRandCard();
    Card c2 = m_gameDeck.getRandCard();

    //Ensure months are different to avoid issues
    if (c1.getMonth() == c2.getMonth())
    {
        while ((c1.getMonth() == c2.getMonth()))
        {
            c2 = m_gameDeck.getRandCard();
        }
    }

    //Determine Oya card
    if (c1.getMonth() < c2.getMonth())
    {
        oyaCard = 1;
    }
    else
    {
        oyaCard = 2;
    }

    //Start Player card selection
    bool madeSelection {false};
    char selection {'0'};

    while (madeSelection == false)
    {
        clearScreen();
        std::cout << "Determine Oya" << std::endl;
        std::cout << "=============" << std::endl;
        std::cout << "Player:  Please select a card, (1) or (2)" << std::endl;
        std::cout << std::endl;
        std::cin >> selection;

        switch (selection)
        {
        case '1':
        /* FALL THROUGH */
        case '2':
            madeSelection = true;
            break;
        default:
            std::cout << "Enter a proper selection..." << std::endl;
            //Sleep
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            break;
        }
    }

    clearScreen();
    std::cout << "Player has chosen: " << selection << std::endl;
    std::cout << std::endl;

    c1.printCard();
    c2.printCard();

    //Dirty trick to get the proper difference (int value) by using the ascii table
    if (((int)selection - '0') == oyaCard)
    {
        //Human has Oya
        m_player1.setOya(true);
        m_player2.setOya(false);
        std::cout << "Player is Oya!!!" << std::endl;
        std::cout << std::endl;
    }
    else
    {
        //CPU has Oya
        m_player1.setOya(false);
        m_player2.setOya(true);
        std::cout << "CPU is Oya!!!" << std::endl;
        std::cout << std::endl;
    }

    //Sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(7000));
}

void Game::deal()
{
    index_t maxDealt {m_gameDeck.getNumCards() / 2};
    index_t fourCount {0};

    Hand playHand1 {m_player1.getHand()};
    Hand playHand2 {m_player2.getHand()};

    for (fourCount = 0; fourCount < maxDealt - 1; fourCount = fourCount + 4)
    {
        for (int i {0}; i < 3; i++)
        {

        }
    }





//m_gameDeck
//m_player1
//m_player2
//m_gameHand


}

void Game::startRound()
{
//Do stuff
//Deal cards
    deal();
    takeTurn();
    takeTurn();
    takeTurn();
    takeTurn();
//Do stuff
    tallyPoints();
//Do stuff
}

void Game::takeTurn() //??  Player nextPlayer
{
    bool match {false};
    Card card1 {Card()};
    Card card2 {Card()};
//Do stuff
    match = compareCards(card1, card2);
    std::cout << "Match: " << match << std::endl;
}

bool Game::compareCards(Card card1, Card card2)
{
    std::cout << "Match: " << card1.getCardType() << std::endl;
    std::cout << "Match: " << card2.getCardType() << std::endl;
    return true;
}

void Game::tallyPoints() //??  Player currentPlayer, Player nextPlayer
{
//Do stuff
//Increment round
}

Deck Game::getDeck()
{
    return m_gameDeck;
}

Player Game::getPlayer(int playerNum)
{
    switch (playerNum)
    {
    case 1:
        return m_player1;
        break;
    case 2:
        return m_player2;
        break;
    default:
        std::cout << "Invalid player number. You must specify a value of 1 or 2. Returning player 1 by default." << std::endl;
        return m_player1;
        break;
    }
}

Hand Game::getGameHand()
{
    return m_gameHand;
}

int Game::getNumRounds()
{
    return m_rounds;
}

int Game::getCurrentRound()
{
    return m_currentRound;
}

bool Game::getGameStatus()
{
    return m_gameStatus;
}

void Game::printNumRounds()
{
    std::cout << "The number of rounds set for the current game are: " << m_rounds << std::endl;
}

void Game::printCurrentRound()
{
    std::cout << "The current round is: " << m_currentRound << std::endl;
}

void Game::printGameStatus()
{
    std::cout << "The game's current status is: " << m_gameStatus << std::endl;
}
