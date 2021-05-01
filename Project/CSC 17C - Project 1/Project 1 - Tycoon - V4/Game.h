/* 
 * File:   Game.h
 * Author: Arthur Choy
 * Created on April 27, 2021, 6:49 PM
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
    
    Game();
    Game(int);
    Game(const Game& orig);
    virtual ~Game();
    
    void start();
    void trick(std::list<Player *>::iterator &);
    void playCards(Player *);
    void prntRanks();
    void dealCards(int);
    void cardTrade();
    void resetTitles();
    
    bool badRank(std::string);
};


#endif /* GAME_H */

