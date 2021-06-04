/* 
 * File:   Deck.cpp
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
 */

#include <cstdlib>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include "Deck.h"
using namespace std;

Deck::Deck() {
    //Create array of card ranks, ordered in value (3 is the lowest value, 2 is the highest
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    
    //Dynamically allocate space
    cards = new vector<pair<string, int>>;
    
    //Place 4 cards of each suit into the deck
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 4; j++) {
            cards->push_back(pair<string, int> (ranks[i], i));
        }
    }
    
    //Shuffle the deck
    random_shuffle(cards->begin(), cards->end());
    
    //Assign to the stack
    sDeck = new stack<pair<string, int>, vector<pair<string, int>>> (*cards);
}

Deck::Deck(const Deck& orig) {
}

Deck::~Deck() {
    delete cards;
    delete sDeck;
}

pair<string, int> Deck::draw() {
    //Remove a card from the top of the deck
    pair<string, int> temp = sDeck->top();
    sDeck->pop();
    return temp;
}

void Deck::insert(std::pair<std::string,int> c) {
    sDeck->push(c);
}

void Deck::resetDeck() {
    //Free up allocated space
    delete sDeck;
    
    //Reshuffle vector
    random_shuffle(cards->begin(), cards->end());
    
    //Make new stack
    sDeck = new stack<pair<string, int>, vector<pair<string, int>>> (*cards);
}