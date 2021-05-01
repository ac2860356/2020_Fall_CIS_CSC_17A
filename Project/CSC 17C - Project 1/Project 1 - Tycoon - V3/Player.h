/* 
 * File:   Player.h
 * Author: Arthur Choy
 * Created on April 23, 2021, 12:07 AM
 */

#include <list>
#include <string>
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    std::list<std::pair<std::string, int>> *hand, played;
    int title;          //1-5, 1 is highest title, 5 is lowest
    std::string name;
    bool emptyHand;
public:
    //Exception class
    class BadPlay
        { };                    //Exception class for when player attempts to play cards they don't have
    
    Player();                   //Default constructor
    Player(std::string);        //Constructor
    Player(const Player& orig); //Copy constructor
    virtual ~Player();          //Destructor
    
    //Member functions
    //Player name related functions
    void setName(std::string s) { name = s; }       //Mutator for name
    std::string getName() const { return name; }    //Accessor for name
    
    //Player hand related functions
    void srtHand();                                 //Sort player's hand
    void dspHand();                                 //Display player's hand
    void addHand(std::pair<std::string, int>);      //Add a card to player's hand
    void clearHand() { hand->clear(); }             //Clear player's hand
    bool empt() const { return emptyHand; }         //See if player's hand is empty
    
    //Player title related functions
    void setTitle(int t) { title = t; }             //Mutator function for player's title
    int getTitle() const { return title; }          //Accessor function for player's title
    
    //Card playing related functions
    std::list<std::pair<std::string, int>> playCards(std::string, int); //Play a card or a group of cards
    void reject();                                                      //Reject played cards and place back in hand (potentially useless function)
};

#endif /* PLAYER_H */

