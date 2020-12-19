/* 
 * File:   main.cpp
 * Author: Arthur Choy
 * Created on December 10, 2020, 11:52 PM
 * Purpose: Create a board/card game that utilizes many of the concepts learned in class
 * Changelog: Converted nearly 75% of the program to classes/class functions
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Game.h"
using namespace std;

//Global Constants
bool qToMenu;   //Whether or not the user is mid-game

//Function Prototypes
void dspMenu();                    //Display menu
Game *gtPlyrs(int &);               //Get the amount and names of players
void start(Game *);                //Start the game

//Execution Begins Here
int main(int argc, char** argv) {
    
    int input;  //Input character
    int amount; //Amount of players in game
    Game *g = nullptr;
    qToMenu = false;
    
    //Main menu
    do
    {
        dspMenu();
        cout << "Please enter the number corresponding to the option you would like: ";
        cin >> input;
        try {
            switch(input)
            {
                case 1: //Start a new game
                    if(qToMenu) //If they were in the middle of a game, ask them if they want to overwrite it
                    {
                        cout << "This will overwrite the current game, " <<
                                "are you sure you want to continue? (Y/N): ";
                        char confirm;
                        cin >> confirm;
                        if(confirm == 'N' || confirm == 'n') break;
                    }

                    //Get players and initialize
                    g = gtPlyrs(amount);
                    qToMenu = false; //Signify user started a new game
                    //Begin the game
                    start(g); //Start the game
                    break;
                case 2: //Continue game
                    if(qToMenu) //Only allow option if user was in the middle of the game
                    {
                        qToMenu = false;
                        start(g);
                    }
                    //Else, tell them they are not in the middle of a game
                    else cout << "There is currently no game loaded into the program." << endl;
                    break;
                case 3: //Quit the program 
                    cout << "Quitting Program..." << endl;
                    break;
                default: //Inform the user of an invalid input 
                    cout << "That is not a valid input" << endl;
                    break;
            }
        }
        catch (Game::qToMenu)
        {
            cout << "Quitting to menu..." << endl << endl;
            qToMenu = true;
        }
    }while(input != 3); //Keep asking the user for a main menu prompt while they don't want the game to close
    
    delete g;
    
    //Exit Program
    return 0;
}

void dspMenu()
{
    //Display menu options
    cout << "1. Start a new game" << endl <<
            "2. Continue the current game" << endl <<
            "3. Quit Program" << endl;
    
    //Return to main
    return;
}

Game *gtPlyrs(int &amount)
{
    //Prompt for amount of players
    do
    {
        cout << "Please enter the amount of people that will be playing: ";
        cin >> amount;
        if(amount < 1) cout << "That is not a valid amount of players" << endl;
    }while(amount < 1);

    Game *g = new Game(amount);


    cin.ignore(); //Clear input

    //Ask for names of players
    for(int i = 0; i < amount; i++)
    {
        cout << "Please enter the name for player " << i + 1 << ": ";
        string name;
        getline(cin, name);
        g->plyrs[i].stName(name);
    }
    
    //Return game to main function
    return g;
}

void start(Game *g) {
    try {
        while(true) {
            cout << g->plyrs[g->gtTCount()].gtName() << "'s Turn" << endl;
            g->turn(g->plyrs[g->gtTCount()]);
            g->nextT();
        }
    }
    
    catch (Game::end) {
        cout << "Stub" << endl;
    }
    
    return;
}
