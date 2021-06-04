/* 
 * File:   AVLTree.cpp
 * Modified:  from http://www.sanfoundry.com/cpp-program-implement-AVL-trees/
 * Created on May 23, 2021, 9:14 PM
 * Purpose:  An Binary Tree using an AVL balancing technique
 */

#include <iostream>
#include <c++/bits/stl_pair.h>
#include "AVLTree.h"
using namespace std;

AVLTree::AVLTree() {
    root = nullptr;
    std::string arr[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2" };
    
    for(int i = 0; i < 13; i++) {
        cKey.emplace(JSHash(arr[i]), i);
    }
}

//******************************************************************************
//                                 Hash Function
//******************************************************************************
unsigned int AVLTree::JSHash(string str) {
    unsigned int hash = 1315423911;

    for(std::size_t i = 0; i < str.length(); i++)
    {
       hash ^= ((hash << 5) + str[i] + (hash >> 2));
    }

    return hash;
}

//******************************************************************************
//                              Destructor function
//******************************************************************************
//Recursive tree destructor from:
//https://stackoverflow.com/questions/34170164/destructor-for-binary-search-tree
void AVLTree::destruct(BNTnode *node) {
    if(node != nullptr) {
        destruct(node->left);
        destruct(node->right);
        delete node;
    }
}

//******************************************************************************
//                            Height of AVL Sub Trees
//******************************************************************************
int AVLTree::height(BNTnode *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
//******************************************************************************
//                      Height Difference of AVL Sub Trees
//******************************************************************************
int AVLTree::diff(BNTnode *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
 
//******************************************************************************
//                      Right-Right Rotations of Sub Trees
//******************************************************************************
BNTnode *AVLTree::rr_rotation(BNTnode *parent){
    BNTnode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

//******************************************************************************
//                      Left-Left Rotations of Sub Trees
//******************************************************************************
BNTnode *AVLTree::ll_rotation(BNTnode *parent){
    BNTnode *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}
 
//******************************************************************************
//                      Left-Right Rotations of Sub Trees
//******************************************************************************
BNTnode *AVLTree::lr_rotation(BNTnode *parent){
    BNTnode *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
 
//******************************************************************************
//                      Right-Left Rotations of Sub Trees
//******************************************************************************
BNTnode *AVLTree::rl_rotation(BNTnode *parent){
    BNTnode *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
 
//******************************************************************************
//                         Balancing of Sub Trees
//******************************************************************************
BNTnode *AVLTree::balance(BNTnode *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }else if (bal_factor < -1){
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}
 
//******************************************************************************
//                    Insert the Data into the Sub Trees
//******************************************************************************
BNTnode *AVLTree::insert(BNTnode *&root, std::pair<std::string, int> c){
    if (root == NULL){
        root = new BNTnode;
        root->data = c;
        root->left = NULL;
        root->right = NULL;
        return root;
    }else if (c.second < root->data.second){
        root->left = insert(root->left, c);
        root = balance (root);
    }else if (c.second >= root->data.second){
        root->right = insert(root->right, c);
        root = balance (root);
    }
    return root;
}

void AVLTree::inCall(std::pair<std::string, int> c) {
    insert(root, c);
}
 
//******************************************************************************
//                         Display all Sub Trees
//******************************************************************************
void AVLTree::display(BNTnode *ptr, int level){
    int i;
    if (ptr!=NULL){
        display(ptr->right, level + 1);
        cout<<endl;
        if (ptr == root)
        cout<<"R -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"     ";
        cout<<ptr->data.first;
        display(ptr->left, level + 1);
    }
}
 
//******************************************************************************
//                      In-order Output of Tree
//******************************************************************************
void AVLTree::inorder(BNTnode *tree){
    if (tree == NULL)
        return;
    inorder (tree->left);
    cout<<tree->data.first<<"  ";
    inorder (tree->right);
}

//******************************************************************************
//                      Pre-order Output of Tree
//******************************************************************************
void AVLTree::preorder(BNTnode *tree){
    if (tree == NULL)
        return;
    cout<<tree->data.first<<"  ";
    preorder (tree->left);
    preorder (tree->right);
}
 
//******************************************************************************
//                      Post-order Output of Tree
//******************************************************************************
void AVLTree::postorder(BNTnode *tree){
    if (tree == nullptr)
        return;
    postorder ( tree ->left );
    postorder ( tree ->right );
    cout<<tree->data.first<<"  ";
}

//******************************************************************************
//                            Get max value
//******************************************************************************
std::pair<std::string, int> AVLTree::getMax() {
    return maxFind(root);
}

std::pair<std::string, int> AVLTree::maxFind(BNTnode *tree) {
    if(tree->right == nullptr) return tree->data;
    return maxFind(tree->right);
}

//******************************************************************************
//                            Get min value
//******************************************************************************
std::pair<std::string, int> AVLTree::getMin() {
    return minFind(root);
}

std::pair<std::string, int> AVLTree::minFind(BNTnode *tree) {
    if(tree->left == nullptr) return tree->data;
    return minFind(tree->left);
}

//******************************************************************************
//                   Delete an element from the tree
//******************************************************************************
//Referenced from:
//https://stackoverflow.com/questions/46385970/binary-search-tree-find-if-value-exists
bool AVLTree::confirmNode(BNTnode *tree, string n) {
    if(tree == nullptr) return false;
    if(tree->data.second == cKey.at(JSHash(n))) return true;
    if(tree->data.second > cKey.at(JSHash(n))) return confirmNode(tree->left, n);
    return confirmNode(tree->right, n);
}

//Referenced from:
//https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
BNTnode *AVLTree::treeDel(BNTnode *tree, std::string n) {
    // base case
    if (tree == nullptr)
        return tree;
 
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (cKey.at(JSHash(n)) < tree->data.second)
        tree->left = treeDel(tree->left, n);
 
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (cKey.at(JSHash(n)) > tree->data.second)
        tree->right = treeDel(tree->right, n);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (tree->left==nullptr && tree->right==nullptr) return nullptr;
       
        // node with only one child or no child
        else if (tree->left == nullptr) {
            BNTnode *temp = tree->right;
            free(tree);
            return temp;
        }
        else if (tree->right == nullptr) {
            BNTnode *temp = tree->left;
            free(tree);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        std::pair<std::string, int> temp = minFind(tree->right);
 
        // Copy the inorder successor's content to this node
        tree->data = temp;
 
        // Delete the inorder successor
        tree->right = treeDel(tree->right, temp.first);
    }
    return tree;
}

bool AVLTree::delCall(std::string n) {
    bool temp = confirmNode(root, n);
    root = treeDel(root, n);
    return temp;
}
