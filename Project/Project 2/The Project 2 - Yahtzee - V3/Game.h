/* 
 * File:   Game.h
 * Author: Arthur Choy
 * Created on December 14, 2020, 12:40 AM
 */

#ifndef GAME_H
#define GAME_H
#include "Player.h"

//Game class
class Game {
private:
    static const int DICE_SIZE = 5; //Amount of time
    int rlCount;    //Roll count  (max. 3 per player)
    int tCount;     //Turn count  (max: amount of players)
    int rCount;     //Round count (max 13)
    int pCount;     //Player count
    bool quit;      //Whether or not player quit to menu
public:
    Player *plyrs;  //Players pointer
    
    //Default Constructor
    Game();
    
    //Constructor
    Game(int);
    
    //Copy Constructor
    Game(const Game &obj);
    
    //Destructor
    virtual ~Game();
    
    //Exception Classes
    class invalidOption { };    //Exception class for when the player inputs an invalid value
    class qToMenu { };          //Exception class for when the player quits to the menu
    class end { };              //Exception class for when the game ends
    
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
    bool getQtoM() const
        { return quit; }
    
    //Functions
    bool reroll(Player &);  //Rerolls dice array
    void turn(Player &);    //A single turn in the game
    void nextT();           //Move to next turn
    void dspCard(Player);   //Display player's scorecard
    void detWin();          //Determine which player won the game
};

#endif /* GAME_H */

