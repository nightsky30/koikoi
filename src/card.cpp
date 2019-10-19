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

#include "card.h"
#include <iostream>
#include <string>
#include <QString>

//Default Constructor
Card::Card()
{
    this->m_month = JANUARY;
    this->m_flower = PINE;
    this->m_imageStr = "Blank";
    this->m_cardType = PLAIN;
    this->m_cardType2 = PLAIN;
    this->m_pointVal = 5;
    this->m_pointVal2 = 5;
    this->m_name = "Card";
    this->m_wild = false;
}

//Constructor
Card::Card(CardMonth month, CardFlower flower, QString imageStr, CardType cardType, CardType cardType2, int pointVal, int pointVal2, std::string name, bool wild)
{
    this->m_month = month;
    this->m_flower = flower;
    this->m_imageStr = imageStr;
    this->m_cardType = cardType;
    this->m_cardType2 = cardType2;
    this->m_pointVal = pointVal;
    this->m_pointVal2 = pointVal2;
    this->m_name = name;
    this->m_wild = wild;
}

//Destructor
Card::~Card()
{
}

/*
* Get Functions
*/
CardMonth Card::getMonth()
{
    return m_month;
}

CardFlower Card::getFlower()
{
    return m_flower;
}

QString Card::getImageStr()
{
    return m_imageStr;
}

CardType Card::getCardType()
{
    return m_cardType;
}

CardType Card::getCardType2()
{
    return m_cardType2;
}

int Card::getPointVal()
{
    return m_pointVal;
}

int Card::getPointVal2()
{
    return m_pointVal2;
}

std::string Card::getName()
{
    return m_name;
}

bool Card::getWild()
{
    return m_wild;
}

std::string Card::determineCardType(CardType cType)
{
    std::string niceType {""};

    switch (cType)
    {
    case LIGHT:
        niceType = "LIGHT";
        break;
    case CRANE:
        niceType = "CRANE";
        break;
    case CURTAIN:
        niceType = "CURTAIN";
        break;
    case RAIN:
        niceType = "RAIN";
        break;
    case MOON:
        niceType = "MOON";
        break;
    case PHEONIX:
        niceType = "PHEONIX";
        break;
    case ANIMAL:
        niceType = "ANIMAL";
        break;
    case NIGHTINGALE:
        niceType = "NIGHTINGALE";
        break;
    case CUCKOO:
        niceType = "CUCKOO";
        break;
    case BRIDGE:
        niceType = "BRIDGE";
        break;
    case BUTTERFLIES:
        niceType = "BUTTERFLIES";
        break;
    case BOAR:
        niceType = "BOAR";
        break;
    case GEESE:
        niceType = "GEESE";
        break;
    case SAKE_CUP:
        niceType = "SAKE CUP";
        break;
    case DEER:
        niceType = "DEER";
        break;
    case SWALLOW:
        niceType = "SWALLOW";
        break;
    case RED_RIBBON:
        niceType = "RED RIBBON";
        break;
    case RED_POEM:
        niceType = "RED POEM";
        break;
    case BLUE_RIBBON:
        niceType = "BLUE RIBBON";
        break;
    case PLAIN:
        niceType = "PLAIN";
        break;
    case NIL:
        niceType = "NIL";
        break;
    default:
        std::cout << "The card type could not be determined." << std::endl;
        break;
    }
    return niceType;
}
