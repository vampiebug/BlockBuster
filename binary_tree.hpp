#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#define SPACE 10

#include <iostream>
using namespace std;

template<typename T>
class Binary_Tree : public Inventory<T>{
    private:
        class TreeNode{
            //needs to be friend or else funcs become a nightmare
            friend class Binary_Tree;
            T value;
            TreeNode* left;
            TreeNode* right;
            TreeNode(T v) : value(v), left(nullptr), right(nullptr){}
            //unfortunately I think big 3 may be needed for this.
        };
        TreeNode* root;

        //sizeInternal--the recursive function for size(). Needs the node it is counting from. Will start with the node, then recurses down.
        //REQUIRES: the node to start with. Needs node so it can recurse, need this to run the interface-valid size() func.
        //EFFECTS: return the size of the list as a size_t.
        size_t sizeInternal(TreeNode* node) const{
            if (nullptr==node){
                return 0;
                
            }
            else{
                return 1 + sizeInternal(node->left) + sizeInternal(node->right);
            }

        }
        //sizeInternal--the recursive function for size(). Needs the node it is counting from. Will start with the node, then recurses down.
        //REQUIRES: the node to start with. Needs node so it can recurse, need this to run the interface-valid size() func.
        //EFFECTS: return the size of the list as a size_t.
        T* const containsInternal(TreeNode* node, const std::string& search) const{

            //start--check the start is not nullptr. Because the tree is sorted, if it ever reaches a leaf, then it doesn't contain the value.
            if (nullptr == node){
                return nullptr;
            }

            //if the title equals the search, return pointer to the current node
            
			if (node->value==search){
                return &(node->value);
            }
            //if the node is less than the search, go right
            else if (node->value.get_title() < search){
                return containsInternal(node->right, search);
            }
            //if the node is less than the search, go right
            else if (node->value.get_title() > search){
                return containsInternal(node->left, search);
            }
			//only will reach if none found--actually should never reach, but leaving it to be safe.
            std::cout<<search<<"not found"<<std::endl;
			return nullptr;
        }
        TreeNode* insertInternal(TreeNode* node_ptr, const T& toAdd){
            //if reach a null node, add it and return out.
            
            if (nullptr == node_ptr){
                //this was causing issues because node is a copy of the node pointer. By reassigning it to a new, this change was not passed on to the tree itself. 
                //Thus, by turning node into a pointer pointer, the function makes a copy of the outer pointer, which is unchanged, while the inner pointer can be changed for both.
                //nwm it works now
                node_ptr = new TreeNode(toAdd);
                return node_ptr;
            }
            //otherwise, if toAdd is greater than the current node, add it to the right. 
            if (node_ptr->value < toAdd){
                //reassigns the right node to be the new value--starts new loop on new, smaller tree
                node_ptr->right = insertInternal(node_ptr->right, toAdd);
            }
            else{
                node_ptr->left = insertInternal(node_ptr->left, toAdd);
            }
            return node_ptr;
            

        }
        void printInternal(std::ostream& output_stream,  TreeNode* node) const{
            if (node != nullptr){
                printInternal(output_stream, node->left);
                output_stream<<node->value<<", ";
                printInternal(output_stream, node->right);
            }

        }

        //helper for operator= using pre-orer traversal
        void copy_tree(Binary_Tree<T> *&dest, const Binary_Tree<T> *src){
            if (src == nullptr){
                dest = NULL;
            }
            
            if (src!= nullptr){
                dest = new Binary_Tree<T>;
                dest->value = src->value;
                copy_tree(dest->left, src->left);
                copy_tree(dest->right, src->right);
            }
        }

    public:
        //need constructor
        Binary_Tree() : root(nullptr){}

        Binary_Tree(const Binary_Tree<T>& src){
            root = nullptr;
            operator=(root, src.root);
        }

        //INVENTORY STUFF:
        virtual void insert(const T& toAdd) override{
            //relies on iterating down and through.
            //when reach empty node, should assign. Look into sorting.
            //must not contain toAdd--need string of toAdd
            T newObject = toAdd;
            std::stringstream newLine;
            newLine<<newObject;
            if (!contains(newLine.str())){
                //now do the internal
                root = insertInternal(this->root, newObject);
            }
            else {
                //should never run
                std::cout<<newLine.str()<<"not found"<<std::endl;
            }

        }

        virtual const T* contains(const std::string& search) const override{
            //also relies on iterating down and doing some behavior at some level
            return containsInternal(this->root, search);
        }
        virtual size_t	size() const override{
            return sizeInternal(this->root);
        }
        virtual void print(std::ostream& output_stream) const override{
            //yeah need to format again
            printInternal(output_stream, this->root);
            output_stream<<std::endl;
        }


        bool isEmpty(){
            return 
            (this->root == nullptr);
        }

        //used for dtor
        //REQUIRES: a tree
        //EFFECTS: cycles down the tree until it reaches a place where both left and right are nullptrs, then deletes that node
        //MODIFIES: deletes the entire tree
        void clearTree(TreeNode* node){
            //need these not to be elses--needs to clear all
            if (nullptr != node->left){
                clearTree(node->left);
            }
            if (nullptr != node->right){
                clearTree(node->right);
            }
            //reaches this only on leaves--otherwise keeps iterating down
            delete node;
        } 
        //REQUIRES: a tree
        //EFFECTS: returns the root node of the tree (null if the tree is empty)
        TreeNode* getRoot(){
            return this->root;
        }



        //big 3:
        //copy constructor
        Binary_Tree(const TreeNode& copy){
            //need to work out the algorithm for this--relies on knowing how to construct tree.
            //root to root.
            //iterate down--make special funcs for this, or look into functors. either way, the func iterates down one level and assigns the new tree.
            root = NULL;
            operator=(copy);


        }

        // Assignment operator
        Binary_Tree& operator=(T& other){

            if (root != nullptr){
                clearTree(other.root);
            }
            copy_tree(root, other.root); //pre-order traversal

        }

        //Deconstructor (delete stuff)
        ~Binary_Tree(){
            //this is going to be complicated
            //iterate down to and delete leaves, reassign to nulltr
            //do this until everything is deleted (isEmpty)
            //check the size to make sure they're all deleted
            std::cout << "destructor for the binary tree" << std::endl;
            clearTree(getRoot());
            std::cout << "destructor for the binary tree" << std::endl;

        }
};


#endif