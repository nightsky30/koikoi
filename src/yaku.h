#ifndef YAKU_H
#define YAKU_H

#include <string>

class Yaku
{

private:

    int m_pointValue {1};
    std::string m_name {"Kasu (Plains)"};
    std::string m_description {"10 Plain cards. 1 point. Each Additional 1P after."};

public:

    Yaku();
    Yaku(int pointValue, std::string name, std::string description);
    ~Yaku();

    int getPointValue();
    std::string getName();
    std::string getDescription();

    void printPointValue();
    void printName();
    void printDescription();

};

#endif
