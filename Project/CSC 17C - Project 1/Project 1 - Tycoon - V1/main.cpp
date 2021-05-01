/* 
 * File:   main.cpp
 * Author: Arthur Choy
 * Created on April 13, 2021, 2:19 PM
 * Purpose: Program the core features of the game
 * VERSION 1
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include "Deck.h"
#include "Player.h"
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
    cout << "Please enter the rank of the card(s) you want to play: ";
    cin >> rank;
    cout << "Please enter the amount of cards you want to play: ";
    cin >> amount;
    list<pair<string, int>> holding = p1.playCards(rank, amount);
    
    for(list<pair<string, int>>::iterator i = holding.begin(); i != holding.end(); i++) {
        cout << (*i).first << endl;
    }
    
    p1.dspHand();
    
    //Recover allocated space
    delete pile;
    return 0;
}

