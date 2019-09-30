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

#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QSettings>
#include <QUrl>

/*
* Class Definition, also functions as forward declaration
*/
class About : public QDialog
{
    Q_OBJECT

private:
    /*
    * Member Initialization List
    */
    QSettings settings;

public:
    /*
    * Constructors / Destructors
    */
    About(QWidget* parent = 0);
    ~About();

public slots:
    void openGitUrl();
};

#endif // ABOUT_H
