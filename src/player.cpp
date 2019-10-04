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

void Player::printScore()
{
    std::cout << "The player's score is: " << m_score << std::endl;
}

void Player::printYaku()
{
    std::cout << "The player's yaku is: " << "" << std::endl;
    for (int i {0};i<m_obtainedYaku.size();i++)
    {
        std::cout << m_obtainedYaku[i] << std::endl;
    }
}

void Player::printOya()
{
    std::cout << "The player's oya status is: " << m_oya << std::endl;
}

void Player::printKoikoi()
{
    std::cout << "The player's koikoi status is: " << m_koikoi << std::endl;
}

void Player::printHand()
{
    std::cout << "The player's hand is: " << std::endl;
    m_playerHand.printHand();
}

void Player::printLightMatch()
{
    std::cout << "The player's light matches are: " << std::endl;
    m_lightMatch.printHand();
}

void Player::printAnimalMatch()
{
    std::cout << "The player's animal matches are: " << std::endl;
    m_animalMatch.printHand();
}

void Player::printRibbonMatch()
{
    std::cout << "The player's ribbon matches are: " << std::endl;
    m_ribbonMatch.printHand();
}

void Player::printPlainMatch()
{
    std::cout << "The player's plain matches are: " << std::endl;
    m_plainMatch.printHand();
}
