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
#include <QResource>
#include <QDir>
#include <QVector>
#include <QLabel>
#include <QRadioButton>

Preferences::Preferences(QWidget *parent) : QDialog (parent),
    ui(new Ui::Preferences)
{

    ui->setupUi(this);
    //Create QWidget object pointers and assign values to their attributes
    //VBox layout with some checkboxes, labels, etc

    //Title and Application Icon
    this->setWindowTitle("Koi-Koi Hanafuda - Preferences");
    this->setWindowIcon(QIcon(QString(":/icon/koi-2.svg")));

    //    //Create vertical box layout
    //    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);

    //    //Set up about fonts
    //    QFont titleFont("Noto Sans", 12, QFont::Bold);
    //    QFont aboutFont("Arial", 9, QFont::Normal);

    //    //Set up application name
    //    QLabel *appName = new QLabel(this);
    //    appName->setText(QString(tr("Koi-Koi Hanafuda")));
    //    appName->setFont(titleFont);

    //    //Set up application version
    //    QLabel *appVersion = new QLabel(this);
    //    appVersion->setText(QString(tr("Version: ") + QString(version)));
    //    appVersion->setFont(aboutFont);

    //    //Set up Git project link
    //    QLabel *gitUrlLabel = new QLabel(this);
    //    gitUrlLabel->setTextFormat(Qt::RichText);
    //    gitUrlLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    //    gitUrlLabel->openExternalLinks();
    //    gitUrlLabel->setText("<a href='" + QString(git) + "'>" + tr("Git Project Page") + "</a>");
    //    connect(gitUrlLabel, &QLabel::linkActivated, this, &About::openGitUrl);

    //    //Set up the vertical box layout by adding the created widgets
    //    vBoxLayout->addWidget(appName);
    //    vBoxLayout->addWidget(appVersion);
    //    vBoxLayout->addWidget(gitUrlLabel);

    QDir *backResource = new QDir(":/background");
    QVector<QLabel*> guiBGLabels {};
    QVector<QRadioButton*> guiBGRadios {};

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
                    label->setPixmap(QString(":/background/" + backResource->entryList().at(itemNum)));
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

                    //Connect radio buttons with labels' resources

                    itemNum++;
                }
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
