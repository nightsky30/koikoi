#ifndef PLAYER_H
#define PLAYER_H

#include "yaku.h"
#include "hand.h"
#include <vector>

/*
* Class Definition, also functions as forward declaration
*/
class Player
{

private:
    /*
    * Member Initialization List
    */
    int m_score {0};
//Holds the numbers from the Game's Yaku const??
    std::vector<Yaku>::size_type m_obtainedYaku
    {
        std::vector<Yaku>::size_type {0}
    };
    bool m_oya {false};
    bool m_koikoi {false};
    Hand m_playerHand {Hand()};
    Hand m_lightMatch {Hand()};
    Hand m_animalMatch {Hand()};
    Hand m_ribbonMatch {Hand()};
    Hand m_plainMatch {Hand()};

public:
    /*
    * Constructors / Destructors
    */
    Player();
    ~Player();

    /*
    * Get Functions
    */
    int getScore();
    std::vector<Yaku>::size_type getYaku();
    bool getOya();
    bool getKoikoi();
    Hand* getHand();
    Hand* getLightMatch();
    Hand* getAnimalMatch();
    Hand* getRibbonMatch();
    Hand* getPlainMatch();

    /*
    * Set Functions
    */
    void setScore(int score);
    void setYaku();
    void setOya(bool oya);
    void setKoikoi();

    /*
    * Print Functions
    */
    void printScore();
    void printYaku();
    void printOya();
    void printKoikoi();
    void printHand();
    void printLightMatch();
    void printAnimalMatch();
    void printRibbonMatch();
    void printPlainMatch();
};

#endif
