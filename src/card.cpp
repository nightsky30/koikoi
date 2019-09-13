#include "card.h"
#include <iostream>
#include <string>

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
Card::Card(CardMonth month, CardFlower flower, std::string imageStr, CardType cardType, CardType cardType2, int pointVal, int pointVal2, std::string name, bool wild)
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

std::string Card::getImageStr()
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

/*
* Print Functions
*/
void Card::printCard()
{
    std::cout << "=========================" << std::endl;
    std::cout << "Information for card:" << std::endl;
    std::cout << "=========================" << std::endl;
    printMonth();
    printFlower();
    printCardType();
    printCardType2();
    printPointVal();
    printPointVal2();
    printName();
    printWild();
    std::cout << "=========================" << std::endl;
    std::cout << std::endl;
}

void Card::printMonth()
{
    std::string niceMonth {""};

    switch (m_month)
    {
    case JANUARY:
        niceMonth = "JANUARY";
        break;
    case FEBRUARY:
        niceMonth = "FEBRUARY";
        break;
    case MARCH:
        niceMonth = "MARCH";
        break;
    case APRIL:
        niceMonth = "APRIL";
        break;
    case MAY:
        niceMonth = "MAY";
        break;
    case JUNE:
        niceMonth = "JUNE";
        break;
    case JULY:
        niceMonth = "JULY";
        break;
    case AUGUST:
        niceMonth = "AUGUST";
        break;
    case SEPTEMBER:
        niceMonth = "SEPTEMBER";
        break;
    case OCTOBER:
        niceMonth = "OCTOBER";
        break;
    case NOVEMBER:
        niceMonth = "NOVEMBER";
        break;
    case DECEMBER:
        niceMonth = "DECEMBER";
        break;
    default:
        std::cout << "The month could not be determined." << std::endl;
        break;
    }
    std::cout << "The month is: " << niceMonth << std::endl;
}

void Card::printFlower()
{
    std::string niceFlower {""};

    switch (m_flower)
    {
    case PINE:
        niceFlower = "PINE";
        break;
    case PLUM_BLOSSOMS:
        niceFlower = "PLUM BLOSSOMS";
        break;
    case CHERRY_BLOSSOMS:
        niceFlower = "CHERRY BLOSSOMS";
        break;
    case WISTERIA:
        niceFlower = "WISTERIA";
        break;
    case IRIS:
        niceFlower = "IRIS";
        break;
    case PEONY:
        niceFlower = "PEONY";
        break;
    case CLOVER:
        niceFlower = "CLOVER";
        break;
    case PAMPAS:
        niceFlower = "PAMPAS";
        break;
    case CHRYSANTHEMUM:
        niceFlower = "CHRYSANTHEMUM";
        break;
    case MAPLE:
        niceFlower = "MAPLE";
        break;
    case WILLOW:
        niceFlower = "WILLOW";
        break;
    case PAULOWNIA:
        niceFlower = "PAULOWNIA";
        break;
    default:
        std::cout << "The flower could not be determined." << std::endl;
        break;
    }
    std::cout << "The flower is: " << niceFlower << std::endl;
}

void Card::printImageStr()
{
    std::cout << "The card image value is: " << m_imageStr << std::endl;
}

void Card::printCardType()
{
    std::cout << "The card type is: " << Card::determineCardType(m_cardType) << std::endl;
}

void Card::printCardType2()
{
    std::cout << "The card second type is: " << Card::determineCardType(m_cardType2) << std::endl;
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
    std::string niceWild {""};

    switch (m_wild)
    {
    case true:
        niceWild = "Wild";
        break;
    case false:
        niceWild = "Not Wild";
        break;
    }
    std::cout << "The wild card status is: " << niceWild << std::endl;
}
