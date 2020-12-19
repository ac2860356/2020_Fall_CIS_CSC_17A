/* 
 * File:   Game.cpp
 * Author: Arthur Choy
 * Created on December 14, 2020, 12:40 AM
 */


#include "Game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//Default Constructor
Game::Game() {
    plyrs = new Player[0];
    tCount = 0;
    rCount = 0;
    pCount = 0;
    quit = false;
}

//Constructor
Game::Game(int p) {
    plyrs = new Player[p];
    tCount = 0;
    rCount = 0;
    pCount = p;
    quit = false;
}

//Destructor
Game::~Game() {
    delete []plyrs;
}

bool Game::reroll(Player &p) {
    bool dont = true;
    int *keepIn = new int[DICE_SIZE];
    for(int i = 0; i < DICE_SIZE; i++) keepIn[i] = -1;
    
    
    cout << "Please enter the dice you would like to keep separated by a space: ";
    for(int i = 0; i < DICE_SIZE; i++) { 
        cin >> keepIn[i];
        if(keepIn[i] > 5 || keepIn[i] < 1) keepIn[i] = -1;
    }
        
    bool *keep = p.keep(keepIn);
    for(int i = 0; i < DICE_SIZE; i++) if(keep[i] == false) dont = false;
    delete []keepIn;
    return dont;
}

void Game::turn(Player &p) {
    //Options menu constant/array
    const int SIZE = 15; //Size of options array
    std::string options[SIZE] = { "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", //String array holding all different options after dice rolling
        "Three of a Kind", "Four of a Kind", "Full House", "Small Straight",
        "Large Straight", "Yahtzee", "Chance", "Show Scorecard", "Exit to Menu" };
    int option;
    
    //Dice copy array
    int *copyDice = new int[DICE_SIZE];
    
    if(!quit)
    {
        p.rstKeep();
        rlCount = 0;

        

        bool reroll = false;
        while(rlCount < 3 && !reroll)
        {
            p.roll();
            p.rstKeep();
            for(int i = 0; i < DICE_SIZE; i++) copyDice[i] = p.gtDice(i);
            cout << "Dice: ";
            for(int i = 0; i < 5; i++) cout << copyDice[i] << " ";
            cout << endl;
            reroll = this->reroll(p);
        }
    }
    quit = false;
        
    bool proceed = false;
    while(!proceed) {
        cout << "Dice: ";
        for(int i = 0; i < 5; i++) cout << copyDice[i] << " ";
        cout << endl << endl;
        for(int i = 0; i < SIZE; i++) std::cout << i+1 << ". " << options[i] << std::endl;
        std::cout << "Please enter the option you would like to choose: ";
        try
        {
            cin >> option;
            if(option > 15 || option < 1 || p.card[option-1].gtFill()) throw invalidOption();
            proceed = true;
        }
        catch (Game::invalidOption)
        {
            proceed = false;
            cout << "That is not a valid option." << endl << endl;
        }
        if(option == 14) {
            dspCard(p);
            proceed = false;
        }
    }
    
    delete []copyDice;
    
    if(option <= 13)
    {
        p.stCat(option-1);
        if(option > 6 && option < 13 && p[13] == 50 && p.freq() == 5) p.addTotal(100);
    }
    else if(option == 15) 
    {
        quit = true;
        throw qToMenu();
    }
}

void Game::nextT() {
    tCount++;
    if(tCount >= pCount && rCount >= 13)
    {
        throw end();
    }
    if(tCount >= pCount) {
        rCount++;
        tCount = 0;
    }
}

void Game::dspCard(Player p) {
    string cats[13] = { "Ones", "Twos", "Threes", "Fours",
                        "Fives", "Sixes", "3-of-a-Kind", "4-of-a-Kind",
                        "Full House", "Small Straight", "Large Straight",
                        "Yahtzee", "Chance" };
    cout << endl;
    cout << p.gtName() << "'s Scorecard" << endl;
    cout << "====== Upper Categories ======" << endl;
    for(int i = 0; i < 6; i++) cout << cats[i] << ": " << p[i] << endl;
    cout << endl;
    cout << "====== Lower Categories ======" << endl;
    for(int i = 6; i < 13; i++) cout << cats[i] << ": " << p[i] << endl;
    cout << endl;
}