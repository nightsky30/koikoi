/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Koi-Koi Hanafuda - Card Game
 * Copyright (C) 2019  nightsky30 @ github
 */

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
    m_playerHand.push_back(newCard);
    m_numCards = m_numCards + 1;
}

void Hand::removeCard(std::vector<Card>::size_type cardNum)
{
        m_playerHand.erase(m_playerHand.begin() + cardNum);
        m_numCards = m_numCards - 1;
}

void Hand::resetHand()
{
    this->m_numCards = 0;
    this->m_playerHand.resize(0);
    this->m_oyaCard = 0;
}

void Hand::printHand()
{
    using index_t = std::vector<Card>::size_type;

    index_t i {0};

    for (i = 0; i < m_numCards; i++)
    {
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
