#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <iostream>
#include <vector>

class Hand
{

private:

    std::vector<Card>::size_type m_numCards {0};
    std::vector<Card> m_playerHand
    {
        Card()
    };

public:

    Hand();
    ~Hand();
    void printHand();
    Card getCard(std::vector<Card>::size_type cardNum);
    std::vector<Card>::size_type getNumCards();
    Card getRandCard();
    void acceptCard(Card newCard);
    Card disCard(std::vector<Card>::size_type cardNum);

};

#endif
