/* 
 * File:   Player.h
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
 */

#include <list>
#include <string>
#include "AVLTree.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    AVLTree *hand;
    std::list<std::pair<std::string, int>> played;
    int title;          //1-5, 1 is highest title, 5 is lowest
    std::string name;
    bool emptyHand;
public:
    //Exception class
    class BadPlay
        { };                    //Exception class for when player attempts to play cards they don't have
        
    struct cmp {
        bool operator() (const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs) const
        { return lhs.second > rhs.second; }
    };
    
    Player();                   //Default constructor
    Player(std::string);        //Constructor
    Player(const Player& orig); //Copy constructor
    virtual ~Player();          //Destructor
    
    //Member functions
    //Player name related functions
    void setName(std::string s) { name = s; }       //Mutator for name
    std::string getName() const { return name; }    //Accessor for name
    
    //Player hand related functions
    void dspHand();                                 //Display player's hand
    void dspSHand();                                //Display player's sorted hand
    void addHand(std::pair<std::string, int>);      //Add a card to player's hand
    void clearHand() { hand->clear(); }             //Clear player's hand
    bool empt() const { return emptyHand; }         //See if player's hand is empty
    
    //Player title related functions
    void setTitle(int t) { title = t; }             //Mutator function for player's title
    int getTitle() const { return title; }          //Accessor function for player's title
    
    //Card playing related functions
    std::list<std::pair<std::string, int>> playCards(std::string, int); //Play a card or a group of cards
    std::list<std::pair<std::string, int>> getBest(int);                //Get a certain amount of the best cards in the hand
    std::list<std::pair<std::string, int>> getWorst(int);               //Get a certain amount of the worst cards in the hand
    void reject();                                                      //Reject played cards and place back in hand (potentially useless function)
};

#endif /* PLAYER_H */

