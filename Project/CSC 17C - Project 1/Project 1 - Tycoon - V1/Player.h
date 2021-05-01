/* 
 * File:   Player.h
 * Author: Arthur Choy
 * Created on April 16, 2021, 2:13 PM
 */

#include <list>
#include <string>
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    std::list<std::pair<std::string, int>> *hand, played;
    int place;
    std::string name;
    bool emptyHand;
public:
    Player();                   //Default constructor
    Player(std::string);        //Constructor
    Player(const Player& orig); //Copy constructor
    virtual ~Player();          //Destructor
    
    //Member functions
    void srtHand();                                  //Sort player's hand
    void dspHand();                                  //Display player's hand
    void addHand(std::pair<std::string, int>);       //Add a card to player's hand
    std::list<std::pair<std::string, int>> playCards(std::string, int); //Play a card or a group of cards
};

#endif /* PLAYER_H */

