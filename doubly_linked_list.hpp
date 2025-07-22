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
	class DoubleNode { //initialize the head pointers and null
        friend class DoubleList;
		T data;	// holds a piece of data
		DoubleNode* next;	// holds a pointer to the next node
        DoubleNode* prev;

		DoubleNode(T Data) : data(Data), next(nullptr), prev(nullptr){}
        DoubleNode(T Data, DoubleNode* _next, DoubleNode* _prev) : data(Data), next(_next), prev(_prev){}


	};

	DoubleNode* head;		// first node of the list (set null)
    DoubleNode* tail;     // last node of list (set null)

public:
    DoubleList() { //Constructor
        head = nullptr;
        tail = nullptr;
    }
    ~DoubleList() { //Deconstructor
        this->pop_all();

    }
    bool empty() const {
        if (head == nullptr)
            return true;
        else{
            return false;
        }
    }
    void push_front(T data) {
        //std::cout<<"In push_front"<<endl;
        if (head != nullptr) { // push to the front of the list
            DoubleNode* new_node = new DoubleNode(data, head, nullptr); //prev pointer is null
            this->head->prev = new_node;
            //reassign head last
            this->head = new_node;
        }
        else { // else we need to create a new node that the head points to, and make the tail point to the head (since there is only one node)
            //std::cout<<"head is null"<<std::endl;
            this->head = new DoubleNode(data,nullptr,nullptr); //prev and head pointer is null
            //std::cout<<"created new node"<<std::endl;
            //cout<<head->data<<endl;
            this->tail = this->head; 
            //std::cout<<"head and tail assigned to same"<<std::endl;
        }       
    }
    void push_back(T data) {
        if (tail != nullptr) { // push to the back of the list
            //creates new node with tail as the previous
            DoubleNode* new_node = new DoubleNode(data, nullptr, tail); // next is null, prev is the current tail
            this->tail->next = new_node;
            this->tail = new_node;
        }
        else { // else we need to create a new node that the head points to, and make the tail point to the head (since there is only one node)
            this->head = new DoubleNode(data,nullptr,nullptr); //prev and head pointer is null
            //std::cout<<"created new node"<<std::endl;
            //cout<<head->data<<endl;
            this->tail = this->head; 
        }  
    }

    void pop_front() { // basically the same as single linked list
        if (head != nullptr) { //check if list is empty
            DoubleNode* temp = head; // create pointer to the front of list (head)
            head = head -> next; //move the head forward one
            
            delete temp; //delete pointer and null it
            //temp = NULL;
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
	void push_all(const DoubleList& list){
        Iterator it = Iterator(list.head);
        while(it != nullptr){
            this->push_front(*it);
            ++it;
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
		//create a new node and set its datum
        //std::cout<<"In insert"<<endl;
        
        T copy = data;
		this->push_back(copy);
        //std::cout<<"back in insert"<<std::endl;
        //std::cout<<head->data<<endl;
        

	}
    // check if the list contains a particular item
    virtual const T* contains(const std::string& search) const override{
        //need to completely redo this to rely on strings
        //if datum.print contains search, return true?
        //create tracker first
        DoubleNode* tracker = this->head;
        while (nullptr!=tracker){

            //if the tracker contains the search term (find returns a value other than string::npos)
            //std::cout<<line.str().substr(0, search.size())<<std::endl;
            if (tracker->data==search){
            //return the tracker--will be the first item to contain the term
                return &(tracker->data);
            }
            //move to next
            tracker = tracker->next;
        }

        //only will reach if none found
        return nullptr;

        
    }
    virtual size_t size() const override{
		DoubleNode* curr = this->head;
		size_t size = 0;
		while (nullptr != curr){
			size++;
			curr = curr->next;
		}
		return size;
	}
    // prints the list to a stream (basically the same as single)
    void print(std::ostream& output_stream) const override{
        for(DoubleNode* temp = head; temp != nullptr; temp=temp->next){
            output_stream << temp->data;
            output_stream<<std::endl;
        }
    }
    // prints the list to a stream in a convenient way (non-member)
    friend std::ostream& operator<< (std::ostream& output_stream, const DoubleList& list) {
        list.print(output_stream);
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
    
    //copy constructor
    DoubleList(const DoubleList& other){
		// will need two directions of push_all

		DoubleList temp_1 = DoubleList();
		temp_1.push_all(other);
		//temp 1 has all the values, but in reverse. Can now push_all from it to the SinglyLinkedList being created.
		this->push_all(temp_1);
			
		}

    // sets this list equal to another one (in a sane way)
	DoubleList& operator= (const DoubleList& other){
        if (*this != other){
            this->pop_all();
            this->push_all(other);
        }
        return *this;
    }

    //swap two movies contained in the double linked list
    void swap(const T& first_val, const T& second_val){
        //Caitlyn: I don't understand this version. I don't see how the int iteration worked. Can't we just do temp direclty assigning to node1 and node2?
        //also: easier to implement in main if we can pass in const refs to movie objects.
        // //create temp holders for the nodes to swap with
        DoubleNode* curr1 = head;
        DoubleNode* curr2 = head;
        
        // //find the correct node they should point to
        while(curr1!=nullptr) {
            if (curr1->data==first_val){
                break;
            }
            curr1 = curr1->next;
        }
        while(curr2!=nullptr) {
            if (curr2->data==second_val){
                break;
            }
            curr2 = curr2->next;
        }

        // //swap the values of two nodes--should invoke assignment operator override of movie.
        T value = curr1->data;
        curr1->data = curr2->data;
        curr2->data = value;

    }

    //remove a specific movie from the double linked list using pop function
    void remove(const T& data){
        DoubleNode* current = head; //tracker starting at the front of the list
        std::cout<<"Entered remove"<<std::endl;

        while( current != nullptr /*&& current->data != data*/){
            
            if (current->data == data){
                //std::cout<<"reached node for "<<current->data<<endl;
                //if current is the only element
                if (this->head == this->tail){
                    std::cout<<"only 1 element"<<endl;
                    this->head = nullptr;
                    this->tail = nullptr;
                }
                //if current is tail:
                else if (current->next == nullptr){
                    current->prev->next = nullptr;
                    this->tail = current->prev;
                }
                //if current is head:
                else if (current->prev == nullptr){
                    current->next->prev = nullptr;
                    this->head = current->next;
                }
                //otherwise (in list):
                else{
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                //make sure the current node is deleted
                delete current;
                //current = NULL;
                return;

            }
            current = current->next;

        }
        

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

            Iterator begin() {
                return Iterator(this->head);
            }

            // EFFECTS: Returns a past-the-end iterator.
            Iterator end() {
                return Iterator();
            }
        private:
            DoubleNode *node_ptr;
    };

};



#endif