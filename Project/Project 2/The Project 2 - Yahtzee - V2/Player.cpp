/* 
 * File:   Player.cpp
 * Author: Arthur Choy
 * Created on December 13, 2020, 2:32 AM
 */

#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//Default Constructor
Player::Player() {
    name = " ";
    total = 0;
    uBonus = false;
    for(int i = 0; i < SCORES_SIZE; i++) card[i].stScore(0);
}

Player::Player(std::string n) {
    name = n;
    total = 0;
    uBonus = false;
    for(int i = 0; i < SCORES_SIZE; i++) card[i].stScore(0);
    
}

//Destructor
Player::~Player() {
}

//Set score player wants to set
void Player::stCat(int i) {
    card[i].stScore(scores[i]);
    card[i].fill();
    total += scores[i];
    int upper = 0;
    for(int i = 0; i < 6; i++) upper += card[i].gtScore();
    if(upper >= 63 && !uBonus) {
        uBonus = true;
        total += 35;
    }
}

//**************************
//Overloaded Operators     *
//**************************
//< Operator
bool Player::operator <(const Player &right) {
    bool status = false;
    
    if(total < right.total)
        status = true;
    
    return status;
}

//> Operator
bool Player::operator >(const Player &right) {
    bool status = false;
    
    if(total > right.total)
        status = true;
    
    return status;
}

//[] Operator
int Player::operator [](const int &sub) {
    return card[sub].gtScore();
}
    