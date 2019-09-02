#ifndef CARD_H
#define CARD_H

#include <string>

/*
* Month Values
* ============
* 0 - 12
*/
enum CardMonth
{
    JANUARY,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

/*
* Flower Values
* =============
* 0 - 12
*/
enum CardFlower
{
    PINE,
    PLUM_BLOSSOMS,
    CHERRY_BLOSSOMS,
    WISTERIA,
    IRIS,
    PEONY,
    CLOVER,
    PAMPAS,
    CHRYSANTHEMUM,
    MAPLE,
    WILLOW,
    PAULOWNIA
};

/*
* General Card Types
* ==================
* Light     =       0
* Animal    =       1
* Ribbon    =       2
* Plain     =       3
* Nil       =       4
*/
enum CardType
{
    LIGHT = 0,
    CRANE = 0,
    CURTAIN = 0,
    RAIN = 0,
    MOON = 0,
    PHEONIX = 0,
    ANIMAL = 1,
    NIGHTINGALE = 1,
    CUCKOO = 1,
    BRIDGE = 1,
    BUTTERFLIES = 1,
    BOAR = 1,
    GEESE = 1,
    SAKE_CUP = 1, // Can also be plain for 10 Kasu Yaku
    DEER = 1,
    SWALLOW = 1,
    RED_RIBBON = 2,
    RED_POEM = 2,
    BLUE_RIBBON = 2,
    PLAIN = 3,
    NIL = 4
};

/*
* Class Definition, also functions as forward declaration
*/
class Card
{

private:

    /*
    * Member Initialization List
    */
    CardMonth m_month {JANUARY};
    CardFlower m_flower {PINE};
    //Need to add image member var
    CardType m_cardType {PLAIN};
    CardType m_cardType2 {NIL};
    int m_pointVal {5};
    int m_pointVal2 {5};
    std::string m_name {"Card"};
    bool m_wild {false};

public:

    /*
    * Constructors / Destructors
    */
    Card();
    Card(CardMonth month, CardFlower flower, CardType cardType, CardType cardType2, int pointVal, int pointVal2, std::string name, bool wild);
    ~Card();

    /*
    * Get Functions
    */
    CardMonth getMonth();
    CardFlower getFlower();
    CardType getCardType();
    CardType getCardType2();
    int getPointVal();
    int getPointVal2();
    std::string getName();
    bool getWild();

    /*
    * Print Functions
    */
    void printMonth();
    void printFlower();
    void printCardType();
    void printCardType2();
    void printPointVal();
    void printPointVal2();
    void printName();
    void printWild();
};

#endif
