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

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <string>

// The game consists of this deck of 48 cards
constexpr static int fullDeck {48};

// Deck of 48 cards listed by point value by month
const static std::vector<Card> koikoiDeck
{
    Card(JANUARY, PINE, ":/deck/Hanafuda_1-4.svg", LIGHT, CRANE, 20, 0, "Crane", false),
    Card(JANUARY, PINE, ":/deck/Hanafuda_1-3.svg", RIBBON, RED_POEM, 5, 0, "Red Poem Tanzaku", false),
    Card(JANUARY, PINE, ":/deck/Hanafuda_1-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(JANUARY, PINE, ":/deck/Hanafuda_1-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, ":/deck/Hanafuda_2-4.svg", ANIMAL, NIGHTINGALE, 10, 0, "Nightingale", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, ":/deck/Hanafuda_2-3.svg", RIBBON, RED_POEM, 5, 0, "Red Poem Tanzaku", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, ":/deck/Hanafuda_2-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(FEBRUARY, PLUM_BLOSSOMS, ":/deck/Hanafuda_2-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(MARCH, CHERRY_BLOSSOMS, ":/deck/Hanafuda_3-4.svg", LIGHT, CURTAIN, 20, 0, "Curtain", false),
    Card(MARCH, CHERRY_BLOSSOMS, ":/deck/Hanafuda_3-3.svg", RIBBON, RED_POEM, 5, 0, "Red Poem Tanzaku", false),
    Card(MARCH, CHERRY_BLOSSOMS, ":/deck/Hanafuda_3-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(MARCH, CHERRY_BLOSSOMS, ":/deck/Hanafuda_3-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(APRIL, WISTERIA, ":/deck/Hanafuda_4-4.svg", ANIMAL, CUCKOO, 10, 0, "Cuckoo", false),
    Card(APRIL, WISTERIA, ":/deck/Hanafuda_4-3.svg", RIBBON, RED_RIBBON, 5, 0, "Red Tanzaku", false),
    Card(APRIL, WISTERIA, ":/deck/Hanafuda_4-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(APRIL, WISTERIA, ":/deck/Hanafuda_4-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(MAY, IRIS, ":/deck/Hanafuda_5-4.svg", ANIMAL, BRIDGE, 10, 0, "Bridge", false),
    Card(MAY, IRIS, ":/deck/Hanafuda_5-3.svg", RIBBON, RED_RIBBON, 5, 0, "Red Tanzaku", false),
    Card(MAY, IRIS, ":/deck/Hanafuda_5-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(MAY, IRIS, ":/deck/Hanafuda_5-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(JUNE, PEONY, ":/deck/Hanafuda_6-4.svg", ANIMAL, BUTTERFLIES, 10, 0, "Butterflies", false),
    Card(JUNE, PEONY, ":/deck/Hanafuda_6-3.svg", RIBBON, BLUE_RIBBON, 5, 0, "Blue Tanzaku", false),
    Card(JUNE, PEONY, ":/deck/Hanafuda_6-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(JUNE, PEONY, ":/deck/Hanafuda_6-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(JULY, CLOVER, ":/deck/Hanafuda_7-4.svg", ANIMAL, BOAR, 10, 0, "Boar", false),
    Card(JULY, CLOVER, ":/deck/Hanafuda_7-3.svg", RIBBON, RED_RIBBON, 5, 0, "Red Tanzaku", false),
    Card(JULY, CLOVER, ":/deck/Hanafuda_7-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(JULY, CLOVER, ":/deck/Hanafuda_7-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(AUGUST, PAMPAS, ":/deck/Hanafuda_8-4.svg", LIGHT, MOON, 20, 0, "Moon", false),
    Card(AUGUST, PAMPAS, ":/deck/Hanafuda_8-3.svg", ANIMAL, GEESE, 10, 0, "Geese", false),
    Card(AUGUST, PAMPAS, ":/deck/Hanafuda_8-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(AUGUST, PAMPAS, ":/deck/Hanafuda_8-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(SEPTEMBER, CHRYSANTHEMUM, ":/deck/Hanafuda_9-4.svg", ANIMAL, SAKE_CUP, 10, 0, "Sake Cup", true),
    Card(SEPTEMBER, CHRYSANTHEMUM, ":/deck/Hanafuda_9-3.svg", RIBBON, BLUE_RIBBON, 5, 0, "Blue Tanzaku", false),
    Card(SEPTEMBER, CHRYSANTHEMUM, ":/deck/Hanafuda_9-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(SEPTEMBER, CHRYSANTHEMUM, ":/deck/Hanafuda_9-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(OCTOBER, MAPLE, ":/deck/Hanafuda_10-4.svg", ANIMAL, DEER, 10, 0, "Deer", false),
    Card(OCTOBER, MAPLE, ":/deck/Hanafuda_10-3.svg", RIBBON, BLUE_RIBBON, 5, 0, "Blue Tanzaku", false),
    Card(OCTOBER, MAPLE, ":/deck/Hanafuda_10-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(OCTOBER, MAPLE, ":/deck/Hanafuda_10-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(NOVEMBER, WILLOW, ":/deck/Hanafuda_11-4.svg", LIGHT, RAIN, 20, 0, "Rain", false),
    Card(NOVEMBER, WILLOW, ":/deck/Hanafuda_11-3.svg", ANIMAL, SWALLOW, 10, 0, "Swallow", false),
    Card(NOVEMBER, WILLOW, ":/deck/Hanafuda_11-2.svg", RIBBON, RED_RIBBON, 5, 0, "Red Tanzaku", false),
    Card(NOVEMBER, WILLOW, ":/deck/Hanafuda_11-1.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(DECEMBER, PAULOWNIA, ":/deck/Hanafuda_12-4.svg", LIGHT, PHEONIX, 20, 0, "Pheonix", false),
    Card(DECEMBER, PAULOWNIA, ":/deck/Hanafuda_12-3.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(DECEMBER, PAULOWNIA, ":/deck/Hanafuda_12-2.svg", PLAIN, NIL, 1, 0, "Plain", false),
    Card(DECEMBER, PAULOWNIA, ":/deck/Hanafuda_12-1.svg", PLAIN, NIL, 1, 0, "Plain", false)
};

/*
* Class Definition, also functions as forward declaration
*/
class Deck
{

private:
    /*
    * Member Initialization List
    */
    std::vector<Card>::size_type m_numCards {fullDeck};
    std::vector<Card> m_cardDeck {koikoiDeck};
    //Currently QIcon.name() does not have a way to return the currently set QString for an icon...
    std::string m_deckIcon = ":/deck/Hanafuda_koi-2.svg";

public:
    /*
    * Constructors / Destructors
    */
    Deck();
    ~Deck();

    /*
    * Get Functions
    */
    Card* getCard(std::vector<Card>::size_type cardNum);
    std::vector<Card>::size_type getNumCards();
    Card* getRandCard();
    std::string getDeckIcon();

    /*
    * Set Functions
    */
    void resetDeck();
    void shuffleDeck();
    Card* dealCard();
    void setDeckIcon(std::string iconStr);

    /*
    * Print Functions
    */
    void printDeck();
};

#endif
