/* 
 * File:   Game.cpp
 * Author: Arthur Choy
 * Created on April 23, 2021, 12:07 AM
 */

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include "Game.h"
using namespace std;

Game::Game() {
    players = new std::list<Player *>;
    rounds = 0;
    pCount = 0;
    pActive = 0;
    passed  = 0;
    tCC = 0;

    key = new std::map<std::string, int>;
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) {
        key->insert(pair<std::string, int>(ranks[i], i));
    }
}

Game::Game(int p) {
    players = new std::list<Player *>;
    pCount = p;
    pActive = pCount;
    for(int i = 0; i < pCount; i++) {
        std::string tempName;
        cout << "Please enter the name for player " << i+1 << ": ";
        cin >> tempName;
        players->push_back(new Player(tempName));
    }
    
    int temp;
    do {
        cout << "Please enter the amount of rounds to be played: ";
        cin >> temp;
        if(temp < 1) cout << endl << "That is not a valid amount of rounds" << endl << endl;
    } while(temp < 1);
    rounds = temp;
    passed = 0;
    tCC = 0;
    
    key = new std::map<std::string, int>;
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) {
        key->insert(pair<std::string, int>(ranks[i], i));
    }
}

Game::Game(const Game& orig) {
}

Game::~Game() {
    for(std::list<Player *>::iterator i = players->begin(); i != players->end(); i++) {
        delete *i;
    }
    delete players;
    delete key;
}

void Game::start() {
    std::set<int> titles;   //Set holding titles
    for(int i = 0; i < pCount; i++) titles.insert(i+1); //Place title values
    
    //Get how many cards will be in each player's hand
    int cInHand;
    do {
        cout << "How many cards in a hand (max " << 52/pCount << " per player): ";
        cin >> cInHand;
        if(cInHand < 1 || cInHand > 52/pCount) cout << endl << "That is not a valid amount of cards" << endl << endl;
    } while(cInHand < 1 || cInHand > 52/pCount);
    
    //Play as many rounds as specified
    int r = 0;  //How many rounds have passed
    do {
        dealCards(cInHand); //Deal cards
        r++;                //Increment what round it is
        pActive = pCount;   //Reset active players
        std::set<int>::iterator t = titles.begin();         //Reset title iterator
        std::list<Player *>::iterator i = players->begin(); //Reset player iterator
        
        //If it's not the first round, begin the round on the highest ranking player
        if(r > 1) {
            for(i = players->begin(); i != players->end(); i++) {
                if((*i)->getTitle() == 1) break;
            }
        }
        
        //Play tricks until all except one player has finished their hand
        do {
            cout << endl << "A new trick begins" << endl;
            trick(i, t);
        } while(pActive > 1);
        
        //Set the title of the last player
        for(i = players->begin(); i != players->end(); i++) {
            if(!(*i)->empt()) (*i)->setTitle(*t);
        }
        t++;
        
        //Print the players in order of rank
        prntRanks();
    } while(r != rounds);
}

void Game::trick(std::list<Player *>::iterator &i, std::set<int>::iterator &t) {
    passed = 0; //How many players have passed
    tCC = 0;    //The amount of cards that are to be played in a trick
    
    //Go through the players until all except 1 have passed
    do {
        //If the player's hand wasn't already empty
        if(!(*i)->empt()) {
            //Try having player play cards unless the pass, then send exception
            try {
                playCards(*i);
                passed = 0;     //Reset count of players passed
            }
            //If player passed, increase pass count
            catch (Game::Passed) {
                passed++;
            }
            //If the player finished their hand
            if((*i)->empt()) {
                pActive--;          //Remove them from active players
                (*i)->setTitle(*t); //Hand them their title
                t++;                //Increase title iterator
            }
        }
        i++;    //Move to next player
        
        //+++++++++++++++++++++++++++++++++
        // TEST OUTPUT, DELETE LATER
        //++++++++++++++++++++++++++++++++++
        cout << "passed: " << passed << endl;   
        cout << "pActive: " << pActive << endl;
        
        //If the iterator makes it to the end of the player list, return to the beginning
        if(i == players->end()) i = players->begin();
    } while(passed != pActive-1);
}

