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

#ifndef CARD_H
#define CARD_H

#include <string>
#include <QString>
#include <QLabel>

/*
* Month Values
* ============
* 0 - 12
*/
enum CardMonth
{
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

/*
* Flower Values
* =============
* 0 - 12
*/
enum CardFlower
{
    PINE,
    PLUM_BLOSSOMS,
    CHERRY_BLOSSOMS,
    WISTERIA,
    IRIS,
    PEONY,
    CLOVER,
    PAMPAS,
    CHRYSANTHEMUM,
    MAPLE,
    WILLOW,
    PAULOWNIA
};

/*
* General Card Types
* ==================
* Light     =       0-5
* Animal    =       6-15
* Ribbon    =       16-19
* Plain     =       20
* Nil       =       21
*/
enum CardType
{
    LIGHT,
    CRANE,
    CURTAIN,
    RAIN,
    MOON,
    PHEONIX,
    ANIMAL,
    NIGHTINGALE,
    CUCKOO,
    BRIDGE,
    BUTTERFLIES,
    BOAR,
    GEESE,
    SAKE_CUP, //Wild, can also be plain for 10 Kasu Yaku
    DEER,
    SWALLOW,
    RIBBON,
    RED_RIBBON,
    RED_POEM,
    BLUE_RIBBON,
    PLAIN,
    NIL
};

/*
* Class Definition, also functions as forward declaration
*/
class Card
{

private:
    /*
    * Member Initialization List
    */
    CardMonth m_month {JANUARY};
    CardFlower m_flower {PINE};
    QString m_imageStr {":/deck/Hanafuda_koi-2.svg"};
    CardType m_cardType {PLAIN};
    CardType m_cardType2 {NIL};
    int m_pointVal {5};
    int m_pointVal2 {5};
    std::string m_name {"Card"};
    bool m_wild {false};

public:
    /*
    * Constructors / Destructors
    */
    Card();
    Card(CardMonth month, CardFlower flower, QString imageStr, CardType cardType, CardType cardType2, int pointVal, int pointVal2, std::string name, bool wild);
    ~Card();

    /*
    * Get Functions
    */
    CardMonth getMonth();
    CardFlower getFlower();
    QString getImageStr();
    CardType getCardType();
    CardType getCardType2();
    int getPointVal();
    int getPointVal2();
    std::string getName();
    bool getWild();
    std::string determineCardType(CardType cType);

    /*
    * Print Functions
    */
    void printCard();
    void printMonth();
    void printFlower();
    void printImageStr();
    void printCardType();
    void printCardType2();
    void printPointVal();
    void printPointVal2();
    void printName();
    void printWild();
};

#endif
