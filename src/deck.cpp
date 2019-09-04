#include "deck.h"
#include "card.h"
#include <iostream>     /* cout, cin, endl */
#include <vector>       /* vector */
#include <cstdio>      /* NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

//Default Constructor
Deck::Deck()
{
    //Ensure deck starts with proper number of cards (48)
    this->m_numCards = fullDeck;
    //Assign standard game deck
    this->m_cardDeck = koikoiDeck;
}

//Destructor
Deck::~Deck()
{
}

/*
* General Functions
*/
void Deck::shuffleDeck()
{
    using index_t = std::vector<Card>::size_type;

    index_t i {0};
    index_t r {0};
    srand(time(NULL));

    for (i = 0; i < m_numCards; i++)
    {
        //Generate a random number to select a card in the deck
        // Normally r = ((std::rand()) % 10) + 1;
        //  but since we want 0 thru 47 we change this a bit
        r = ((index_t)std::rand() % (m_numCards-1));
        //Swap the current card number being iterated through with the randomly picked card
        std::swap(m_cardDeck[i], m_cardDeck[r]);
    }
    std::cout << "=====================" << std::endl;
    std::cout << "The deck was shuffled" << std::endl;
    std::cout << "=====================" << std::endl;
}

void Deck::printDeck()
{
    using index_t = std::vector<Card>::size_type;

    index_t i {0};

    for (i = 0; i < m_numCards; i++)
    {
        //Print
        std::cout << "The current card info is: " << std::endl;
        std::cout << "==========================" << std::endl;
        m_cardDeck[i].printMonth();
        m_cardDeck[i].printFlower();
        m_cardDeck[i].printCardType();
        m_cardDeck[i].printCardType2();
        m_cardDeck[i].printPointVal();
        m_cardDeck[i].printPointVal2();
        m_cardDeck[i].printName();
        m_cardDeck[i].printWild();
        std::cout << "==========================" << std::endl;
    }
}

Card Deck::getCard(std::vector<Card>::size_type cardNum)
{
    return m_cardDeck[cardNum];
}

Card Deck::dealCard(std::vector<Card>::size_type cardNum)
{
    std::cout << "A card has been dealt" << std::endl;
    m_numCards = m_numCards - 1;
    std::cout << "The number of cards remaining in deck are: " << m_numCards << std::endl;
    return m_cardDeck[cardNum];
}
