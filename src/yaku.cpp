#include "yaku.h"
#include <iostream>
#include <string>

Yaku::Yaku()
{
    this->m_pointValue = 1;
    this->m_name = "Kasu (Plains)";
    this->m_description = "10 Plain cards. 1 point. Each Additional 1P after.";
}

Yaku::Yaku(int pointValue, std::string name, std::string description)
{
    this->m_pointValue = pointValue;
    this->m_name = name;
    this->m_description = description;
}

Yaku::~Yaku()
{
}

int Yaku::getPointValue()
{
    return m_pointValue;
}

std::string Yaku::getName()
{
    return m_name;
}

std::string Yaku::getDescription()
{
    return m_description;
}

void Yaku::printPointValue()
{
    std::cout << "The yaku point value is: " << m_pointValue << std::endl;
}

void Yaku::printName()
{
    std::cout << "The yaku name is: " << m_name << std::endl;
}

void Yaku::printDescription()
{
    std::cout << "The yaku description is: " << m_description << std::endl;
}
