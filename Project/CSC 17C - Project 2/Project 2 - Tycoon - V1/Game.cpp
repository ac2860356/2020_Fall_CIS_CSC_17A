/* 
 * File:   Game.cpp
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
 */

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include "Game.h"
using namespace std;

Game::Game() {
    //Default constructor, shouldn't really occur, vestigial?
    players = new std::list<Player *>;
    rounds = 0;
    pCount = 0;
    pActive = 0;
    tCC = 0;

    key = new std::map<std::string, int>;
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) {
        key->insert(pair<std::string, int>(ranks[i], i));
    }
    tKey = new std::map<int, std::string>;
    string t[] = { "Millionaire", "Noble", "Commoner", "Poor", "Destitute" };
    for(int i = 0; i < 5; i++) {
        tKey->insert(pair<int, std::string>(i+1, t[i]));
    }
}

Game::Game(int p) {
    //Initialize list of players
    players = new std::list<Player *>;
    pCount = p;
    pActive = pCount;
    for(int i = 0; i < pCount; i++) {
        std::string tempName;
        cout << "Please enter the name for player " << i+1 << ": ";
        cin >> tempName;
        players->push_back(new Player(tempName));
    }
    
    //Get amount of rounds played
    int temp;
    do {
        cout << "Please enter the amount of rounds to be played: ";
        cin >> temp;
        if(temp < 1) cout << endl << "That is not a valid amount of rounds" << endl << endl;
    } while(temp < 1);
    rounds = temp;
    tCC = 0;
    
    //Initialize keys
    key = new std::map<std::string, int>;
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) {
        key->insert(pair<std::string, int>(ranks[i], i));
    }
    tKey = new std::map<int, std::string>;
    string t[] = { "Millionaire", "Noble", "Commoner", "Poor", "Destitute" };
    for(int i = 0; i < 5; i++) {
        tKey->insert(pair<int, std::string>(i+1, t[i]));
    }
}

Game::Game(const Game& orig) {
}

Game::~Game() {
    //Recover allocated memory
    for(std::list<Player *>::iterator i = players->begin(); i != players->end(); i++) {
        delete *i;
    }
    delete players;
    delete key;
    delete tKey;
}

void Game::start() {
    resetTitles();  //Reset title queue
    
    //Get how many cards will be in each player's hand
    int cInHand;
    do {
        cout << "Please enter the cards in a hand (max " << 52/pCount << " per player, min 3): ";
        cin >> cInHand;
        if(cInHand < 3 || cInHand > 52/pCount) cout << endl << "That is not a valid amount of cards" << endl << endl;
    } while(cInHand < 3 || cInHand > 52/pCount);
    
    //Play as many rounds as specified
    int r = 0;  //How many rounds have passed
    do {
        dealCards(cInHand);     //Deal cards
        r++;                    //Increment what round it is
        if(r > 1) { 
            cardTrade();        //Initiate the card trade
        }
        
        pActive = pCount;       //Reset active players
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
            tCC = 0;    //The amount of cards that are to be played in a trick
            trick(i, 0);
        } while(pActive > 1);
        
        //Set the title of the last player
        for(i = players->begin(); i != players->end(); i++) {
            if(!(*i)->empt()) (*i)->setTitle(titles.front());
        }
        
        //Reset player hands
        for(i = players->begin(); i != players->end(); i++) {
            (*i)->clearHand();
        }
        resetTitles();
        
        //Print the players in order of rank
        prntRanks();
    } while(r != rounds);
}

void Game::trick(std::list<Player *>::iterator &i, int p) {
    //Go through the players until all except 1 have passed
    if(p == pActive-1) return;
    
    //If the player's hand wasn't already empty
    if(!(*i)->empt()) {
        //Try having player play cards unless the pass, then send exception
        try {
            playCards(*i);
            p = 0;     //Reset count of players passed
        }
        //If player passed, increase pass count
        catch (Game::Passed) {
            cout << endl;
            p++;
        }
        //If the player finished their hand
        if((*i)->empt()) {
            pActive--;                      //Remove them from active players
            (*i)->setTitle(titles.front()); //Hand them their title
            titles.pop();
        }
    }
    i++;    //Move to next player

    //If the iterator makes it to the end of the player list, return to the beginning
    if(i == players->end()) i = players->begin();
    
    //Call next trick recursively
    trick(i, p);
}

