/* 
 * File:   DICE.h
 * Author: Arthur Choy
 * Created on December 13, 2020, 1:06 AM
 */

#ifndef NEWFILE_H
#define NEWFILE_H

class Dice {
private:
    const int DICE_SIZE = 5;    //Dice and score array sizes
    int *diceArr;               //Dice array
protected:
    const int SCORES_SIZE = 13; //Size of arrays involving categories
    int *scores;                //Score array
    bool *keepArr;              //Keep dice 
public:
    //Default Constructor
    Dice();
    
    //Default Copy Constructor
    Dice(const Dice& orig);
    
    //Destructor
    virtual ~Dice();
    
    //Accessor functions
    int *gtDice() const
        { return diceArr; }
    int *gtScores() const
        { return scores; }
    int gtScores(const int i) const
        { return scores[i]; }
    
    //Functions
    void roll();        //Roll all die
    void rstKeep();     //Reset which dice are kept
    void detScre();     //Determine scores available from current dice
    void rstScre();     //Reset scores available from dice
    int rollDie(int);   //Roll one die
    void sort();        //Sort dice for determining score
    int freq();         //Find dice mode for determining scores
    int seq();          //Find longest sequence for determining scores
    bool *keep(const int *);  //Determine which dice to keep
};

#endif /* NEWFILE_H */

