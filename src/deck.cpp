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

#include "deck.h"
#include "card.h"
#include <iostream>     /* cout, cin, endl */
#include <QVector>
#include <cstdio>      /* NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

//Default Constructor
Deck::Deck()
{
    //Ensure deck starts with proper number of cards (48)
    this->m_numCards = fullDeck;
    //Assign standard game deck
    this->m_cardDeck = koikoiDeck;
}

//Destructor
Deck::~Deck()
{
}

Card* Deck::getCard(int cardNum)
{
    Card *requestedCard;
    requestedCard = &m_cardDeck[cardNum];
    return requestedCard;
}

int Deck::getNumCards()
{
    return m_numCards;
}

Card* Deck::getRandCard() // Caution: Does not remove card from deck...
{
    int randNum {0};
    randNum = static_cast<int>(std::rand() % m_numCards);
    Card *requestedCard;
    requestedCard = &m_cardDeck[randNum];
    return requestedCard;
}

std::string Deck::getDeckIcon()
{
    return m_deckIcon;
}

void Deck::resetDeck()
{
    //Ensure deck starts with proper number of cards (48)
    this->m_numCards = fullDeck;
    //Assign standard game deck
    this->m_cardDeck = koikoiDeck;
}

/*
* General Functions
*/
void Deck::shuffleDeck()
{

    int i {0};
    int r {0};

    for (i = 0; i < m_numCards; i++)
    {
        //Generate a random number to select a card in the deck
        r = static_cast<int>(std::rand() % m_numCards);
        //Swap the current card number being iterated through with the randomly picked card
        std::swap(m_cardDeck[i], m_cardDeck[r]);
    }
    std::cout << "=====================" << std::endl;
    std::cout << "The deck was shuffled" << std::endl;
    std::cout << "=====================" << std::endl;
}

Card* Deck::dealCard()
{
    //when a card is dealt, create a temp card object
    //remove it from the deck
    //it should go into the player's hand or the gamehand.
    //when removed from the deck and either cardNum decremented, or just use vector.size.
    //when cards are matched they should go to an alternate "match hand" to be tallied later.
    //Implement this system...

    Card *tempCard;
    tempCard = &m_cardDeck[m_numCards-1];
    m_cardDeck.pop_back();
    m_numCards--;
    return tempCard;
}

void Deck::setDeckIcon(std::string iconStr)
{
    m_deckIcon = iconStr;
}

