/* 
 * File:   Player.cpp
 * Author: Arthur Choy
 * Created on December 13, 2020, 2:32 AM
 */

#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//***************************
// Constructors/Destructors *
//***************************
//Default Constructor
Player::Player() {
    name = " ";
    total = 0;
    uBonus = false;
    for(int i = 0; i < SCORES_SIZE; i++) card[i].stScore(0);
}

//Constructor
Player::Player(std::string n) {
    name = n;
    total = 0;
    uBonus = false;
    for(int i = 0; i < SCORES_SIZE; i++) card[i].stScore(0);
    
}

//Copy Constructor
Player::Player(const Player& obj) {
    name = obj.name;
    uBonus = obj.uBonus;
    for(int i = 0; i < SCORES_SIZE; i++) card[i] = obj.card[i]; 
}

//Destructor
Player::~Player() {
}

//********************************************************
// Set score player wants to set, see if they earn upper *
// category bonus                                        *
//********************************************************
void Player::stCat(int i) {
    //Set score of wanted category, set category as filled
    card[i].stScore(scores[i]);
    card[i].fill();
    total += scores[i]; //Add score to total
    
    //Determine whether or not player earns upper category bonus
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
//*************************************************************
// < Operator; sees if right element is greater than the left *
//*************************************************************
bool Player::operator <(const Player &right) {
    bool status = false;
    
    if(total < right.total)
        status = true;
    
    return status;
}

//*************************************************************
// > Operator; sees if left element is greater than the right *
//*************************************************************
bool Player::operator >(const Player &right) {
    bool status = false;
    
    if(total > right.total)
        status = true;
    
    return status;
}

//********************************************************
// [] Operator; access player scorecard as if player was *
// score array                                           *
//********************************************************
int Player::operator [](const int &sub) {
    return card[sub].gtScore();
}
    