/* 
 * File:   main.cpp
 * Author: Arthur Choy
 * Created on April 23, 2021, 12:07 AM
 * Purpose: Program the game
 * VERSION 3
 * To do: fully implement rounds and player titles
 *        begin thinking about write-up
 *        fix bugs (refer to version 2)
 * Changelog: Implemented rounds and player titles
 *            Rounds past the first will begin on the highest ranking player
 *            Re-did tricks and how players who finished their hand are dealt with internally
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include "Deck.h"
#include "Player.h"
#include "Game.h"
using namespace std;

//User Libraries
//No Global Constants

//Function Prototypes

//Execution begins here
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    
    //***********************************
    //  Create and shuffle deck
    //***********************************
    cout << "Creating and shuffling deck..." << endl;
    Deck *pile;
    pile = new Deck;
    
    for(int i = 0; i < 3; i++) { 
        cout << endl << "Pulling card from deck..." << endl;
        pair<string, int> temp;
        temp = pile->draw();

        cout << "Rank of pulled card: " << temp.first << endl;
        cout << "Value of pulled card: " << temp.second << endl;
    }
    
    //********************************************
    //  Test deck reshuffling
    //********************************************
    cout << endl << "Size of stack: " << pile->getDeck().size() << endl;
    
    cout << "Resetting deck..." << endl;
    pile->resetDeck();
    
    cout << "New size of stack: " << pile->getDeck().size() << endl;
    
    //*********************************
    //  Testing card dealing
    //*********************************
    cout << endl <<"Giving player hand..." << endl;
    Player p1;
    
    for(int i = 0; i < 10; i++) {
        p1.addHand(pile->draw());
    }
    
    p1.dspHand();
    
    //*************************************
    //  Testing card playing
    //*************************************
    string rank;
    int amount;
    bool good2Go;
    list<pair<string, int>> holding;
    do {
        cout << "Please enter the rank of the card(s) you want to play: ";
        cin >> rank;
        cout << "Please enter the amount of cards you want to play: ";
        cin >> amount;
        try {
            holding = p1.playCards(rank, amount);
            good2Go = true;
        }
        catch (Player::BadPlay) {
            cout << "You don't have that card in your deck" << endl;
            good2Go = false;
        }
    } while(!good2Go);
    for(list<pair<string, int>>::iterator i = holding.begin(); i != holding.end(); i++) {
        cout << i->first << endl;
    }
    
    p1.dspHand();
    p1.clearHand();

    //************************
    //  Testing Game class
    //************************
    Game *g;
    g = new Game(4);
    
    g->start();
    
    
    //Recover allocated space
    delete pile;
    return 0;
}

