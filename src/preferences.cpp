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

#include "preferences.h"
#include "ui_preferences.h"
#include <iostream>
#include <QIcon>
#include <QString>
#include <QVBoxLayout>
#include <QDir>
#include <QVector>
#include <QLabel>
#include <QRadioButton>
#include <QRegularExpression>
#include <QSettings>

Preferences::Preferences(QWidget *parent) : QDialog (parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    //Title and Application Icon
    this->setWindowTitle("Koi-Koi Hanafuda - Preferences");
    this->setWindowIcon(QIcon(QString(":/icon/koi-2.svg")));

    /*
     * Backgrounds
     */
    backResource->setPath(":/backgrounds");

    ui->gridLayout_2->setContentsMargins(50,50,50,50);

    if(backResource->isEmpty() == false)
    {
        int itemNum {0};
        //Set up background label and radio button defaults in GUI
        for(unsigned int i{0};i<(backResource->count()*2)-1;i=i+2)
        {
            for(unsigned int j{0};j<(backResource->count()/5)+1;j++)
            {
                if(itemNum < backResource->count())
                {
                    QString labelName = "bgLabel_" + QString::number(itemNum);
                    QLabel *label = new QLabel(labelName, this);
                    label->setObjectName(labelName);
                    label->setMinimumSize(100,100);
                    label->setMaximumSize(100,100);
                    label->setText("");
                    label->setPixmap(QString(":/backgrounds/" + backResource->entryList().at(itemNum)));
                    label->setScaledContents(true);
                    label->setEnabled(true);
                    label->setVisible(true);
                    label->show();

                    QString radioName = "bgRadio_" + QString::number(itemNum);
                    QRadioButton *radio = new QRadioButton(radioName, this);
                    radio->setObjectName(radioName);
                    radio->setText("");
                    radio->setEnabled(true);
                    radio->setVisible(true);
                    radio->show();

                    ui->gridLayout_2->addWidget(label, i, j);
                    ui->gridLayout_2->setAlignment(label, Qt::AlignCenter);

                    ui->gridLayout_2->addWidget(radio, i+1, j);
                    ui->gridLayout_2->setAlignment(radio, Qt::AlignCenter);

                    guiBGLabels.append(label);
                    guiBGRadios.append(radio);

                    //Connect radio buttons with labels' resources and send SIGNALS to the parent's (KoiKoi) SLOT (setBG())
                    connect(radio, SIGNAL(clicked()), parent, SLOT(setBG()), Qt::UniqueConnection);

                    itemNum++;
                }
            }
        }
        if(!settings.isWritable())
        {
            //We got issues
        }
        else
        {
            QString buttonName = this->settings.value("bgRadio", "").toString();
            int buttonNum {0};

            if(buttonName != nullptr)
            {
                QRegularExpression regEx("(\\d{2}|\\d{1})");
                QRegularExpressionMatch match = regEx.match(buttonName);
                if (match.hasMatch())
                {
                    //Get card number
                    QString matchedString = match.captured(1);
                    buttonNum = matchedString.toInt();
                }
                else
                {
                    std::cout << "There were issues matching regex with the sender button to obtain the button number..." << std::endl;
                }
            }
            QRadioButton *radioButton = guiBGRadios.at(buttonNum);
            if (radioButton != nullptr) {
                radioButton->setChecked(true);
            }
        }
    }
    else
    {
        std::cout << "Problem:  Resources not found." << std::endl;;
    }

    /*
     * Decks
     */
    deckResource->setPath(":/decks");

    ui->gridLayout->setContentsMargins(50,50,50,50);

    if(deckResource->isEmpty() == false)
    {
        int itemNum {0};
        //Set up deck label and radio button defaults in GUI
        for(unsigned int i{0};i<(deckResource->count()*2)-1;i=i+2)
        {
            for(unsigned int j{0};j<(deckResource->count()/5)+1;j++)
            {
                if(itemNum < deckResource->count())
                {
                    QString labelName = "deckLabel_" + QString::number(itemNum);
                    QLabel *label = new QLabel(labelName, this);
                    label->setObjectName(labelName);
                    label->setMinimumSize(60,84);
                    label->setMaximumSize(60,84);
                    label->setText("");
                    label->setPixmap(QString(":/decks/" + deckResource->entryList().at(itemNum)));
                    label->setScaledContents(true);
                    label->setEnabled(true);
                    label->setVisible(true);
                    label->show();

                    QString radioName = "deckRadio_" + QString::number(itemNum);
                    QRadioButton *radio = new QRadioButton(radioName, this);
                    radio->setObjectName(radioName);
                    radio->setText("");
                    radio->setEnabled(true);
                    radio->setVisible(true);
                    radio->show();

                    ui->gridLayout->addWidget(label, i, j);
                    ui->gridLayout->setAlignment(label, Qt::AlignCenter);

                    ui->gridLayout->addWidget(radio, i+1, j);
                    ui->gridLayout->setAlignment(radio, Qt::AlignCenter);

                    guiDeckLabels.append(label);
                    guiDeckRadios.append(radio);

                    //Connect radio buttons with labels' resources and send SIGNALS to the parent's (KoiKoi) SLOT (setDeck())
                    connect(radio, SIGNAL(clicked()), parent, SLOT(setDeck()), Qt::UniqueConnection);

                    itemNum++;
                }
            }
        }
        if(!settings.isWritable())
        {
            //We got issues
        }
        else
        {
            QString buttonName = this->settings.value("deckRadio", "").toString();
            int buttonNum {0};

            if(buttonName != nullptr)
            {
                QRegularExpression regEx("(\\d{2}|\\d{1})");
                QRegularExpressionMatch match = regEx.match(buttonName);
                if (match.hasMatch())
                {
                    //Get card number
                    QString matchedString = match.captured(1);
                    buttonNum = matchedString.toInt();
                }
                else
                {
                    std::cout << "There were issues matching regex with the sender button to obtain the button number..." << std::endl;
                }
            }
            QRadioButton *radioButton = guiDeckRadios.at(buttonNum);
            if (radioButton != nullptr) {
                radioButton->setChecked(true);
            }
        }
    }
    else
    {
        std::cout << "Problem:  Resources not found." << std::endl;;
    }
}

Preferences::~Preferences()
{
    delete ui;
}
