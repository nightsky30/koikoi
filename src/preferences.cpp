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

    ui->bgGridLayout->setContentsMargins(50,50,50,50);

    if(backResource->isEmpty() == false)
    {
        int itemNum {0};
        //Set up background label and radio button defaults in GUI
        for(int i{0};i<(static_cast<int>(backResource->count())*2)-1;i=i+2)
        {
            for(int j{0};j<(static_cast<int>(backResource->count())/5)+1;j++)
            {
                if(itemNum < static_cast<int>(backResource->count()))
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

                    ui->bgGridLayout->addWidget(label, i, j);
                    ui->bgGridLayout->setAlignment(label, Qt::AlignCenter);

                    ui->bgGridLayout->addWidget(radio, i+1, j);
                    ui->bgGridLayout->setAlignment(radio, Qt::AlignCenter);

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

    ui->deckGridLayout->setContentsMargins(50,50,50,50);

    if(deckResource->isEmpty() == false)
    {
        int itemNum {0};
        //Set up deck label and radio button defaults in GUI
        for(int i{0};i<(static_cast<int>(deckResource->count())*2)-1;i=i+2)
        {
            for(int j{0};j<(static_cast<int>(deckResource->count())/5)+1;j++)
            {
                if(itemNum < static_cast<int>(deckResource->count()))
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

                    ui->deckGridLayout->addWidget(label, i, j);
                    ui->deckGridLayout->setAlignment(label, Qt::AlignCenter);

                    ui->deckGridLayout->addWidget(radio, i+1, j);
                    ui->deckGridLayout->setAlignment(radio, Qt::AlignCenter);

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

    /*
     * Misc.
     */
    //Connect spinbox and send SIGNALS to the parent's (KoiKoi) SLOT (setRounds())
    connect(ui->roundsSpinBox, SIGNAL(valueChanged(int)), parent, SLOT(setRounds(int)), Qt::UniqueConnection);
    if(!settings.isWritable())
    {
        //We got issues
    }
    else
    {
        //Set to saved value
        ui->roundsSpinBox->setValue(this->settings.value("rounds", "").toInt());
    }
}

Preferences::~Preferences()
{
    delete ui;
}
