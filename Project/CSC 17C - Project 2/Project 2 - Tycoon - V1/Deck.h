/* 
 * File:   Deck.h
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
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
    std::stack<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>> getDeck() const { return *sDeck; }
    void insert(std::pair<std::string, int>);
    void resetDeck();
};

#endif /* DECK_H */