void Game::playCards(Player *p) {
    cout << p->getName() << "'s Turn" << endl;
    p->dspHand();
    std::string rank;
    int amount;
    bool good2Go = true, sorted = false;
    std::list<std::pair<std::string, int>> *holding = new std::list<std::pair<std::string, int>>;
    
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //  The horrible, no good, very bad nested do-while loops
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    do {
        //If player is first to play in trick
        if(tCC == 0) {
            //See if player is attempting to play a valid rank
            do {
                sorted = false;
                cout << "Please enter the rank of the card you want to play (if you want to pass, type Pass; if you want to sort your hand, type Sort): ";
                cin >> rank;
                if(rank == "Pass") throw Passed();
                if(rank == "Sort") {
                    sorted = true;
                    p->srtHand();
                    cout << "Sorting hand..." << endl;
                    p->dspHand();
                }
                else if(badRank(rank)) cout << "That is not a valid rank" << endl;
            } while(badRank(rank) || sorted);
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
                    sorted = false;
                    cout << "Please enter the rank of the card you want to play (if you want to pass, type Pass; if you want to sort your hand, type Sort): ";
                    cin >> rank;
                    if(rank == "Pass") throw Passed();
                    if(rank == "Sort") {
                        sorted = true;
                        p->srtHand();
                        cout << "Sorting hand..." << endl;
                        p->dspHand();
                    }
                    else if(badRank(rank)) cout << endl << "That is not a valid rank" << endl << endl;
                } while(badRank(rank) || sorted);
                //See if player is attempting to play a valid amount of cards (not necessarily what they have)
                do {
                    cout << "Please enter the amount of cards of this rank you want to play (inputs higher than the amount you have will play all of them): ";
                    cin >> amount;
                    if(amount > 4 || amount < 1) cout << endl << "That is not a valid amount of cards" << endl << endl;
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
            cout << endl << "You don't have that card in your deck" << endl << endl;
            good2Go = false;
        }
    } while(!good2Go); //Make sure the player is playing cards they have
    
    //Set the amount of cards played
    tCC = amount;
    
    for(std::list<std::pair<std::string, int>>::iterator i = holding->begin(); i != holding->end(); i++) {
        discard.insert((*i));      
        cout << "Played cards: " << (*i).first << " ";
    }
    cout << endl << endl;
    
    delete holding;
}

