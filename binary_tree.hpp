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
    bool isTreeEmpty();
    void insertNode(TreeNode *new_node);
    void printPreorder(TreeNode* r);
    void printInorder(TreeNode* r);
    void printPostorder(TreeNode* r);
    void print2D(TreeNode *r, int space);
    void printLevelOrder(TreeNode *r);

    TreeNode* search(TreeNode*r, int v);
    TreeNode* minValueNode(TreeNode* node);
    TreeNode* deleteNode(TreeNode* r, int v);

};

#endif