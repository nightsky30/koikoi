#include "hand.h"
#include "card.h"
#include <iostream>
#include <vector>

using index_t = std::vector<Card>::size_type;

Hand::Hand()
{
    this->m_numCards = 0;
    this->m_playerHand.resize(0);
    this->m_oyaCard = 0;
    this->m_handLabels.resize(0);
}

Hand::~Hand()
{

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

//QLabel* getLabel()
//{

//}

index_t Hand::getOyaCard()
{
return m_oyaCard;
}

void Hand::setOyaCard(index_t oyaCard)
{
    m_oyaCard = oyaCard;
}

void Hand::acceptCard(Card &newCard)
{
    //modify to accept label??...card has label string...but hand has label object
    m_playerHand.push_back(newCard);
    m_numCards = m_numCards + 1;
}

void Hand::removeCard(std::vector<Card>::size_type cardNum)
{
        //modify to accept label??...card has label string...but hand has label object
        //m_playerHand.erase(m_playerHand.begin() + cardNum);
        m_playerHand.erase(m_playerHand.begin()+cardNum);
        m_numCards = m_numCards - 1;
}

void Hand::resetHand()
{
    this->m_numCards = 0;
    this->m_playerHand.resize(0);
    this->m_oyaCard = 0;
    this->m_handLabels.resize(0);
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
        m_playerHand[i].printImageStr();
        m_playerHand[i].printCardType();
        m_playerHand[i].printCardType2();
        m_playerHand[i].printPointVal();
        m_playerHand[i].printPointVal2();
        m_playerHand[i].printName();
        m_playerHand[i].printWild();
        std::cout << "=========================" << std::endl;
    }
}
