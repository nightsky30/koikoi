#include "hand.h"
#include "card.h"
#include <iostream>
#include <vector>

Hand::Hand()
{

}

Hand::~Hand()
{

}

std::vector<Card> Hand::getHand()
{
    return m_playerHand;
}

void Hand::viewHand()
{
    //For loop to print out hand info...
    std::cout << "The player's hand is: " << "" << std::endl;
}
