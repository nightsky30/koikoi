#include "card.h"
#include "deck.h"
#include <iostream>
#include <vector>

//Default Constructor
Deck::Deck()
{
    this->m_numCards = fullDeck;
    //Add function and function call to randomly generate deck
}

//Destructor
Deck::~Deck()
{
}

/*
* General Functions
*/
void Deck::dealCard()
{
    std::cout << "A card has been dealt" << std::endl;
    m_numCards = m_numCards - 1;
    std::cout << "The number of cards remaining in deck are: " << m_numCards << std::endl;
}

void Deck::shuffleDeck()
{
    std::cout << "The deck was shuffled" << std::endl;
}

Card Deck::getCard(std::vector<Card>::size_type cardNum)
{
    return m_cardDeck[cardNum];
}