void Game::prntRanks() {
    for(std::list<Player *>::iterator i = players->begin(); i != players->end(); i++) {
        cout << tKey->find((*i)->getTitle())->second << ": " << (*i)->getName() << endl;
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

void Game::cardTrade() {
    //Two iterators for finding the player at an advantage against a corresponding player, based on rank
    std::list<Player *>::iterator advan, disadvan;
    
    //Proxy lists that hold the cards of the players at advantage/disadvantage
    std::list<std::pair<std::string, int>> *holdingA = new std::list<std::pair<std::string, int>>;
    std::list<std::pair<std::string, int>> *holdingD = new std::list<std::pair<std::string, int>>;
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  Change the card trade based on the number of players present
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    switch(pCount) {
        case 3 :    //Three players: Millionaire, Commoner, and Destitute
            //Find the Millionaire and the Destitute
            for(advan = players->begin(); advan != players->end(); advan++) if((*advan)->getTitle() == 1) break;
            for(disadvan = players->begin(); disadvan != players->end(); disadvan++) if((*disadvan)->getTitle() == 5) break;
            
            //The Millionaire gets to trade their worst two cards with the Destitute
            *holdingA = (*advan)->getWorst(2);
            //The Destitute has to trade their best two cards to the Millionaire
            *holdingD = (*disadvan)->getBest(2);
            
            //Swap cards
            for(std::list<std::pair<std::string, int>>::iterator i = holdingA->begin(); i != holdingA->end(); i++) {
                (*disadvan)->addHand((*i));
            }
            for(std::list<std::pair<std::string, int>>::iterator i = holdingD->begin(); i != holdingD->end(); i++) {
                (*advan)->addHand((*i));
            }
            break;
        case 4 :    //Four players: Millionaire, Noble, Poor, Destitute
            //Find Millionaire and Destitute
            for(advan = players->begin(); advan != players->end(); advan++) if((*advan)->getTitle() == 1) break;
            for(disadvan = players->begin(); disadvan != players->end(); disadvan++) if((*disadvan)->getTitle() == 5) break;
            
            //The Millionaire gets to trade their worst two cards with the Destitute 
            *holdingA = (*advan)->getWorst(2);
            //The Destitute has to trade their best two cards to the Millionaire
            *holdingD = (*disadvan)->getBest(2);
            
            //Swap cards
            for(std::list<std::pair<std::string, int>>::iterator i = holdingA->begin(); i != holdingA->end(); i++) {
                (*disadvan)->addHand((*i));
            }
            for(std::list<std::pair<std::string, int>>::iterator i = holdingD->begin(); i != holdingD->end(); i++) {
                (*advan)->addHand((*i));
            }
            
            //Find Noble and Poor
            for(advan = players->begin(); advan != players->end(); advan++) if((*advan)->getTitle() == 2) break;
            for(disadvan = players->begin(); disadvan != players->end(); disadvan++) if((*disadvan)->getTitle() == 4) break;
            
            //The Noble gets to trade their worst card with the Poor 
            *holdingA = (*advan)->getWorst(1);
            //The Poor has to trade their best card to the Noble
            *holdingD = (*disadvan)->getBest(1);
            
            //Swap cards
            for(std::list<std::pair<std::string, int>>::iterator i = holdingA->begin(); i != holdingA->end(); i++) {
                (*disadvan)->addHand((*i));
            }
            for(std::list<std::pair<std::string, int>>::iterator i = holdingD->begin(); i != holdingD->end(); i++) {
                (*advan)->addHand((*i));
            }
            break;
        case 5 :    //Five players: Millionaire, Noble, Commoner, Poor, Destitute
            //Find Millionaire and Destitute
            for(advan = players->begin(); advan != players->end(); advan++) if((*advan)->getTitle() == 1) break;
            for(disadvan = players->begin(); disadvan != players->end(); disadvan++) if((*disadvan)->getTitle() == 5) break;
            
            //The Millionaire gets to trade their worst two cards with the Destitute 
            *holdingA = (*advan)->getWorst(2);
            //The Destitute has to trade their best two cards to the Millionaire
            *holdingD = (*disadvan)->getBest(2);
            
            //Swap cards
            for(std::list<std::pair<std::string, int>>::iterator i = holdingA->begin(); i != holdingA->end(); i++) {
                (*disadvan)->addHand((*i));
            }
            for(std::list<std::pair<std::string, int>>::iterator i = holdingD->begin(); i != holdingD->end(); i++) {
                (*advan)->addHand((*i));
            }
            
            //Find Noble and Poor
            for(advan = players->begin(); advan != players->end(); advan++) if((*advan)->getTitle() == 2) break;
            for(disadvan = players->begin(); disadvan != players->end(); disadvan++) if((*disadvan)->getTitle() == 4) break;
            
            //The Noble gets to trade their worst card with the Poor 
            *holdingA = (*advan)->getWorst(1);
            //The Poor has to trade their best card to the Noble
            *holdingD = (*disadvan)->getBest(1);
            
            //Swap cards
            for(std::list<std::pair<std::string, int>>::iterator i = holdingA->begin(); i != holdingA->end(); i++) {
                (*disadvan)->addHand((*i));
            }
            for(std::list<std::pair<std::string, int>>::iterator i = holdingD->begin(); i != holdingD->end(); i++) {
                (*advan)->addHand((*i));
            }
            break;
        default :
            cout << "Something went wrong, you found the secret message!" << endl;
            break;
    }
    
    delete holdingA, holdingD;
}

void Game::resetTitles() {
    //Place titles in queue based on amount  of players
    if(!titles.empty()) {
        for(int i = 0; i < titles.size(); i++) {
            titles.pop();
        }
    }
    switch(pCount) {
        case 3:
            titles.push(1);
            titles.push(3);
            titles.push(5);
            break;
        case 4:
            titles.push(1);
            titles.push(2);
            titles.push(4);
            titles.push(5);
            break;
        case 5:
            for(int i = 1; i <= 5; i++) {
                titles.push(5);
            }
            break;
        default:
            break;
    }
}

bool Game::badRank(std::string s) {
    string ranks[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    for(int i = 0; i < 13; i++) if(s == ranks[i]) return false;
    return true;
}