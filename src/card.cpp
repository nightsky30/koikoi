#include "card.h"
#include <iostream>
#include <string>

//Default Constructor
Card::Card()
{
    this->m_month = JANUARY;
    this->m_flower = PINE;
    this->m_cardType = PLAIN;
    this->m_cardType2 = PLAIN;
    this->m_pointVal = 5;
    this->m_pointVal2 = 5;
    this->m_name = "Card";
    this->m_wild = false;
}

//Constructor
Card::Card(CardMonth month, CardFlower flower, CardType cardType, CardType cardType2, int pointVal, int pointVal2, std::string name, bool wild)
{
    this->m_month = month;
    this->m_flower = flower;
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

/*
* Print Functions
*/
void Card::printMonth()
{
    std::cout << "The month is: " << m_month << std::endl;
}

void Card::printFlower()
{
    std::cout << "The flower is: " << m_flower << std::endl;
}

void Card::printCardType()
{
    std::cout << "The card type is: " << m_cardType << std::endl;
}

void Card::printCardType2()
{
    std::cout << "The card second type is: " << m_cardType2 << std::endl;
}

void Card::printPointVal()
{
    std::cout << "The card point value is: " << m_pointVal << std::endl;
}

void Card::printPointVal2()
{
    std::cout << "The card second point value is: " << m_pointVal2 << std::endl;
}

void Card::printName()
{
    std::cout << "The card name is: " << m_name << std::endl;
}

void Card::printWild()
{
    std::cout << "The wild card status is: " << m_wild << std::endl;
}
