/* 
 * File:   main.cpp
 * Author: Arthur Choy
 * Created on December 17, 2020, 6:52 PM
 * Purpose: Create a board/card game that utilizes many of the concepts learned in class
 * Changelog:   -Got program functional
 *              -Added static member sin the form of constant integers
 *              -Removed unnecessary dynamically allocated arrays
 *              -Added scorecard display
 *              -Some of the overloaded operators had to be removed as they didn't
 *               work properly (ie. reset some of the members in an object)
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include "Game.h"
#include "Dice.h"
using namespace std;

//Global Constants
bool qToMenu;   //Whether or not the user is mid-game

//Function Prototypes
void dspMenu();         //Display menu
Game *gtPlyrs(int &);   //Get the amount and names of players
void start(Game *);     //Start the game
template <class T>
T grandTotal(T, const Game *);  //Total score of all players in game
template <class T>
T mean(T, const Game *);        //Average score between all players

//Execution Begins Here
int main(int argc, char** argv) {
    
    int input;  //Input character
    int amount; //Amount of players in game
    Game *g = nullptr;  //Game pointer
    qToMenu = false;    //Initialize quit to menu
    string msg = "That input is not valid";
    
    //Main menu
    do
    {
        dspMenu();
        cout << "Please enter the number corresponding to the option you would like: ";
        try
        {
            if(!(cin >> input)) 
            {
                cin.clear();
                cin.ignore();
                throw msg;
            }
            try 
            {
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
            catch (Game::qToMenu) //Catch whether or not player quit to menu
            {
                cout << "Quitting to menu..." << endl << endl;
                qToMenu = true;
            }
        }
        catch (string msg)
        {
            cout << "That is not a valid input" << endl << endl;
        }
    }while(input != 3); //Keep asking the user for a main menu prompt while they don't want the game to close
    
    //Delete pointer
    delete g;
    
    //Exit Program
    return 0;
}

//Function to display the menu
void dspMenu()
{
    //Display menu options
    cout << "1. Start a new game" << endl <<
            "2. Continue the current game" << endl <<
            "3. Quit Program" << endl;
    
    //Return to main
    return;
}

//*****************
// Game functions *
//*****************
//Get the names of the players in a game
Game *gtPlyrs(int &amount)
{
    bool badInput;
    //Prompt for amount of players
    do
    {
        badInput = false;
        cout << "Please enter the amount of people that will be playing: ";
        if(!(cin >> amount))
        {
            cin.clear();
            cin.ignore();
            cout << "That is not a valid input" << endl << endl;
            badInput = true;
        }
        if(amount < 1 && !badInput) cout << "That is not a valid amount of players" << endl;
    }while(amount < 1);
    
    //Dynamically create a new game
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

//Start a game
void start(Game *g) 
{
    //Try code so exceptions can be thrown
    try 
    {
        //Continue until error is throw
        while(true) 
        {
            //Print current player's name
            cout << endl;
            cout << g->plyrs[g->gtTCount()].gtName() << "'s Turn" << endl;
            
            //Start player's turn
            cout << endl;
            g->turn(g->plyrs[g->gtTCount()]);
            g->nextT(); //Increment to next turn
        }
    }
    
    catch (Game::end)   //Catch whether or not the game has ended
    {
        //Determine the winner
        g->detWin();
        
        //Determine game statistics
        int num;
        num = grandTotal(num, g);
        cout << "====== Game Statistics ======" << endl;
        cout << "Total of all players: " << num << endl;
        num = mean(num, g);
        cout << "Average Score: " << num << endl;
        cout << endl;
    }
    
    //Return from function
    return;
}

//***************************
// Game Statistic functions *
//***************************
//Template total function
template <class T>
T grandTotal(T num, const Game *g)
{
    num = 0; //Initialize number to 0
    //Add all players score totals to number
    for(int i = 0; i < g->gtPCount(); i++)
    {
        num += g->plyrs[i].gtTotal();
    }
    
    //Return number
    return num;
}

//Template average function
template <class T>
T mean(T num, const Game *g)
{
    //Divide overall total by player count and return
    return num/g->gtPCount();
}
