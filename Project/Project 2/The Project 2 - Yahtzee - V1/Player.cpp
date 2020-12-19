/* 
 * File:   Player.cpp
 * Author: Arthur Choy
 * Created on December 13, 2020, 2:32 AM
 */

#include "Player.h"

//Default Constructor
Player::Player() {
    name = " ";
    total = 0;
    uBonus = false;
    card = new Category[SCORES_SIZE];
    for(int i = 0; i < SCORES_SIZE; i++) card[i] = 0;
}

Player::Player(std::string n) {
    name = n;
    total = 0;
    uBonus = false;
    card = new Category[SCORES_SIZE];
    for(int i = 0; i < SCORES_SIZE; i++) card[i] = 0;
    
}

//Default Copy Constructor
Player::Player(const Player& orig) {
}

//Destructor
Player::~Player() {
    delete [] card;
}

//Set score player wants to set
void Player::stScore(int i) {
    card[i] = scores[i];
    total += scores[i];
    int upper = 0;
    for(int i = 0; i < 6; i++) upper += card[i];
    if(upper >= 63 && !uBonus) total += 35;
}

//**************************
//Overloaded Operators     *
//**************************
//+= Operator
Player Player::operator +=(const int &right) {
    total += right;
    return *this;
}

//-= Operator
Player Player::operator -=(const int &right) {
    total -= right;
    return *this;
}

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
    return card[sub];
}
    