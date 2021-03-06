/* 
 * File:   Category.h
 * Author: Arthur Choy
 * Created on December 13, 2020, 3:20 AM
 */

#ifndef CATEGORY_H
#define CATEGORY_H

class Category {
private:
    int score;   //Category score
    bool filled; //Whether or not the category was filled
    
public:
    //Default Constructor
    Category();
    
    //Default Copy Constructor
    Category(const Category& orig);
    
    //Destructor
    virtual ~Category();
    
    //Mutator functions
    void stScore(int);
    void fill();
    void unfill();
    
    //Accessor functions
    int gtScore() const
        { return score; }
    bool gtFill() const
        { return filled; }
};

#endif /* CATEGORY_H */

