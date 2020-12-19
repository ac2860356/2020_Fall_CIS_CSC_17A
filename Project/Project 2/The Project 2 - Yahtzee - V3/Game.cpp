/* 
 * File:   Game.cpp
 * Author: Arthur Choy
 * Created on December 14, 2020, 12:40 AM
 */


#include "Game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//****************************
// Constructors/Desctructors *
//****************************
//Default Constructor
Game::Game() {
    plyrs = new Player[0];  //No players in array
    
    //Initialize game variables to 0
    tCount = 0;             
    rCount = 0;
    pCount = 0;
    
    //Player had not quit to menu yet
    quit = false;
}

//Constructor
Game::Game(int p) {
    plyrs = new Player[p];  //Create dynamic array depending on amount of players
    
    //Initialize game variables to 0
    tCount = 0;
    rCount = 0;
    pCount = p;
    
    //Player had not quit to menu yet
    quit = false;
}

//Copy Constructor
Game::Game(const Game& obj) {
    tCount = obj.tCount;
    rCount = obj.rCount;
    pCount = obj.pCount;
    quit = obj.quit;
    plyrs = new Player[obj.pCount];
    for(int i = 0; i < obj.pCount; i++) plyrs[i] = obj.plyrs[i];
}

//Destructor
Game::~Game() {
    delete []plyrs;
}

//*****************
// Game Functions *
//*****************

//**************************************************
// Reroll function; reroll dice depending on which *
// the dice the player didn't want to keep         *
//**************************************************
bool Game::reroll(Player &p) {
    bool dont = true;       //Whether or not to reroll again      
    bool *keep = p.keep();  //Copy keep dice boolean array
    
    //If player doesn't want to keep a dice, then reroll
    for(int i = 0; i < DICE_SIZE; i++) if(keep[i] == false) dont = false;
    
    //Return whether or not to reroll
    return dont;
}

//*******************************************************
// Singular game turn (one per player in round); player *
// rolls three times and sets their dice to a category. *
// Also allows for showing of scorecard and quitting to *
// menu.                                                *
//*******************************************************
void Game::turn(Player &p) {
    //Options menu constant/array
    const int SIZE = 16; //Size of options array
    std::string options[SIZE] = { "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", //String array holding all different options after dice rolling
        "Three of a Kind", "Four of a Kind", "Full House", "Small Straight",
        "Large Straight", "Yahtzee", "Chance", "Show Scorecard", "See All Players' Cards", 
        "Exit to Menu" };
    
    //Holding variable for player input
    int option;
    
    //Dice copy array
    int *copyDice = new int[DICE_SIZE];
    
    //If the game hadn't been paused
    if(!quit)
    {
        //Player had not rolled yet
        rlCount = 0;
        
        //Roll once
        p.roll();       //Roll dice
        p.rstKeep();    //Reset dice to keep
        rlCount++;      //Player rolled once
        
        bool reroll = false;    //Initialize whether or not to reroll
        while(rlCount < 3 && !reroll) { //No more than 3 rolls, 2 rerolls
            //Copy the dice the player has to print
            for(int i = 0; i < DICE_SIZE; i++) copyDice[i] = p.gtDice(i);
            cout << "Dice: ";
            for(int i = 0; i < 5; i++) cout << copyDice[i] << " ";
            cout << endl;
            
            //Start reroll function
            reroll = this->reroll(p);
            p.roll();
            p.rstKeep();
            rlCount++;  //Increase roll count
        }
    }
    quit = false;   //Reset whether or not the game was paused
    
    bool proceed = false;   //Whether or not to end the turn
    while(!proceed) {
        //Redisplay dice for convenience
        cout << "Dice: ";
        for(int i = 0; i < 5; i++) cout << copyDice[i] << " ";
        cout << endl << endl;
        
        //Present options
        for(int i = 0; i < SIZE; i++) std::cout << i+1 << ". " << options[i] << std::endl;
        
        //Prompt for option
        cout << "Please enter the option you would like to choose: ";
        
        //Get option, if player inputs something that isn't an integer, an option,
        //or an unfilled category, throw exception
        try
        {
            if(!(cin >> option)) 
            {
                cin.clear();
                cin.ignore();
                throw invalidOption();
            }
            if(option > 16 || option < 1 || p.card[option-1].gtFill()) throw invalidOption();
            proceed = true;
        }
        catch (Game::invalidOption) //Exception catch for invalid options
        {
            proceed = false;
            cout << "That is not a valid option." << endl << endl;
        }
        
        if(option = 15) 
        {
            cout << "Which player would you like to see the scorecard of?" << endl;
            for(int i = 0; i < this->pCount; i++)
            {
                cout << i+1 << ". " << this->plyrs[i].gtName() << endl;
            }
            int input;
            try
            {
                if(!(cin >> input))
                {
                    cin.clear();
                    cin.ignore();
                    throw invalidOption;
                }
                else if(input < 1 || input+1 > this->pCount) throw invalidOption();
                dspCard(this->plyrs[input-1]);
            }
            catch (Game::invalidOption)
            {
                cout << "That is not a valid option" << endl << endl;
            }
            proceed = false;
        }
        
        //If option is to display the player's scorecard, display the scorecard
        //and set to repeat options menu
        if(option == 14) 
        {
            dspCard(p);
            proceed = false;
        }
    }
    
    //Delete copy
    delete []copyDice;
    
    //If option involves a score, set it
    if(option <= 13)
    {
        p.stCat(option-1);
        if(option > 6 && option < 13 && p[13] == 50 && p.freq() == 5) p.addTotal(100);
    }
    
    //If option is to quit to the menu, throw exception
    else if(option == 16) 
    {
        quit = true;    //Set quit to menu flag to true
        throw qToMenu();
    }
}

