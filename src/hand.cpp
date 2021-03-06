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
#include <QVector>

Hand::Hand()
{
    this->m_numCards = 0;
    this->m_playerHand.resize(0);
    this->m_oyaCard = 0;
}

Hand::~Hand()
{

}

Card* Hand::getCard(int cardNum)
{
    Card *requestedCard;
    requestedCard = &m_playerHand[cardNum];
    return requestedCard;
}

int Hand::getNumCards()
{
    return m_numCards;
}

Card* Hand::getRandCard()
{
    int randNum {0};
    randNum = static_cast<int>(std::rand() % m_numCards);
    Card *requestedCard;
    requestedCard = &m_playerHand[randNum];
    return requestedCard;
}

int Hand::getOyaCard()
{
return m_oyaCard;
}

void Hand::setOyaCard(int oyaCard)
{
    m_oyaCard = oyaCard;
}

void Hand::acceptCard(Card &newCard)
{
    m_playerHand.push_back(newCard);
    m_numCards = m_numCards + 1;
}

void Hand::removeCard(int cardNum)
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
