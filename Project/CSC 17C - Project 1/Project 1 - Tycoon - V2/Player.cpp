/* 
 * File:   Player.cpp
 * Author: Arthur Choy
 * Created on April 16, 2021, 2:13 PM
 */

#include <list>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "Player.h"
using namespace std;

Player::Player() {
    hand = new std::list<std::pair<std::string, int>>;
    title = 3;
    emptyHand = false;
}

Player::Player(std::string n) {
    hand = new std::list<std::pair<std::string, int>>;
    title = 3;
    emptyHand = false;
    name = n;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
    delete hand;
}

void Player::dspHand() {
    for(std::list<std::pair<std::string, int>>::iterator i = hand->begin(); i != hand->end(); i++) {
        cout << setw(2) << right << (*i).first << " ";
    }
    cout << endl;
}

void Player::addHand(std::pair<std::string, int> c) {
    hand->push_front(c);
}

std::list<std::pair<std::string, int>> Player::playCards(string r, int a) {
    played.clear();
    int t = 0;
    for(std::list<std::pair<std::string, int>>::iterator i = hand->begin(); i != hand->end(); i++) {
        if((*i).first == r && t != a) {
            t++;
            played.push_front((*i));
            i = hand->erase(i);
        }
    }
    if(played.empty()) throw BadPlay();
    if(hand->empty()) emptyHand = true;
    return played;
}

void Player::reject() {
    for(std::list<std::pair<std::string, int>>::iterator i = played.begin(); i != played.end(); i++) {
        hand->push_front((*i));
    }
    if(!hand->empty()) emptyHand = false;
    played.clear();
}