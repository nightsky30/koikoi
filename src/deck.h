#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

// The game consists of this deck of 48 cards
constexpr static int fullDeck {48};

// Deck of 48 cards listed by point value by month
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

/*
* Class Definition, also functions as forward declaration
*/
class Deck
{

private:

    /*
    * Member Initialization List
    */
    std::vector<Card>::size_type m_numCards {fullDeck};
    std::vector<Card> m_cardDeck {koikoiDeck};

public:

    /*
    * Constructors / Destructors
    */
    Deck();
    ~Deck();

    /*
    * General Functions
    */
    void shuffleDeck();
    void printDeck();
    Card getCard(std::vector<Card>::size_type cardNum);
    std::vector<Card>::size_type getNumCards();
    Card getRandCard();
    Card dealCard();

};

#endif
