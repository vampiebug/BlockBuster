#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include "inventory.hpp"
#include <iostream>
#include <sstream>

//had to include T
template <typename T>
class SinglyLinkedList : public Inventory<T> {
	private:
		// recursive data structure to hold each chunk of the list
		struct Node {
			T datum;	// holds a piece of data
			Node* next;	// holds a pointer to the next chunk
		};

		Node* head;		// first node of the list

	public:
		// constructor

		SinglyLinkedList(): head(nullptr){
			//default constructor
			//I think datum needs to be assigned to a new T
			//head->datum = new T;
		}


		// tells whether the list is empty or not
		bool empty() const{
			//checks if head is null
			return head == nullptr;
		}

		// adds new data to the front of the list
		virtual void insert(const T& datum) override{
		//create a new node
			Node* new_node = new Node();
		//set its datum
			new_node->datum = datum;
		//set its next to the head
			new_node->next = this->head;
		//set the head to the new node.
			this->head = new_node;
			
		}

		// gets a reference to the *data* value of the front node
		T& front(){
			//it's just head's datum. Should only return this if list is not empty.
			if (!this->empty()){
				return head->datum;
			}
			//um help what do we return otherwise
		}

		virtual size_t size() const override{
			Node* curr = this->head;
			size_t size = 0;
			while (nullptr!= curr){
				size++;
				curr = curr->next;
			}
			return size;
		}
		
		// removes and deallocates the front node of the list
		void pop_front(){
			//make sure list is not empty first
			if (!this->empty()){
				//make a shallow copy of the head.
				Node* temp_ptr = head;
				//assign the head to the next object
				this->head = head->next;
				//delete the head through the copy
				delete temp_ptr;
				//good to set temp_ptr to null so it doesn't get hit with a double delete
				//temp_ptr = nullptr;
			}

		}
		
		// check if the list contains a particular item. Returns a pointer to it, or nullptr otherwise.
		//checks based on a string of that item's data. Use this->print to compare?
		//ask what exactly it wants us to compare. just the title?
		virtual const T* contains(const std::string& search) const override{
			//need to completely redo this to rely on strings
			//if datum.print contains search, return true?
			//create tracker first
			Node* tracker = this->head;
			while (nullptr!=tracker){
				//pipe the tracker's datum to a string.
				std::stringstream line;
				line<<tracker->datum;
				//if the tracker contains the search term (find returns a value other than string::npos)
				if (line.str().find(search) != std::string::npos){
				//return the tracker--will be the first item to contain the term
					return &(tracker->datum);
				}
				//move to next
				tracker = tracker->next;
			}

			//only will reach if none found
			return nullptr;

			
		}

		// pushes all elements from another list onto this one
		void push_all(const SinglyLinkedList& other){
			//womp womp don't need to make a copy and delete, just need to iterate down like contains.
			//instead of checking for same, do a push_front() with the current data
				//can't use .begin() or .end() because this is const, must define custom. Iterators are generally for use outside of the class.
			//loop through the list until you reach the nullptr at the end
			Iterator it = Iterator(other.head);
			while (it != nullptr){
				//add the data
				this->push_front(*it);
				++it;
			}
		}

		// removes all of the data from the list
		void pop_all(){
			//just delete the front until the list is empty.
			while (!this->empty()){
				this->pop_front();
			}
		}

		// prints the list to a stream
		void print(std::ostream& output_stream) const{
			output_stream<<"[";//this is just format stuff
			//for each node, print its datum and some formatting.
			Node* temp = this->head;
			while (nullptr != temp->next){
				output_stream<<temp->datum;
				output_stream<<", ";
				temp = temp->next;
			}
			output_stream<<temp->datum<<"]";
		}

		// prints the list to a stream in a convenient way
		// NOTE: non-member function, but doing this in the .hpp because it was causing linker errors in the cpp
		friend std::ostream& operator<< (std::ostream& output_stream, const SinglyLinkedList& list){
			list.print(output_stream);
			return output_stream;
		}

		// determines if the data contained by one list is the same as in the other
		bool operator== (const SinglyLinkedList& other) const{
			//loop through the list. both will need to increment, terminates when either is nullptr.
			Node* my_temp = this->head;
			Node* other_temp = other.head;
			while (my_temp!=nullptr && other_temp != nullptr){
				//if they are ever not equal, return false.
				if (my_temp->datum != other_temp->datum){
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
		bool operator!= (const SinglyLinkedList& other) const{
			return !(*this==other);
		}

		// ***************************************************************************
		// These are "the big three" that make it easier to work with complex data types
		// copy constructor
		SinglyLinkedList(const SinglyLinkedList& other){
			//make new copies for everything--use push_all to do this?
			//will need two directions of push_all.
			//LOOK INTO THIS: if, in this context, temp_1 is intialized without the <T>, what happens?

			SinglyLinkedList<T> temp_1 = SinglyLinkedList<T>();
			temp_1.push_all(other);
			//temp 1 has all the values, but in reverse. Can now push_all from it to the SinglyLinkedList being created.
			this->push_all(temp_1);
			
		}

		// sets this list equal to another one (in a sane way)
		SinglyLinkedList& operator= (const SinglyLinkedList& other){
			//pop everything in the current list
			delete this;
			//do the same double push all thing
			SinglyLinkedList<T> temp_1 = SinglyLinkedList<T>();
			temp_1.push_all(other);
			this->push_all(temp_1);
			return *this;
		}
		
		// destructor
		~SinglyLinkedList(){
			//pop all
			//try deleting head again and see if I get double free. actually, can safely delete it because head is redefined to nullptr at the end of pop_front()).
			this->pop_all();
			delete this->head;
		}
		// ***************************************************************************

		// iterator class is an attribute of the SinglyLinkedList class.
		//Implementing this here bc templates are evil >:(
		class Iterator
		{
			// allow SinglyLinkedList to access private variables 
			friend class SinglyLinkedList;
		private:
			Node* node;

		public:
			// constructor
			Iterator() : node(nullptr){}

			// constructor starting from a particular node
			Iterator(Node* _node) : node(_node){}

			// adapation of dereference operator
			T& operator* () const{
				return this->node->datum;
			}

			// prefix iterator increment operator
			Iterator& operator++ (){
				//reassign this iterator to its node's next node and return the dereferenced this--the iter itself.
				this->node = this->node->next;
				return *this;
			}

			// postfix iterator increment operator
			//&T may need to be const
			// Iterator& operator++ (T&);

			// equality check between two iterators
			bool operator== (Iterator other) const{
				//compare by address;
				return (this->node == other.node);
			}

			// inequality check between two iterators
			bool operator!= (Iterator other) const{
				//compare by address;
				return !(this->node == other.node);
			}
		}; // this is an important semicolon

		// get an iterator starting at the beginning of the list
		Iterator begin(){
			//head as an iterator
			return Iterator(this->head);
		}

		// get an iterator corresponding to the end of the list (nullptr)
		Iterator end(){
			//returns default null iter
			return Iterator();
		}
};


#endif // SINGLLY_LINKED_LIST_HPP
