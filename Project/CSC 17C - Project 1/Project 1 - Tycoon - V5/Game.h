/* 
 * File:   Game.h
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
 */

#include <queue>
#include <map>
#include <set>
#include "Deck.h"
#include "Player.h"
#ifndef GAME_H
#define GAME_H

class Game {
private:
    //Players
    std::list<Player *> *players;
    //Titles, in order from richest to poorest
    std::queue<int> titles;
    //Rounds to player, how many players have passed, how many players, how many 
    //players are still playing in a round, trick card count
    int rounds, passed, pCount, pActive, tCC;
    //Dealing deck and discard pile
    Deck drawPile, discard;
    //Key to determine value of card
    std::map<std::string, int> *key;
    //Key to determine titles
    std::map<int, std::string> *tKey;
public:
    class Passed
        { };
    
    //Constructors
    Game();
    Game(int);
    Game(const Game& orig);
    virtual ~Game();
    
    //Member functions
    void start();                                   //Start the game
    void trick(std::list<Player *>::iterator &);    //Start a trick
    void playCards(Player *);                       //Let a player plays cards
    void prntRanks();                               //Print the players and their ranks
    void dealCards(int);                            //Deal the cards to the players
    void cardTrade();                               //Initiate rank-based card trade
    void resetTitles();                             //Place titles into title queue
    bool badRank(std::string);                      //See whether a card rank exists
};


#endif /* GAME_H */

