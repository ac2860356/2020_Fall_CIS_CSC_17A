/* 
 * File:   Player.h
 * Author: Arthur Choy
 * Created on December 13, 2020, 2:32 AM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Dice.h"
#include "Category.h"
#include <string>

class Player : public Dice {
private:
    std::string name;           //Player name
    bool uBonus;                //Upper cate. bonus flag
protected:
    int total;                  //Total Score
public:
    Category card[SCORES_SIZE];             //Scorecard
    
    //Default Constructor
    Player();
    
    //Constructor
    Player(std::string);
    
    //Destructor
    virtual ~Player();

    //Mutator functions
    void stName(std::string n)
        { name = n; }
    void stCat(int);
    void stTotal(int t)
        { total = t; }
    void addTotal(int a)
        { total += a; }
    void subTotal(int s)
        { total -= s; }
    
    //Accessor functions
    std::string gtName() const
        { return name; }
    int gtScore(const int i) const
        { return card[i].gtScore(); }
    int gtTotal() const
        { return total; }
    
    //Overloaded operator
    bool operator >(const Player &);
    bool operator <(const Player &);
    int operator [](const int &);
    
};

#endif /* PLAYER_H */

