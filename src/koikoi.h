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

#ifndef KOIKOI_H
#define KOIKOI_H

#include "deck.h"
#include "hand.h"
#include "yaku.h"
#include "player.h"
#include <QVector>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>

/*
 * The game consists of these yaku.
 * Order here matters.
 * Each player has a corresponding bool vector that
 * matches values with objects in this Yaku vector.
 */
const static QVector<Yaku> acceptableYaku
{
    Yaku(1, "Kasu (Plains)", "10 Plain cards. 1 point. Each Additional 1P after."),
            Yaku(1, "Bake-Fuda (Wild Card)", "The animal card of Chrysanthemum can be regarded as a plain card as well. If you have this, 9 plain cards and this card will be the Yaku of Kasu."),
            Yaku(4, "Tsuki-fuda (Monthly Cards)", "All four cards in one group shown right on screen. 4 points."),
            Yaku(6, "Oya-Ken (Dealer's Privilege)", "If neither gets any Yaku, Dealer wins 6 points."),
            Yaku(1, "Tane (Animals)", "5 Animals. 1 point. Each Additional 1P after."),
            Yaku(5, "Ino-Shika-Cho (Boar-Deer-Butterflies)", "Animal cards of Clover, Maple, Peony. 5 points."),
            Yaku(1, "Tanzaku (Ribbons)", "5 Ribbons. 1 point. Each Additional 1P after."),
            Yaku(5, "Akatan (Red Poetry Ribbons)", "All 3 red poetry ribbons. 5 points."),
            Yaku(5, "Aotan (Blue Ribbons)", "All 3 blue ribbons. 5 points."),
            Yaku(10, "Akatan Aotan No Chofuku (3 Red Poetry Ribbons and 3 Blue Ribbons)", "3 Red Poetry Ribbons and 3 Blue Ribbons. 10 points."),
            Yaku(5, "Tsukimi De Ippai (Moon and Sake Cup)", "Moon and Sake Cup cards. 5 points."),
            Yaku(5, "Hanami De Ippai (Curtain and Sake Cup)", "Curtain and Sake Cup cards. 5 points."),
            Yaku(5, "Sanko (3 Brights)", "3 Bright cards not containing Rain man card. 5 points."),
            Yaku(7, "Ame-Shiko (4 Brights, Rain man)", "4Brights containing Rain man card. 7 points."),
            Yaku(8, "Shiko (4 Brights)", "4 Bright cards not containing Rain man card. 8 points."),
            Yaku(10, "Goko (5 Brights)", "All 5 Bright cards. 10 points.")
};

const static QVector<QString> settingKeys
{
    QString("background"),
            QString("bgRadio"),
            QString("deck"),
            QString("deckRadio"),
            QString("rounds")
};

namespace Ui {

/*
* Class Definition, also functions as forward declaration
*/
class KoiKoi;

}

/*
* Class Definition, also functions as forward declaration
*/
class KoiKoi : public QMainWindow
{
    Q_OBJECT

private:
    /*
    * Member Initialization List
    */
    Ui::KoiKoi *ui;
    Deck m_gameDeck {Deck()};
    Player m_player1 {Player()};
    Player m_player2 {Player()};
    Hand m_gameHand {Hand()};
    Hand m_oyaHand {Hand()};
    int m_rounds {12};
    int m_currentRound {0};
    bool m_gameStatus {false};
    bool m_koikoiRequested {false};
    bool m_koikoiDecided {false};
    bool m_cpuKoikoiRequested {false};
    bool m_cpuKoikoiDecided {false};
    QTimer *timeDelay {};

    QVector<QPushButton*> guiPlayerCards {};
    QVector<QPushButton*> guiCPUCards {};
    QVector<QPushButton*> guiGameHandCards {};

    QVector<QLabel*> guiPlayerLightYaku {};
    QVector<QLabel*> guiPlayerAnimalYaku {};
    QVector<QLabel*> guiPlayerRibbonYaku {};
    QVector<QLabel*> guiPlayerPlainYaku {};

    QVector<QLabel*> guiCPULightYaku {};
    QVector<QLabel*> guiCPUAnimalYaku {};
    QVector<QLabel*> guiCPURibbonYaku {};
    QVector<QLabel*> guiCPUPlainYaku {};

    QSettings settings;
    QPixmap m_bkgnd {};
    QString m_deckArt {};

public:
    /*
    * Constructors / Destructors
    */
    explicit KoiKoi(QWidget *parent = nullptr);
    ~KoiKoi();

    /*
    * Get Functions
    */
    Deck* getDeck();
    Player* getPlayer(int playerNum);
    Hand* getGameHand();
    int getNumRounds();
    int getCurrentRound();
    bool getGameStatus();

    /*
    * Set Functions
    */
    void startGame();
    void generateOyaCard();
    void deal();
    void startRound();
    void tallyPoints(int playerNum); //??  Player currentPlayer, Player nextPlayer
    void cpuSelectFromHand();
    void cpuSelectFromGameHand();
    void cpuDrawCard();
    void cpuRequestKoiKoi();

    /*
    * GUI Functions
    */
    void showTitleScreen();
    void showGameScreen();
    void showOyaScreen();
    void showKoiKoiScreen();
    void showTallyScreen();
    void updateCards();
    void updateScores();
    void updateKoiKoi();
    void resetYaku();
    void resetTally();
    void updateYaku();
    void checkYaku(int playerNum);
    void connectDeck();
    void connectGameHand(QPushButton *button);
    void connectGameHand();
    void connectPlayerHand(QPushButton *button);
    void connectPlayerHand();
    void disconnectDeck();
    void disconnectGameHand(QPushButton *button);
    void disconnectGameHand();
    void disconnectPlayerHand(QPushButton *button);
    void disconnectPlayerHand();
    void paintEvent(QPaintEvent *pe);
    void loadSettings();

public slots:
    void onNewGameClicked();
    void onQuitGameClicked();
    void onPreferencesClicked();
    void onAboutClicked();
    void determineOyaPlayer();
    void selectFromHand();
    void selectFromGameHand();
    void drawCard();
    void requestKoiKoi();
    void nextRound();
    void waitABit(int timeUnit);
    void setBG();
    void setDeck();
    void setRounds(int numRounds);
};

#endif // KOIKOI_H
