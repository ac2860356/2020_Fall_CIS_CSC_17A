/* 
 * File:   Deck.h
 * Author: Arthur Choy
 * Created on April 15, 2021, 1:55 PM
 */

#include <vector>
#include <stack>
#ifndef DECK_H
#define DECK_H

class Deck {
private:
    std::vector<std::pair<std::string, int>> *cards;    //Vector of cards to shuffle
    std::stack<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>> *sDeck;   //Shuffled deck
public:
    Deck();                 //Default constructor
    Deck(const Deck& orig); //Copy constructor
    virtual ~Deck();        //Destructor
    
    //Member functions
    std::pair<std::string, int> draw();     //Draw a card from the deck
    std::stack<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>> getDeck() { return *sDeck; }
    void resetDeck();
};

#endif /* DECK_H */

