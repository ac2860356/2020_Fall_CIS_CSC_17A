/* 
 * File:   Game.cpp
 * Author: Arthur Choy
 * Created on December 14, 2020, 12:40 AM
 */

#include "Game.h"

//Default Constructor
Game::Game() {
    plyrs = nullptr;
    tCount = 0;
    rCount = 0;
    pCount = 0;
    keepIn = new int[DICE_SIZE];
    for(int i = 0; i < DICE_SIZE; i++) keepIn[i] = -1;
    qToMenu = false;
}

//Constructor
Game::Game(const int p) {
    plyrs = new Player[p];
    tCount = 0;
    rCount = 0;
    pCount = p;
    keepIn = new int[DICE_SIZE];
    for(int i = 0; i < DICE_SIZE; i++) keepIn[i] = -1;
    qToMenu = false;
}

//Default Copy Constructor
Game::Game(const Game& orig) {
}

//Destructor
Game::~Game() {
}

//Overloaded operator
Game Game::operator ++() {
    ++tCount;
    if(tCount >= pCount && rCount >= 13)
    {
        throw end();
    }
    if(tCount >= pCount) {
        ++rCount;
        tCount = 0;
    }
    return *this;
}

bool Game::reroll(Player &p) {
    bool dont = true;
    for(int i = 0; i < DICE_SIZE; i++) keepIn[i] = -1;
    
    std::cout << "Please enter the dice you would like to keep separated by a space: ";
    std::cin >> keepIn;
    
    bool *keep = p.keep(keepIn);
    for(int i = 0; i < DICE_SIZE; i++) if(keep[i] == false) dont = false;
    return dont;
}

void Game::turn(Player &p) {
    //Options menu constant/array
    const int SIZE = 15; //Size of options array
    std::string options[SIZE] = { "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", //String array holding all different options after dice rolling
        "Three of a Kind", "Four of a Kind", "Full House", "Small Straight",
        "Large Straight", "Yahtzee", "Chance", "Show Scorecard", "Exit to Menu" };
    int option;
    
    if(!qToMenu)
    {
        p.rstKeep();
        rlCount = 0;

        //Dice copy array
        int *copyDice = new int[5];

        bool reroll = false;
        while(rlCount < 3 && !reroll)
        {
            p.roll();
            p.rstKeep();
            copyDice = p.gtDice();
            std::cout << "Dice: ";
            for(int i = 0; i < 5; i++) std::cout << copyDice[i] << " ";
            std::cout << std::endl;
            reroll = reroll(p);
        }
    }
    qToMenu = false;
        
    bool valid = false;
    if(!valid) {
        for(int i = 0; i < SIZE; i++) std::cout << i+1 << ". " << options[i] << std::endl;
        std::cout << "Please enter the option you would like to choose: ";
        try
        {
            std::cin >> option;
            if(option > 15 || option < 1 || p.card[option].gtFill()) throw invalidOption();
            valid = true;
        }
        catch (invalidOption)
        {
            valid = false;
            std::cout << "That is not a valid option." << std::endl;
        }
    }
    
    if(option <= 13)
    {
        p.stScore(option-1);
        if(option > 6 && option < 13 && p[13] == 50) p+= 100;
    }
    else if(option == 14) std::cout << "Stub" << std::endl;
    else if(option == 15) 
    {
        qToMenu = true;
        throw(qToMenu());
    }
}

