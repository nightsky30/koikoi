#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <iostream>
#include <vector>

class Hand
{

private:

    int numCards {8};
    std::vector<Card> m_playerHand
    {
        Card()
    };

public:

    Hand();
    ~Hand();
    std::vector<Card> getHand();
    void viewHand();

};

#endif
