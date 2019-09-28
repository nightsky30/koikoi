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
    int m_score {30};
//Holds the numbers from the Game's Yaku const??
    std::vector<bool> m_obtainedYaku
    {
        std::vector<bool> {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false}
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
    bool getYaku(int numYaku);
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
    void setYaku(int numYaku, bool yakuValue);
    void resetYaku();
    void setOya(bool oya);
    void setKoikoi(bool koikoi);

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
