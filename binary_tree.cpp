#include <iostream>
#include "binary_tree.hpp"

using namespace std;

class TreeNode{
    public:
        int value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(){
            value = 0;
            left = NULL;
            right = NULL;
        }
        TreeNode(int v){
            value = v;
            left = NULL;
            right = NULL;
        }
};

class BST{
    public:
        TreeNode* root;
        bool isEmpty(){
            if (root == NULL){
                return true;
            }
            else{
                return false;
            }
        }
        
        void insertNode(TreeNode *new_node){
            if(root == NULL){
                root = new_node;
            }
            else{
                TreeNode* temp = root;
                while(temp != NULL){
                    if(new_node->value == temp->value){
                        cout << "Value already exists." << endl;
                        return;
                    }
                    else if((new_node->value < temp->value) && (temp->left == NULL)){
                        temp->left = new_node;
                        cout << "Value inserted to the left." << endl;
                        break;
                    }
                    else if(new_node->value < temp->value){
                        temp = temp->left;
                    }
                    else if((new_node->value > temp->value) && (temp->right==NULL)){
                        temp->right = new_node;
                        cout << "Value inserted to the right." << endl;
                        break;
                    }
                    else{
                        temp = temp->right;
                    }
                }
            }
        }

        void print2D(TreeNode *r, int space){
            if (r == NULL){
                return;
            }
            space += SPACE;
            print2D(r->right, space);
            cout << endl;
            for( int i= SPACE; i<space; i++){
                cout << " ";
            }
            cout << r->value << "\n";
            print2D(r->left, space);
        }
};