void Game::playCards(Player *p) {
    cout << p->getName() << "'s Turn" << endl;
    p->dspHand();
    std::string rank;
    int amount;
    bool good2Go = true;
    std::list<std::pair<std::string, int>> *holding = new std::list<std::pair<std::string, int>>;
    
    //The horrible, no good, very bad nested do-while loops
    do {
        //If player is first to play in trick
        if(tCC == 0) {
            //See if player is attempting to play a valid rank
            do {
                cout << "Please enter the rank of the card you want to play (if you want to pass, type Pass): ";
                cin >> rank;
                if(rank == "Pass") throw Passed();
                if(badRank(rank)) cout << "That is not a valid rank" << endl;
            } while(badRank(rank));
            //See if player is attempting to play a valid amount of cards (not necessarily what they have)
            do {
                cout << "Please enter the amount of cards of this rank you want to play (inputs higher than the amount you have will play all of them): ";
                cin >> amount;
                if(amount > 4 || amount < 1) cout << "That is not a valid amount of cards" << endl;
            } while(amount > 4 || amount < 1);
        }
        //If player is continuing trick
        else {
            //See if player is attempting to play a valid amount of cards that are in sequence
            do {
                //See if player is attempting to play a valid rank
                do {
                    cout << "Please enter the rank of the card you want to play (if you want to pass, type Pass): ";
                    cin >> rank;
                    if(rank == "Pass") throw Passed();
                    if(badRank(rank)) cout << "That is not a valid rank" << endl;
                } while(badRank(rank));
                //See if player is attempting to play a valid amount of cards (not necessaril what they have)
                do {
                    cout << "Please enter the amount of cards of this rank you want to play (inputs higher than the amount you have will play all of them): ";
                    cin >> amount;
                    if(amount > 4 || amount < 1) cout << "That is not a valid amount of cards" << endl;
                } while(amount > 4 || amount < 1);
                if(key->find(rank)->second <= discard.getDeck().top().second) cout << "Must play a rank whose value is higher than the previously played cards" << endl;
                if(amount != tCC) cout << "Must play the same number of cards that was previously played" << endl;
            } while(key->find(rank)->second <= discard.getDeck().top().second || amount != tCC);
        }
        //Throw exception if playing cards player doesn't have
        try {
            *holding = p->playCards(rank, amount);
            good2Go = true;
        }
        catch (Player::BadPlay) {
            cout << "You don't have that card in your deck" << endl;
            good2Go = false;
        }
    } while(!good2Go); //Make sure the player is playing cards they have
    
    //Set the amount of cards played
    tCC = amount;
    
    for(std::list<std::pair<std::string, int>>::iterator i = holding->begin(); i != holding->end(); i++) {
        discard.insert((*i));
        
        //++++++++++++++++++++++++++++++++++
        //  TEST OUTPUT, DELETE LATER
        //++++++++++++++++++++++++++++++++++
        cout << (*i).first << endl;
    }
    
    delete holding;
}

void Game::prntRanks() {
    std::list<Player *>::iterator j;
    for(int i = 0; i < pCount; i++) {
        for(j = players->begin(); j != players->end(); j++) {
            if((*j)->getTitle() == i+1) break;
        }
        cout << (*j)->getTitle() << ". " << (*j)->getName() << endl;
    }
}

void Game::dealCards(int a) {
    drawPile.resetDeck();
    for(int i = 0; i < a; i++) {
        for(std::list<Player *>::iterator j = players->begin(); j != players->end(); j++) {
            (*j)->addHand(drawPile.draw());
        }
    }
}

bool Game::badRank(std::string s) {
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) if(s == ranks[i]) return false;
    return true;
}