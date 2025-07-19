#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>
using namespace std;

// https://stackoverflow.com/questions/67788059/c-doubly-linkedlist-in-template 
template <typename T>
class DoubleList : public Inventory<T>{
private:
	struct DoubleNode { //initialize the head pointers and null
		T data;	// holds a piece of data
		DoubleNode* next;	// holds a pointer to the next node
        DoubleNode* prev;

		DoubleNode(T Data){
            data = Data;
            next = nullptr;
            prev = nullptr;
        }


	};

	DoubleNode* head;		// first node of the list (set null)
    DoubleNode* tail;     // last node of list (set null)

public:
    DoubleList<T>() { //Constructor
        head = nullptr;
        tail = nullptr;
    }
    ~DoubleList<T>() { //Deconstructor
        this->pop_all();
        delete this->head;
        delete this->tail;
    }
    bool empty() const {
        if (head == nullptr)
            return true;
        else{
            return false;
        }
    }
    void push_front(T data) {
        if (head != nullptr) { // push to the front of the list
            head = new DoubleNode<T>(data, nullptr, head); //prev pointer is null
            head ->next->prev = head;
        }
        else { // else we need to create a new node that the head points to, and make the tail point to the head (since there is only one node)
            head = new DoubleNode<T>(data,nullptr,nullptr); //prev and head pointer is null
            tail = head; 
        }       
    }
    void push_back(T data) {
        if (tail != nullptr) { // push to the back of the list
            tail = new DoubleNode<T>(data, tail,nullptr); // head is null
            tail->prev->next = tail;
        }
        else { // else we need to create a new node that the head points to, and make the tail point to the head (since there is only one node)
            tail = new DoubleNode<T>(data,nullptr,nullptr); //prev and head pointer is null
            head = tail;
        }  
    }

    void pop_front() { // basically the same as single linked list
        if (head != nullptr) { //check if list is empty
            DoubleNode* temp = head; // create pointer to the front of list (head)
            head = head -> next; //move the head forward one
            
            delete temp; //delete pointer and null it
            temp = NULL;
        }
        
    }
    void pop_back() { //remove node at end of list
        if (tail != nullptr) { //check if list is empty
            DoubleNode* temp = tail; // create pointer to the back of list (tail)
            tail->prev->next = nullptr; //null the end
            tail = tail->prev; //move the tail backward one (new end of the list)

            delete temp; //delete pointer and null it
            temp = NULL;
        }
        
    }
    // pushes all elements from another list onto this one
	void push_all(const T DoubleList<T>& list){
        while(head != nullptr){
            push_front(list.data);
        }
    }

	// removes all of the data from the list
	void pop_all(){
        //while the list isnt empty
        //  popfront
        while (head != nullptr) {
            pop_front();
        }
    }
    // gets a reference to the *data* value of the front node
	T& front(){
        return this->head->data;

    }
    // gets a reference to the data value of the back node
    T& back(){
        return this->tail->data;
    }
    // Add new data to the front of the list
	virtual void insert(const T& data) override{
		//create a new node
		DoubleNode* new_node = new DoubleNode();
		//set its datum
		new_node->data = data;
		//set its next to the head
		new_node->next = this->head;
		//set the head to the new node.
		this->head = new_node;	
	}
    // check if the list contains a particular item
	bool contains(const T DoubleList<T>& list) const{
        // Initialize a pointer with the head of linked list
        DoubleNode* current = head;

        // Iterate over all the nodes in the list
        while (current != nullptr) {
            // If the current node's value is equal to the data in the list, will return true
            if (current->data == list.data){
                return true;
            }
            // Move to the next node
            current = current->next;
        }

        // If there is no node with the same value, will return false
        return false;
    }
    virtual size_t size() const override{
		DoubleNode* curr = this->head;
		size_t size = 0;
		while (nullptr!= curr){
			size++;
			curr = curr->next;
		}
		return size;
	}
    // prints the list to a stream (basically the same as single)
    void print(std::ostream& output_stream) const{
        output_stream << "[";
        for(DoubleNode* temp = head; head != nullptr; temp=temp->next){
            output_stream << temp->data;
            output_stream<<", ";
        }
        output_stream << "]";
    }
    // prints the list to a stream in a convenient way (non-member)
    friend std::ostream& operator<< (std::ostream& output_stream, const DoubleList<T>& list) {
        output_stream << "[";
        output_stream << list.head->data;
        DoubleNode* temp = list.head->next;
        while (temp != nullptr) {
            output_stream <<  ", " << temp->data;
            temp = temp->next;
        }
        output_stream << "]";
        return output_stream; 
    }
    // determines if the data contained by one list is the same as in the other
	bool operator== (const DoubleList& other) const{
        //loop through the list. both will need to increment, terminates when either is nullptr.
		DoubleNode* my_temp = this->head;
		DoubleNode* other_temp = other.head;
		while (my_temp!=nullptr && other_temp != nullptr){
			//if they are ever not equal, return false.
			if (my_temp->data != other_temp->data){
				return false;
			}
			my_temp = my_temp->next;
			other_temp = other_temp->next;
		}
		//at the end of the list, if both temps are nullptr, then the lists are the same length. We can return true if that is true, otherwise it is false.
		if (my_temp == nullptr && other_temp == nullptr){
			return true;
		}
		return false;
    }
	
	// calls operator== and negates it
	bool operator!= (const DoubleList& other) const{
        return !(*this==other);
    }
    
    DoubleList(const SinglyLinkedList& other){
		// will need two directions of push_all

		DoubleList<T> temp_1 = DoubleList<T>();
		temp_1.push_all(other);
		//temp 1 has all the values, but in reverse. Can now push_all from it to the SinglyLinkedList being created.
		this->push_all(temp_1);
			
		}

    // sets this list equal to another one (in a sane way)
	DoubleList& operator= (const DoubleList& other){
        this->pop_all();
        this->push_all(other);
    }

    Iterator begin() {
        return Iterator(this->head);
    }

  // EFFECTS: Returns a past-the-end iterator.
    Iterator end() {
        return Iterator();
    }

    class Iterator {
        friend class DoubleList;
        public:
            T& operator*() const{
                assert(node_ptr);  // check whether this is a past-the-end iterator
                return node_ptr->data;
            }

            Iterator &operator++(){
                assert(node_ptr);  // check whether this is a past-the-end iterator
                Iterator tmp = *this;               // make a copy of this iterator
                node_ptr = node_ptr->next;
                return tmp;
            }

            bool operator==(Iterator rhs) const{
                return node_ptr == rhs.node_ptr;
            }

            bool operator!=(Iterator rhs) const{
                return node_ptr != rhs.node_ptr;
            }
        private:
            DoubleNode *node_ptr;
    };

};



#endif