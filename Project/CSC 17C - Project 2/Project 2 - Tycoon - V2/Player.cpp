/* 
 * File:   Player.cpp
 * Author: Arthur Choy
 * Created on April 30, 2021, 2:58 PM
 */

#include <list>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <set>
#include <algorithm>
#include "Player.h"
using namespace std;

Player::Player() {
    hand = new AVLTree;
    title = 3;
    emptyHand = true;
}

Player::Player(std::string n) {
    hand = new AVLTree;
    title = 3;
    emptyHand = true;
    name = n;
}

Player::Player(const Player& orig) {
    hand = new AVLTree;
    title = orig.getTitle();
    name = orig.getName();
    emptyHand = orig.empt();
}

Player::~Player() {
    delete hand;
}

void Player::dspHand() {
    hand->dsp();
    cout << endl;
}

void Player::dspSHand() {
    hand->dspSort();
    cout << endl;
}

void Player::addHand(std::pair<std::string, int> c) {
    emptyHand = false;
    hand->inCall(c);
}

std::list<std::pair<std::string, int>> Player::playCards(string r, int a) {
    played.clear();

    for(int i = 0; i < a; i++) {
        if(hand->delCall(r)) played.emplace_front(r, hand->cKey.at(hand->JSHash(r)));
    }
    
    cout << endl;
    if(played.empty()) throw BadPlay();
    if(hand->root == nullptr) emptyHand = true;
    return played;
}

std::list<std::pair<std::string, int>> Player::getBest(int a) {
    played.clear(); //Clear card playing proxy
    
    //Get the specified amount of the best ranking cards in a player's deck
    for(int x = 0; x < a; x++) {
        if(hand->root == nullptr) break;
        std::pair<std::string, int> temp = hand->getMax();
        played.push_front(temp);
        hand->delCall(temp.first);
    }
    
    return played;
}

std::list<std::pair<std::string, int>> Player::getWorst(int a) {
    played.clear(); //Clear card playing proxy
    
    //Get the specified amount of the worst ranking cards in a player's deck
    for(int x = 0; x < a; x++) {
        if(hand->root == nullptr) break;
        std::pair<std::string, int> temp = hand->getMin();
        played.push_front(temp);
        hand->delCall(temp.first);        
    }
    
    return played;
}

void Player::reject() {
    for(std::list<std::pair<std::string, int>>::iterator i = played.begin(); i != played.end(); i++) {
        hand->inCall((*i));
    }
    if(hand->root != nullptr) emptyHand = false;
    played.clear();
}