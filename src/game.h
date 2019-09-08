#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "hand.h"
#include "yaku.h"
#include "player.h"
#include <vector>

// The game consists of these yaku
const static std::vector<Yaku> acceptableYaku
{
    Yaku(1, "Kasu (Plains)", "10 Plain cards. 1 point. Each Additional 1P after."),
    Yaku(1, "Tanzaku (Ribbons)", "5 Ribbons. 1 point. Each Additional 1P after."),
    Yaku(1, "Tane (Animals)", "5 Animals. 1 point. Each Additional 1P after."),
    Yaku(5, "Ino-Shika-Cho (Boar-Deer-Butterflies)", "Animal cards of Clover, Maple, Peony. 5 points."),
    Yaku(6, "Akatan (Red Poetry Ribbons)", "All 3 red poetry ribbons. 6 points."),
    Yaku(6, "Aotan (Blue Ribbons)", "All 3 blue ribbons. 6 points."),
    Yaku(6, "Sanko (3Brights)", "3 Bright cards not containing Rain man card 6 points."),
    Yaku(8, "Ame-Shiko (Rain man)", "4Brights containing Rain man card. 8 points."),
    Yaku(10, "Shiko (4Brights)", "4 Bright cards not containing Rain man card 10 points."),
    Yaku(15, "Goko (5Brights)", "All 5 Bright cards. 15 points."),
    Yaku(4, "Tsuki-fuda (Monthly Cards)", "All four cards in one group shown right on screen. 4 points."),
    Yaku(6, "Oya-Ken (Dealer's Privilege)", "If neither gets any Yaku, Dealer wins 6 points."),
    Yaku(1, "Bake-Fuda (Wild Card)", "The animal card of Chrysanthemum can be regarded as a plain card as well. If you have this, 9 plain cards and this card will be the Yaku of Kasu.")
};

class Game
{

//Create deck
//Shuffle deck
//Create players
//Deal deck and create gameboard/hand and players' hands
//Set scores to 30 each
//Set rounds to 12
//Set current round to 0
//Set game over to false
//Loop while switching turns
//Implement each turn
//Tally points
//Wait for quit or game over to be true

private:

    Deck m_gameDeck {Deck()};
    Player m_player1 {Player()};
    Player m_player2 {Player()};
    Hand m_gameHand {Hand()};
    int m_rounds {12};
    int m_currentRound {0};
    bool m_gameStatus {false};

public:

    Game();
    ~Game();
    void clearScreen();
    void startGame();
    void determineOya();
    void deal();
    void startRound();
    void takeTurn(Player &currentPlayer, int &currentTurn);
    bool compareCards(Card card1, Card card2);
    void tallyPoints(); //??  Player currentPlayer, Player nextPlayer

    Deck getDeck();
    Player getPlayer(int playerNum);
    Hand getGameHand();
    int getNumRounds();
    int getCurrentRound();
    bool getGameStatus();

    void printNumRounds();
    void printCurrentRound();
    void printGameStatus();

};

#endif
