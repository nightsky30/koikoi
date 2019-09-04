#include "Test.h"
#include "game.h"
#include "card.h"
#include "deck.h"
#include "yaku.h"
#include "hand.h"
#include "player.h"
#include <iostream>

Test::Test()
{
    //ctor
}

Test::~Test()
{
    //dtor
}

void Test::startDebug()
{
    bool quitDebug {false};
    char selection {'0'};

    std::cout << "\033[2J\033[1;1H";
    while (quitDebug == false)
    {
        std::cout << "  Koi-koi  " << std::endl;
        std::cout << " Debug Menu " << std::endl;
        std::cout << "============" << std::endl;
        std::cout << std::endl;
        std::cout << "1) Run Test" << std::endl;
        std::cout << std::endl;
        std::cout << "2) Quit" << std::endl;
        std::cout << std::endl;
        std::cout << "============" << std::endl;
        std::cout << "Enter a selection or hit Enter: " << std::endl;
        std::cin >> selection;

        switch (selection)
        {
        case '1':
            debugTest();
            break;
        case '2':
            quitDebug = true;
            break;
        default:
            break;
        }
    }
}

void Test::debugTest()
{
// Game
    Game myGame {Game()};

    myGame.printNumRounds();
    myGame.printCurrentRound();
    myGame.printGameStatus();

// Card
    Card myCard {Card()};

    myCard.printMonth();
    myCard.printFlower();
    myCard.printCardType();
    myCard.printCardType2();
    myCard.printPointVal();
    myCard.printPointVal2();
    myCard.printName();
    myCard.printWild();

// Deck
    Deck myDeck {Deck()};

    myDeck.shuffleDeck();
    myDeck.printDeck();

// Yaku
    Yaku myYaku {Yaku()};



// Hand
    Hand myHand {Hand()};



// Player
    Player myPlayer {Player()};



}
