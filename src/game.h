#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "yaku.h"
#include "deck.h"
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

// The game consists of this deck of 48 cards
// Deck can be instantiated with 48 cards in random order
const static std::vector<Card> koikoiDeck
{
    Card(JANUARY, PINE, LIGHT, CRANE, 20, 0, "Crane", false),
    Card(JANUARY, PINE, RED_RIBBON, RED_POEM, 5, 0, "Red Poem Tanzaku", false),
    Card(JANUARY, PINE, PLAIN, NIL, 1, 0, "Plain", false),
    Card(JANUARY, PINE, PLAIN, NIL, 1, 0, "Plain", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, ANIMAL, NIGHTINGALE, 10, 0, "Nightingale", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, RED_RIBBON, RED_POEM, 5, 0, "Red Poem Tanzaku", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(MARCH, CHERRY_BLOSSOMS, LIGHT, CURTAIN, 20, 0, "Curtain", false),
    Card(MARCH, CHERRY_BLOSSOMS, RED_RIBBON, RED_POEM, 5, 0, "Red Poem Tanzaku", false),
    Card(MARCH, CHERRY_BLOSSOMS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(MARCH, CHERRY_BLOSSOMS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(APRIL, WISTERIA, ANIMAL, CUCKOO, 10, 0, "Cuckoo", false),
    Card(APRIL, WISTERIA, RED_RIBBON, NIL, 5, 0, "Red Tanzaku", false),
    Card(APRIL, WISTERIA, PLAIN, NIL, 1, 0, "Plain", false),
    Card(APRIL, WISTERIA, PLAIN, NIL, 1, 0, "Plain", false),
    Card(MAY, IRIS, ANIMAL, BRIDGE, 10, 0, "Bridge", false),
    Card(MAY, IRIS, RED_RIBBON, NIL, 5, 0, "Red Tanzaku", false),
    Card(MAY, IRIS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(MAY, IRIS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(JUNE, PEONY, ANIMAL, BUTTERFLIES, 10, 0, "Butterflies", false),
    Card(JUNE, PEONY, BLUE_RIBBON, NIL, 5, 0, "Blue Tanzaku", false),
    Card(JUNE, PEONY, PLAIN, NIL, 1, 0, "Plain", false),
    Card(JUNE, PEONY, PLAIN, NIL, 1, 0, "Plain", false),
    Card(JULY, CLOVER, ANIMAL, BOAR, 10, 0, "Boar", false),
    Card(JULY, CLOVER, RED_RIBBON, NIL, 5, 0, "Red Tanzaku", false),
    Card(JULY, CLOVER, PLAIN, NIL, 1, 0, "Plain", false),
    Card(JULY, CLOVER, PLAIN, NIL, 1, 0, "Plain", false),
    Card(AUGUST, PAMPAS, LIGHT, MOON, 20, 0, "Moon", false),
    Card(AUGUST, PAMPAS, ANIMAL, GEESE, 10, 0, "Geese", false),
    Card(AUGUST, PAMPAS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(AUGUST, PAMPAS, PLAIN, NIL, 1, 0, "Plain", false),
    Card(SEPTEMBER, CHRYSANTHEMUM, ANIMAL, SAKE_CUP, 10, 0, "Sake Cup", true),
    Card(SEPTEMBER, CHRYSANTHEMUM, BLUE_RIBBON, NIL, 5, 0, "Blue Tanzaku", false),
    Card(SEPTEMBER, CHRYSANTHEMUM, PLAIN, NIL, 1, 0, "Plain", false),
    Card(SEPTEMBER, CHRYSANTHEMUM, PLAIN, NIL, 1, 0, "Plain", false),
    Card(OCTOBER, MAPLE, ANIMAL, DEER, 10, 0, "Deer", false),
    Card(OCTOBER, MAPLE, BLUE_RIBBON, NIL, 5, 0, "Blue Tanzaku", false),
    Card(OCTOBER, MAPLE, PLAIN, NIL, 1, 0, "Plain", false),
    Card(OCTOBER, MAPLE, PLAIN, NIL, 1, 0, "Plain", false),
    Card(NOVEMBER, WILLOW, LIGHT, RAIN, 20, 0, "Rain", false),
    Card(NOVEMBER, WILLOW, ANIMAL, SWALLOW, 10, 0, "Swallow", false),
    Card(NOVEMBER, WILLOW, RED_RIBBON, NIL, 5, 0, "Red Tanzaku", false),
    Card(NOVEMBER, WILLOW, PLAIN, NIL, 1, 0, "Plain", false),
    Card(DECEMBER, PAULOWNIA, LIGHT, PHEONIX, 20, 0, "Pheonix", false),
    Card(DECEMBER, PAULOWNIA, PLAIN, NIL, 1, 0, "Plain", false),
    Card(DECEMBER, PAULOWNIA, PLAIN, NIL, 1, 0, "Plain", false),
    Card(DECEMBER, PAULOWNIA, PLAIN, NIL, 1, 0, "Plain", false)
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
    Hand m_gameboard {Hand()};
    int m_rounds {12};
    int m_currentRound {0};
    bool m_gameOver {false};

public:

Game();
~Game();
void startGame();
void startRound();
void takeTurn(); //??  Player nextPlayer
void tallyPoints(); //??  Player currentPlayer, Player nextPlayer

};

#endif
