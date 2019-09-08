#include "hand.h"
#include "card.h"
#include <iostream>
#include <vector>

using index_t = std::vector<Card>::size_type;

Hand::Hand()
{
    this->m_numCards = 0;
    this->m_playerHand.resize(0);
}

Hand::~Hand()
{

}

void Hand::printHand()
{
    using index_t = std::vector<Card>::size_type;

    index_t i {0};

    for (i = 0; i < m_numCards; i++)
    {
        //Print
        std::cout << "=========================" << std::endl;
        std::cout << "Information for card " << (i + 1) << ":" << std::endl;
        std::cout << "=========================" << std::endl;
        m_playerHand[i].printMonth();
        m_playerHand[i].printFlower();
        m_playerHand[i].printCardType();
        m_playerHand[i].printCardType2();
        m_playerHand[i].printPointVal();
        m_playerHand[i].printPointVal2();
        m_playerHand[i].printName();
        m_playerHand[i].printWild();
        std::cout << "=========================" << std::endl;
    }
}

Card* Hand::getCard(std::vector<Card>::size_type cardNum)
{
    Card *requestedCard;
    requestedCard = &m_playerHand[cardNum];
    return requestedCard;
}

std::vector<Card>::size_type Hand::getNumCards()
{
    return m_numCards;
}

Card* Hand::getRandCard()
{
    index_t randNum {0};
    srand(time(NULL));
    randNum = ((index_t)std::rand() % (m_numCards-1));
    Card *requestedCard;
    requestedCard = &m_playerHand[randNum];
    return requestedCard;
}

void Hand::acceptCard(Card &newCard)
{
    m_playerHand.push_back(newCard);
    m_numCards++;
}

Card* Hand::disCard(std::vector<Card>::size_type cardNum)
{
//create a card pointer
//remove the card from the hand's vector or cards
//decrement numCards
//return card pointer to be placed on the game hand or in the players played cards

    std::cout << "A card has been dealt" << std::endl;
    m_numCards = m_numCards - 1;
    std::cout << "The number of cards remaining in hand are: " << m_numCards << std::endl;
    Card *requestedCard;
    requestedCard = &m_playerHand[cardNum];
    return requestedCard;
}
