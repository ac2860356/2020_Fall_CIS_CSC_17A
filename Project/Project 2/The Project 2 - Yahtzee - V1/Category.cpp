/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Category.cpp
 * Author: gameb
 * 
 * Created on December 13, 2020, 3:20 AM
 */

#include "Category.h"

//Default Constructor
Category::Category() {
    score = 0;
    filled = false;
}

//Default Copy Constructor
Category::Category(const Category& orig) {
}

//Destructor
Category::~Category() {
}

void Category::stScore(int s) {
    score = s;
}

void Category::fill() {
    filled = true;
}

void Category::unfill() {
    filled = false;
}