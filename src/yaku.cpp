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

int Yaku::getPointValue() const
{
    return m_pointValue;
}

std::string Yaku::getName() const
{
    return m_name;
}

std::string Yaku::getDescription() const
{
    return m_description;
}
