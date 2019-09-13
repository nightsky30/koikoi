#ifndef YAKU_H
#define YAKU_H

#include <string>

/*
* Class Definition, also functions as forward declaration
*/
class Yaku
{

private:
    /*
    * Member Initialization List
    */
    int m_pointValue {1};
    std::string m_name {"Kasu (Plains)"};
    std::string m_description {"10 Plain cards. 1 point. Each Additional 1P after."};

public:
    /*
    * Constructors / Destructors
    */
    Yaku();
    Yaku(int pointValue, std::string name, std::string description);
    ~Yaku();

    /*
    * Get Functions
    */
    int getPointValue();
    std::string getName();
    std::string getDescription();

    /*
    * Print Functions
    */
    void printPointValue();
    void printName();
    void printDescription();

};

#endif
