/* 
 * File:   DICE.h
 * Author: Arthur Choy
 * Created on December 13, 2020, 1:06 AM
 */

#ifndef NEWFILE_H
#define NEWFILE_H

class Dice {
private:
    static const int DICE_SIZE = 5;    //Dice and score array sizes
    int diceArr[DICE_SIZE];            //Dice array
protected:
    static const int SCORES_SIZE = 13; //Size of arrays involving categories
    int scores[SCORES_SIZE];           //Score array
    bool keepArr[DICE_SIZE];           //Keep dice 
public:
    //Default Constructor
    Dice();
     
    //Destructor
    virtual ~Dice();
    
    //Accessor functions
    int gtDice(int i) const
        { return diceArr[i]; }
    virtual int gtScore(int i) const
        { return scores[i]; }
    
    //Functions
    void roll();        //Roll all die
    void rstKeep();     //Reset which dice are kept
    void detScre();     //Determine scores available from current dice
    void rstScre();     //Reset scores available from dice
    int rollDie(int);   //Roll one die
    int freq();         //Find dice mode for determining scores
    int seq();          //Find longest sequence for determining scores
    bool *keep();       //Determine which dice to keep
};

#endif /* NEWFILE_H */

