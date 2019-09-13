#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>
#include <QLabel>
#include <QVector>
#include <QString>

using index_t = std::vector<Card>::size_type;

/*
* Class Definition, also functions as forward declaration
*/
class Hand
{

private:
    /*
    * Member Initialization List
    */
    index_t m_numCards {0};
    std::vector<Card> m_playerHand
    {
        Card()
    };
    index_t m_oyaCard {0};
    //numLabels needed??
    QVector<QLabel*> m_handLabels;

public:
    /*
    * Constructors / Destructors
    */
    Hand();
    ~Hand();

    /*
    * Get Functions
    */
    Card* getCard(std::vector<Card>::size_type cardNum);
    std::vector<Card>::size_type getNumCards();
    Card* getRandCard();
    QLabel* getLabel(QVector<QLabel>::size_type labelNum);
    index_t getOyaCard();

    /*
    * Set Functions
    */
    void setOyaCard(index_t oyaCard);
    void acceptCard(Card &newCard);
    Card* disCard(std::vector<Card>::size_type cardNum);
    void removeCard(std::vector<Card>::size_type cardNum);
    void resetHand();

    /*
    * Print Functions
    */
    void printHand();
};

#endif
