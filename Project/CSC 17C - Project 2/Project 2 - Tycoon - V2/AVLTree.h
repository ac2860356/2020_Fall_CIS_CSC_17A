/* 
 * File:   AVLTree.h
 * Modified:  from http://www.sanfoundry.com/cpp-program-implement-AVL-trees/
 * Created on May 23, 2021, 9:14 PM
 * Purpose:  An Binary Tree using an AVL balancing technique
 */

#ifndef AVLTREE_H
#define	AVLTREE_H

#include <map>
#include "BNTnode.h"

class AVLTree{
    public:
        BNTnode *root;                   //Root node
        std::map<int, int> cKey;         //Card rank key
        unsigned int JSHash(std::string);//Hash to get int value for associated card name
        int height(BNTnode *);           //Tree height
        int diff(BNTnode *);             //Difference of right/left subtrees
        BNTnode *rr_rotation(BNTnode *); //Right-Right rotation
        BNTnode *ll_rotation(BNTnode *); //Left-Left   rotation
        BNTnode *lr_rotation(BNTnode *); //Left-Right  rotation
        BNTnode *rl_rotation(BNTnode *); //Right-Left  rotation
        BNTnode* balance(BNTnode *);     //Balance subtrees with diff > 1
        BNTnode* insert(BNTnode *&, std::pair<std::string, int> );//Insert and balance the tree
        void display(BNTnode *, int);    //Funky display root left to right
        void inorder(BNTnode *);         //In order display
        void preorder(BNTnode *);        //Pre order display
        void postorder(BNTnode *);       //Post order display
        void dsp() {preorder(root);}     //Display hand
        void dspSort() {inorder(root);}  //Display sorted hand
        AVLTree();          //Constructor
        virtual ~AVLTree(){destruct(root);}//Destructor
        void clear() {destruct(root);root=nullptr;}//Call destruct function
        void destruct(BNTnode*);         //Recursive tree destruction
        BNTnode *treeDel(BNTnode*, std::string);//Delete node
        bool confirmNode(BNTnode *, std::string);//Confirm a node's existance in the tree
        bool delCall(std::string);       //Call delete function
        std::pair<std::string, int> getMax();//Get max value in tree
        std::pair<std::string, int> getMin();//Get min value in tree
        std::pair<std::string, int> maxFind(BNTnode *);//Find max value in tree
        std::pair<std::string, int> minFind(BNTnode *);//Find min value in tree
        void inCall(std::pair<std::string, int>);//Call insert function
};

#endif	/* AVLTREE_H */