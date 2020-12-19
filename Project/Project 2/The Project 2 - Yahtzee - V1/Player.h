/* 
 * File:   Player.h
 * Author: Arthur Choy
 * Created on December 13, 2020, 2:32 AM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Dice.h"
#include "Category.h"

class Player : public Dice {
private:
    std::string name;           //Player name
    bool uBonus;                //Upper cate. bonus flag
protected:
    int total;                  //Total Score
public:
    Category *card;             //Scorecard
    
    //Default Constructor
    Player();
    
    //Constructor
    Player(std::string);
    
    //Default Copy Constructor
    Player(const Player& orig);
    
    //Destructor
    virtual ~Player();

    //Mutator functions
    void stName(std::string n)
        { name = n; }
    void stScore(int);
    void stTotal(int t)
        { total = t; }
    
    //Accessor functions
    std::string gtName() const
        { return name; }
    int gtScore(const int i) const
        { return card[i]; }
    int gtTotal() const
        { return total; }
    
    //Overloaded operator
    void operator +=(const int &);
    void operator -=(const int &);
    bool operator >(const Player &);
    bool operator <(const Player &);
    int operator [](const int &);
    
};

#endif /* PLAYER_H */

