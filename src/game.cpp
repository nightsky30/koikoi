#include "game.h"

Game::Game()
{

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
        std::cout << "1) Start Round" << std::endl;
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
//Do stuff
}

void Game::takeTurn() //??  Player nextPlayer
{
//Do stuff
    this->tallyPoints();
//Do stuff
}

void Game::tallyPoints() //??  Player currentPlayer, Player nextPlayer
{
//Do stuff
}
