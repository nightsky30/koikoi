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
