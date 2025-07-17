#include <iostream>
#include "binary_tree.hpp"
#include "inventory.hpp"

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

        TreeNode* search( int v){
            if( root == NULL ){
                return root;
            }
            else{
                TreeNode *temp=root;
                while( temp != NULL){
                    if( v == temp->value){
                        return temp;
                    }
                    else if(v < temp->value){
                        temp = temp->left;
                    }
                    else{
                        temp = temp->right;
                    }
                }
            }
        }

        TreeNode* minValueNode(TreeNode* node){
            TreeNode* current = node;
            while( current->left != NULL ){
                current = current->left;
            }
            return current;
        }

        TreeNode* deleteNode(TreeNode* r, int v){
            if( r== NULL ){
                return NULL;
            }
            else if(v < r->value){
                r->left = deleteNode(r->left, v);
            }
            else if(v > r->value){
                r->right = deleteNode(r->right, v);
            }
            else{
                if(r->left == NULL){
                    TreeNode* temp = r->right;
                    delete r;
                    r = NULL;
                    return temp;
                }
                else if(r->right == NULL){
                    TreeNode* temp = r->left;
                    delete r;
                    r = NULL;
                    return temp;
                }
                else{
                    TreeNode* temp = minValueNode(r->right);
                    r->value = temp->value;
                    r->right = deleteNode(r->right, temp->value);
                }
            }
            return r;
        }
};