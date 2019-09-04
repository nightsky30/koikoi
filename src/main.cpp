#include "game.h"
#include "Test.h"
#include <iostream>

/*
* Main Function
*/
int main()
{

// Create windows and components / menus
// Wait for user input
// Create / Start game
// Run thru game
// Finish Game
// Reenter menu and wait for user input again
// Exit

    bool quitApp {false};
    char selection {'0'};

    while (quitApp == false)
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "  Koi-koi  " << std::endl;
        std::cout << " Main Menu " << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << std::endl;
        std::cout << "1) Start Game" << std::endl;
        std::cout << std::endl;
        std::cout << "2) Quit" << std::endl;
        std::cout << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << std::endl;
        std::cout << "0) Debug" << std::endl;
        std::cout << std::endl;
        std::cout << "===========" << std::endl;
        std::cout << "Enter a selection: " << std::endl;
        std::cin >> selection;

        switch (selection)
        {
        case '1':
        {
            //Create game
            Game newGame {Game()};
            newGame.startGame();
        }
        break;
        case '2':
            quitApp = true;
            break;
        case '0':
        {
            Test newTest {Test()};
            newTest.startDebug();
        }
        break;
        default:
            break;
        }
    }

    std::cout << "\033[2J\033[1;1H";
    std::cout << "Thank you for playing!!!" << std::endl;

    return 0;
}
