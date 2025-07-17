#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#define SPACE 10

#include <iostream>
using namespace std;

class BST{
private:
    class TreeNode{
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode();
        TreeNode(int v);
    };

    TreeNode* root;
public:
    bool isEmpty();
    void insertNode(TreeNode *new_node); 
    void print2D(TreeNode *r, int space); 
    //void swap(TreeNode *node1, TreeNode *node2); // swap (do this with the list hpps???)
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* search( int v); //check if a query is in the inventory
    TreeNode* deleteNode(TreeNode* r, int v); // remove a movie from inventory

};

#endif