//****************************************
// Move on to next turn, move on to next *
// round if all turns in round are over. *
//****************************************
void Game::nextT() {
    //Increase turn count
    tCount++;
    
    //If all turns have passed in the last round, throw an end of game exception
    if(tCount >= pCount && rCount >= 12) {
        throw end();
    }
    
    //If all player turns have passed in a round, move to next round
    if(tCount >= pCount) {
        rCount++;
        tCount = 0;
    }
}

//**************************************************
// Display player's scorecard, along with progress *
// to upper category bonus and score total.        *
//**************************************************
void Game::dspCard(Player p) {
    //String array holding name of all categories
    string cats[13] = { "Ones", "Twos", "Threes", "Fours",
                        "Fives", "Sixes", "3-of-a-Kind", "4-of-a-Kind",
                        "Full House", "Small Straight", "Large Straight",
                        "Yahtzee", "Chance" };
    cout << endl;
    cout << p.gtName() << "'s Scorecard" << endl;
    
    //Display scores of upper category
    cout << "====== Upper Categories ======" << endl;
    for(int i = 0; i < 6; i++) cout << cats[i] << ": " << p[i] << endl;
    cout << endl;
    
    //Calculate player's upper category bonus 
    int upper = 0;
    for(int i = 0; i < 6; i++) upper += p[i];
    if(upper >  63) upper = 63;
    cout << "Upper Category Bonus: " << upper << "/63" << endl << endl;
    
    //Display scores of lower category
    cout << "====== Lower Categories ======" << endl;
    for(int i = 6; i < 13; i++) cout << cats[i] << ": " << p[i] << endl;
    cout << endl;
    
    //Display total
    cout << "Total Score: " << p.gtTotal() << endl << endl;
}

//**************************************
// Determine which player won the game *
//**************************************
void Game::detWin() {
    int winner = 0; //Initialize which player won the game
    
    //Compare total scores
    for(int i = 0; i < pCount-1; i++) {
        if(plyrs[i] > plyrs[winner]) winner = i;
    }
    
    //Display player that won game
    cout << endl;
    cout << plyrs[winner].gtName() << " wins the game!" << endl;
    cout << endl;
}