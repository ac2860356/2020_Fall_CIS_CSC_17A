/* 
 * File:   main.cpp
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
 * Purpose: Program the game
 * VERSION 5
 * To do: Clean up UI
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Deck.h"
#include "Player.h"
#include "Game.h"
using namespace std;

//User Libraries
//No Global Constants

//Function Prototypes
int menu();             //Run menu
void game();            //Run game
void instructions();    //Show how to play the game
void runDiag();         //Run game function tests

//Execution begins here
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    
    bool quit = false;
    do {
        switch(menu()) {
            case 1:
                game();
                break;
            case 2:
                instructions();
                break;
            case 3:
                runDiag();
                break;
            case 4:
                cout << "Quitting game..." << endl;
                quit = true;
                break;
            default:
                cout << "Found the secret message!" << endl;
                break;
        }
    } while(!quit);
    
    //Exit program
    return 0;
}

int menu() {
    int selection;
    do {
        cout << "1. Start a Game" << endl
             << "2. See How to Play" << endl
             << "3. Test Game Functions" << endl
             << "4. Quit Program" << endl;
        cout << "Please select an option by typing in a corresponding number: ";
        cin >> selection;
        if(selection < 1 || selection > 4) cout << endl << "That is not a valid option" << endl << endl;
    } while(selection < 1 || selection > 4);
    return selection;
}

void game() {
    int p;
    do {
        cout << "How many players are playing? (3-5 players only): ";
        cin >> p;
        if(p > 5 || p < 3) cout << endl << "That is not a valid amount of players" << endl << endl;
    } while(p > 5 || p < 3);
    
    Game *g;
    g = new Game(p);
    
    g->start();
    
    delete g;
}

void instructions() {
    cout << endl;
    cout << "Titles:" << endl;
    cout << "In the game of Tycoon, players are broken up into five different"  << endl
         << "titles: Millionaire, Noble, Commoner, Poor, and Destitute. Every"  << endl
         << "player will begin as a commoner. Richer titles will grant"         << endl 
         << "the corresponding player with benefits that hinder the poorer"     << endl
         << "titles" << endl << endl;
    cout << "Card Values:" << endl;
    cout << "In Tycoon, 2's represent the highest value card, with the Ace"     << endl
         << "being the second highest, King bing the third, etc. with 3 being"  << endl
         << "the lowest ranking card." << endl << endl;
    cout << "Playing:" << endl;
    cout << "The game of Tycoon is broken into 'tricks', which make up a round" << endl
         << "in a game. Whichever player begins a trick can play any number of" << endl
         << "cards of the same rank, given they have such in their hand. This"  << endl
         << "will determine how many matching cards of a higher face value"     << endl
         << "must be played in the trick. If the proceeding players cannot"     << endl
         << "do so, they must pass. (However, players are allowed to pass at "  << endl
         << "any time). This continues until all players pass or"               << endl
         << "a 2 is played. After which, the last player to play a card will"   << endl
         << "lead the next trick. (In the program, if all except one player"    << endl
         << "passes, the player that didn't pass will begin a new trick)."      << endl
         << "How many rounds that are played will be determined by the players,"<< endl
         << "and whoever results with the Millionaire title is deemed the "     << endl
         << "winner"<< endl << endl;
    cout << "The End of a Round:" << endl;
    cout << "When a player has played their entire hand, they do not play for"  << endl
         << "the rest of the round. The other players will continue playing"    << endl
         << "until there is one player remaining. Titles will be handed out"    << endl
         << "based on who finished their hand first, with the first player"     << endl
         << "getting the title of 'Millionaire', the second getting 'Noble',"   << endl
         << "etc. Before the next round begins after dealing, the Millionaire"  << endl
         << "will give their worst two cards to the Destitute, who has to give" << endl
         << "them their best two cards to the Millionaire. The Noble and the"   << endl
         << "Poor will do a similar process, but only with one card. The"       << endl
         << "Millionaire also has the benefit of beginning the first trick"     << endl
         << "of the next round." << endl << endl;
}

void runDiag() {
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
    cout << endl << "Testing deck reshuffling..." << endl;
    cout << endl << "Size of stack: " << pile->getDeck().size() << endl;
    
    cout << "Resetting deck..." << endl;
    pile->resetDeck();
    
    cout << "New size of stack: " << pile->getDeck().size() << endl;
    
    //*********************************
    //  Testing card dealing
    //*********************************
    cout << endl << "Testing card dealing" << endl;
    cout << endl << "Giving player hand..." << endl;
    Player p1;
    
    for(int i = 0; i < 10; i++) {
        p1.addHand(pile->draw());
    }
    
    p1.dspHand();
    
    //*************************************
    //  Testing card playing
    //*************************************
    cout << endl << "Teating card playing..." << endl;
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
    
    //******************************************
    //  Testing best/worst card pulling
    //******************************************
    cout << endl << "Testing worst/best card pulling..." << endl;
    pile->resetDeck();
    holding.clear();
    
    for(int i = 0; i < 20; i++) {
        p1.addHand(pile->draw());
    }
    
    cout << endl << "Testing best/worst card playing..." << endl;
    p1.dspHand();
    
    cout << endl << "Pulling 2 of the worst cards in the deck..." << endl;
    holding = p1.getWorst(2);
    for(list<pair<string, int>>::iterator i = holding.begin(); i != holding.end(); i++) {
        cout << setw(2) << right << i->first << " ";
    }
    cout << endl;
    
    p1.dspHand();
    
    holding.clear();
    
    cout << endl << "Pulling 2 of the best cards in the deck..." << endl;
    holding = p1.getBest(2);
    for(list<pair<string, int>>::iterator i = holding.begin(); i != holding.end(); i++) {
        cout << setw(2) << right << i->first << " ";
    }
    cout << endl;
    
    p1.dspHand();
    p1.clearHand();
    
    delete pile;
}