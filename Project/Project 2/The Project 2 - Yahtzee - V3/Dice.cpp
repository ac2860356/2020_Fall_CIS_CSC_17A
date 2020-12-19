/* 
 * File:   Dice.cpp
 * Author: Arthur Choy
 * Created on December 13, 2020, 1:20 AM
 */

#include "Dice.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

//Default Constructor
Dice::Dice() {
    rstScre();
    rstKeep();
    srand(static_cast<unsigned int>(time(0)));
    for(int i = 0; i < DICE_SIZE; i++) keepArr[i] = false;
}

//Destructor
Dice::~Dice() {
}

//*****************
// Dice functions *
//*****************
//******************************************************************
// Roll all die depending on which the player doesn't want to keep *
//******************************************************************
void Dice::roll() {
    for(int i = 0; i < DICE_SIZE; i++)
        if(!keepArr[i])
            diceArr[i] = rollDie(6);
    detScre();
}

//******************************************************
// Reset which dice to keep; set all elements to false *
//******************************************************
void Dice::rstKeep() {
    for(int i = 0; i < DICE_SIZE; i++)
        keepArr[i] = false;
}

//***********************************************************************
// Determine scores from dice available; store in potential score array *
//***********************************************************************
void Dice::detScre() {
    rstScre(); //Reset scores in array to be 0
    
    //Score determining functions
    sort(diceArr, diceArr + DICE_SIZE);  
    int freq = this->freq(); //Highest mode in dice array
    int seq  = this->seq();  //Longest sequence in dice array
    
    //*******************
    // Upper Categories *
    //*******************
    for(int i = 0; i < 6; i++) //Ones thru Sixes
    {
        for(int j = 0; j < DICE_SIZE; j++)
            if(diceArr[j] == i+1)
                scores[i] += diceArr[j];
    }
    
    //*******************
    // Lower Categories *
    //*******************
    if(freq >= 3 || freq == 5) //Three-of-a-Kind
    {
        for(int i = 0; i < DICE_SIZE; i++) scores[6] += diceArr[i];
    }
    
    if(freq >= 4 || freq == 5) //Four-of-a-Kind
    {
        for(int i = 0; i < DICE_SIZE; i++) scores[7] += diceArr[i];
    }
    
    if(freq == 3 || freq == 5) //Full House
    {
        if(diceArr[0] == diceArr[1] || diceArr[3] == diceArr[4] || freq == 5)
        {
            scores[8] = 25;
        }
    }
    
    if(seq >= 4 || freq == 5) //Small Straight
    {
        scores[9] = 30;
    }
    
    if(seq == 5 || freq == 5) //Large Straight
    {
        scores[10] = 40;
    }
    
    if(freq == 5) //Yahtzee
    {
        scores[11] = 50;
    }
    
    for(int i = 0; i < DICE_SIZE; i++) scores[12] += diceArr[i]; //Chance
}

//**************************
// Reset calculated scores *
//**************************
void Dice::rstScre() {
    for(int i = 0; i < SCORES_SIZE; i++)
        scores[i] = 0;
}

// Roll a dice
int Dice::rollDie(int sides) {
    int dice = rand() % sides + 1; //Choose a number between 1 and the number of sides
    return dice;                    //Return the dice value
}

//********************************************************************
// Determine which dice to keep; ask player for each individual dice *
// whether or not they want to keep it                               *
//********************************************************************
bool *Dice::keep() {
    cout << "Please enter Y/N depending whether or not you want to keep a dice" << endl;
    for(int i = 0; i < DICE_SIZE; i++) {
        char input;
        cout << "Dice " << i+1 << ": ";
        cin >> input;
        if(input == 'Y' || input == 'y') keepArr[i] = true;
    }
    
    return keepArr;
}

//*******************************
// Score Determining Functions  *
//*******************************
//************************************************
// Determine the highest dice frequency in array *
// (ie. 1, 1, 1, 1, 1 = freq of 5;               *
//  ie. 1, 1, 1, 2, 3 = freq of 3)               *
//************************************************
int Dice::freq() {
    int maxFreq = 0; //Variable holding maximum frequency
    int pos = 0;     //Variable holding position in array
    do
    {
        int freq = 0;                 //Initial frequency is 0 (for numbers that aren't present)
        int nfocus = diceArr[pos];      //Sets focus to current position in array
        for(int i = 0; i < DICE_SIZE; i++) //Goes through entire array, and sees if any values match the focus
        {
            if(nfocus == diceArr[i])freq++;
        }
        pos += freq;                    //Shift the position to next number focus (works on assumption that array has been sorted
        if(freq>maxFreq)maxFreq=freq;   //Updates or keeps max frequency
    }while(pos != DICE_SIZE);           //While the position has not hit the end of the array
    
    //Return max frequency and exit function
    return maxFreq;
}

//******************************************
// Determine longest sequence in the array *
// (ie. 1, 2, 3, 4, 5 = seq of 5;          *
//  ie. 1, 2, 3, 5, 6 = seq of 3)          *
//******************************************
int Dice::seq() {
    //Array assumed to be sorted from least to greatest
    int x = diceArr[0];                 //Declare and initialize check value
    int seq = 1, maxSeq = 1;          //Maximum sequence and sequence count (minimum of one)
    for(int i = 0; i < DICE_SIZE - 1; i++) //Check the whole array
    {
        //If the next element in the array follows the sequence, increase the sequence count
        //If the next element in the array doesn't follow the sequence, reset the count,
        //Unless it is a repeat digit, in which it will not affect the sequence count
        if(diceArr[i + 1] == diceArr[i] + 1) seq++;
        else if(diceArr[i + 1] == diceArr[i]) seq += 0;
        else seq = 1;
        x = diceArr[i+1];
        if(seq > maxSeq) maxSeq = seq; //Update or keep the maximum sequence count
    }
    
    //Return sequence value and exit function
    return seq;
}
