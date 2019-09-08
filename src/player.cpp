#include "player.h"

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

void Player::setScore(int score)
{
    m_score = score;
}

std::vector<Yaku>::size_type Player::getYaku()
{
    return m_obtainedYaku;
}

void Player::setYaku()
{

}

bool Player::getOya()
{
    return m_oya;
}

void Player::setOya(bool oya)
{
    m_oya = oya;
}

bool Player::getKoikoi()
{
    return m_koikoi;
}

void Player::setKoikoi()
{

}

Hand Player::getHand()
{
    return m_playerHand;
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
