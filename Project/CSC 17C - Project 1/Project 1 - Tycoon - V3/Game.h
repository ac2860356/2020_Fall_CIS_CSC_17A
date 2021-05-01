/* 
 * File:   Game.h
 * Author: Arthur Choy
 * Created on April 23, 2021, 12:07 AM
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
    //Rounds to player, how many players have passed, how many players, how many 
    //players are still playing in a round, trick card coun
    int rounds, passed, pCount, pActive, tCC;
    //Dealing deck and discard pile
    Deck drawPile, discard;
    //Key to determine value of card
    std::map<std::string, int> *key;
public:
    class Passed
        { };
    
    Game();
    Game(int);
    Game(const Game& orig);
    virtual ~Game();
    
    void start();
    void trick(std::list<Player *>::iterator &, std::set<int>::iterator &);
    void playCards(Player *);
    void prntRanks();
    void dealCards(int);
    
    bool badRank(std::string);
};


#endif /* GAME_H */

