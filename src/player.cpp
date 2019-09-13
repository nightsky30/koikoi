#include "player.h"
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

std::vector<Yaku>::size_type Player::getYaku()
{
    return m_obtainedYaku;
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

void Player::setScore(int score)
{
    m_score = score;
}

void Player::setYaku()
{

}

void Player::setOya(bool oya)
{
    m_oya = oya;
}

void Player::setKoikoi()
{

}

void Player::printScore()
{
    std::cout << "The player's score is: " << m_score << std::endl;
}

void Player::printYaku()
{
    std::cout << "The player's yaku is: " << "" << std::endl;
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
