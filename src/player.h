#ifndef PLAYER_H
#define PLAYER_H

#include "yaku.h"
#include "hand.h"
#include <vector>

class Player
{

private:

    int m_score {0};
//Holds the numbers from the Game's Yaku const??
    std::vector<Yaku>::size_type m_obtainedYaku
    {
        std::vector<Yaku>::size_type {0}
    };
    bool m_oya {false};
    bool m_koikoi {false};
    Hand m_playerHand {Hand()};

public:

    Player();
    ~Player();

    int getScore();
    void setScore(int score);
    std::vector<Yaku>::size_type getYaku();
    bool getOya();
    bool getKoikoi();
    Hand getHand();

    void printScore();
    void printYaku();
    void printOya();
    void printKoikoi();
    void printHand();

};

#endif
