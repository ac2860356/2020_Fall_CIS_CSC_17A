/* 
 * File:   Game.h
 * Author: Arthur Choy
 * Created on December 14, 2020, 12:40 AM
 */

#ifndef GAME_H
#define GAME_H
#include "Player.h"

class Game {
private:
    static const int DICE_SIZE = 5;
    int rlCount;    //Roll count  (max. 3 per player)
    int tCount;     //Turn count  (max: amount of players)
    int rCount;     //Round count (max 13)
    int pCount;     //Player count
    bool quit;   //Whether or not player quit to menu
public:
    Player *plyrs;  //Players pointer
    
    //Default Constructor
    Game();
    
    //Constructor
    Game(int);
    
    //Destructor
    virtual ~Game();
    
    //Exception Classes
    class invalidOption { };
    class qToMenu { };
    class end { };
    
    //Mutator functions
    void stRLCount(int rl)
        { rlCount = rl; }
    void stTCount(int t)
        { tCount = t; }
    void stRCount(int r)
        { rCount = r; }
    void stPCount(int p)
        { pCount = p; }
    
    //Accessor functions
    int gtRLCount() const
        { return rlCount; }
    int gtTCount() const
        { return tCount; }
    int gtRCount() const
        { return rCount; }
    int gtPCount() const
        { return pCount; }
    
    //Functions
    bool reroll(Player &);
    void turn(Player &);
    void nextT();
    void dspCard(Player);
};

#endif /* GAME_H */

