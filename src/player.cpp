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

#include "player.h"
#include "hand.h"
#include <iostream>

Player::Player()
{

}

Player::~Player()
{
}

int Player::getScore()
{
    return m_score;
}

bool Player::getYaku(int numYaku)
{
    return m_obtainedYaku[numYaku];
}

int Player::getYakuSize()
{
    return m_obtainedYaku.size();
}

bool Player::getOya()
{
    return m_oya;
}

bool Player::getKoikoi()
{
    return m_koikoi;
}

int Player::getKoikoiNum()
{
    return m_koikoiNum;
}

Hand* Player::getHand()
{
    Hand *playerHand;
    playerHand = &m_playerHand;
    return playerHand;
}

Hand* Player::getLightMatch()
{
    Hand *lightMatch;
    lightMatch = &m_lightMatch;
    return lightMatch;
}

Hand* Player::getAnimalMatch()
{
    Hand *animalMatch;
    animalMatch = &m_animalMatch;
    return animalMatch;
}

Hand* Player::getRibbonMatch()
{
    Hand *ribbonMatch;
    ribbonMatch = &m_ribbonMatch;
    return ribbonMatch;
}

Hand* Player::getPlainMatch()
{
    Hand *plainMatch;
    plainMatch = &m_plainMatch;
    return plainMatch;
}

void Player::setScore(int score)
{
    m_score = score;
}

void Player::setYaku(int numYaku, bool yakuValue)
{
    m_obtainedYaku[numYaku] = yakuValue;
}

void Player::resetYaku()
{
    for(int i {0};i<m_obtainedYaku.size();i++)
    {
        m_obtainedYaku[i] = false;
    }
}

void Player::setOya(bool oya)
{
    m_oya = oya;
}

void Player::setKoikoi(bool koikoi)
{
    m_koikoi = koikoi;
}

void Player::setKoikoiNum(int koikoiNum)
{
    m_koikoiNum = koikoiNum;
}
