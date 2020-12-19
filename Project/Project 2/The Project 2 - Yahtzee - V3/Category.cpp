/* 
 * File:   Category.cpp
 * Author: Arthur Choy
 * Created on December 13, 2020, 3:20 AM
 */

#include "Category.h"

//***************
// Constructors *
//***************
//Default Constructor
Category::Category() {
    score = 0;
    filled = false;
}

//Copy Constructor
Category::Category(const Category& obj) {
    score = obj.score;
    filled = obj.filled;
}

//Destructor
Category::~Category() {
}

//*********************
// Accessor Functions *
//*********************
void Category::stScore(int s) {
    score = s;
}

void Category::fill() {
    filled = true;
}

void Category::unfill() {
    filled = false;
}