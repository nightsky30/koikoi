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

#ifndef PLAYER_H
#define PLAYER_H

#include "yaku.h"
#include "hand.h"
#include <QVector>

/*
* Class Definition, also functions as forward declaration
*/
class Player
{

private:
    /*
    * Member Initialization List
    */
    int m_score {30};
//Holds the numbers from the Game's Yaku const??
    QVector<bool> m_obtainedYaku
    {
        QVector<bool> {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
    };
    bool m_oya {false};
    bool m_koikoi {false};
    int m_koikoiNum {0};
    Hand m_playerHand {Hand()};
    Hand m_lightMatch {Hand()};
    Hand m_animalMatch {Hand()};
    Hand m_ribbonMatch {Hand()};
    Hand m_plainMatch {Hand()};

public:
    /*
    * Constructors / Destructors
    */
    Player();
    ~Player();

    /*
    * Get Functions
    */
    int getScore();
    bool getYaku(int numYaku);
    int getYakuSize();
    bool getOya();
    bool getKoikoi();
    int getKoikoiNum();
    Hand* getHand();
    Hand* getLightMatch();
    Hand* getAnimalMatch();
    Hand* getRibbonMatch();
    Hand* getPlainMatch();

    /*
    * Set Functions
    */
    void setScore(int score);
    void setYaku(int numYaku, bool yakuValue);
    void resetYaku();
    void setOya(bool oya);
    void setKoikoi(bool koikoi);
    void setKoikoiNum(int koikoiNum);
};

#endif
