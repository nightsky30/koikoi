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

#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>
#include <QVector>
#include <QString>

using index_t = std::vector<Card>::size_type;

/*
* Class Definition, also functions as forward declaration
*/
class Hand
{

private:
    /*
    * Member Initialization List
    */
    index_t m_numCards {0};
    std::vector<Card> m_playerHand
    {
        Card()
    };
    index_t m_oyaCard {0};

public:
    /*
    * Constructors / Destructors
    */
    Hand();
    ~Hand();

    /*
    * Get Functions
    */
    Card* getCard(std::vector<Card>::size_type cardNum);
    std::vector<Card>::size_type getNumCards();
    Card* getRandCard();
    index_t getOyaCard();

    /*
    * Set Functions
    */
    void setOyaCard(index_t oyaCard);
    void acceptCard(Card &newCard);
    Card* disCard(std::vector<Card>::size_type cardNum);
    void removeCard(std::vector<Card>::size_type cardNum);
    void resetHand();

    /*
    * Print Functions
    */
    void printHand();
};

#endif
