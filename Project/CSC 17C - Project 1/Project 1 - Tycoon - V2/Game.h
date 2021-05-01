/* 
 * File:   Game.h
 * Author: Arthur Choy
 * Created on April 21, 2021, 4:24 PM
 */

#include <queue>
#include <map>
#include "Deck.h"
#include "Player.h"
#ifndef GAME_H
#define GAME_H

class Game {
private:
    //Players
    std::list<Player *> *players;
    //Queue ordering the players who won first
    std::queue<Player *> *won;
    //Rounds to player, how many players have passed, how many players, how many 
    //players are still playing in a round, trick card count
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
    
    void round();
    void trick();
    void playCards(Player *);
    
    bool badRank(std::string);
};

#endif /* GAME_H */

