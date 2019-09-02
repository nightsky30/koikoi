#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

constexpr static int fullDeck {48};

/*
* Class Definition, also functions as forward declaration
*/
class Deck
{

public:

    /*
    * Constructors / Destructors
    */
    Deck();
    ~Deck();

    /*
    * General Functions
    */
    void dealCard();
    void shuffleDeck();
    Card getCard(std::vector<Card>::size_type cardNum);

private:

    /*
    * Member Initialization List
    */
    int m_numCards {fullDeck};
    // Deck can be instantiated with 48 cards in random order
    std::vector<Card> m_cardDeck
    {
        Card()
    };

};

#endif
