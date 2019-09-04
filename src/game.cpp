#include "game.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include <iostream>

Game::Game()
{
    //Set up deck
    Deck m_gameDeck {Deck()};
    this->m_gameDeck.shuffleDeck();

    //Set up players and gameboard
    Player m_player1 {Player()};
    Player m_player2 {Player()};
    Hand m_gameHand {Hand()};

    //Set game variables
    this->m_rounds = 12;
    this->m_currentRound = 0;
    this->m_gameStatus = false;
}

Game::~Game()
{
}

void Game::startGame()
{

    bool quitGame {false};
    char selection {'0'};

    while (quitGame == false)
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "  Koi-koi  " << std::endl;
        std::cout << " Game Menu " << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << std::endl;
        std::cout << "1) Start Round: " << std::endl;
        std::cout << std::endl;
        std::cout << "2) Quit" << std::endl;
        std::cout << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << "Enter a selection: " << std::endl;
        std::cin >> selection;

        switch (selection)
        {
        case '1':
            //Start round
            this->startRound();
            break;
        case '2':
            quitGame = true;
            break;
        default:
            break;
        }
    }

}

void Game::startRound()
{
//Do stuff
    this->takeTurn();
    this->takeTurn();
    this->takeTurn();
    this->takeTurn();
//Do stuff
    this->tallyPoints();
//Do stuff
}

void Game::takeTurn() //??  Player nextPlayer
{
//Do stuff
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
