/* 
 * File:   Game.cpp
 * Author: Arthur Choy
 * Created on April 21, 2021, 4:24 PM
 */

#include <iostream>
#include <algorithm>
#include <unordered_set>
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
    pCount = p;
    pActive = pCount;
    players = new std::list<Player *>;
    won = new std::queue<Player *>;
    for(int i = 0; i < pCount; i++) {
        std::string tempName;
        cout << "Please enter the name for player " << i+1 << ": ";
        cin >> tempName;
        players->push_front(new Player(tempName));
    }
    //random_shuffle(players->begin(), players->end());
    
    cout << "Please enter the amount of rounds to be played: ";
    int temp;
    cin >> temp;
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
    delete won;
    delete key;
}

void Game::round() {
    for(int i = 0; i < 10; i++) {
        for(std::list<Player *>::iterator j = players->begin(); j != players->end(); j++) {
            (*j)->addHand(drawPile.draw());
        }
    }
    
    trick();
    cout << "Trick end" << endl;
}

void Game::trick() {
    passed = 0;
    tCC = 0;
    std::list<Player *>::iterator i = players->begin();
    do {
        if(i == players->end()) i = players->begin();
        if((*i)->empt()) {
            pActive--;
            won->push(*i);
            players->erase(i);
        }
        else {
            try {
                playCards((*i));
            }
            catch (Game::Passed) {
                passed++;
            }
        }
        i++;
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

bool Game::badRank(std::string s) {
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) if(s == ranks[i]) return false;
    return true;
}