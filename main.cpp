#include "movie.hpp"
#include "inventory.hpp"
#include "finicky_database.hpp"
#include "singly_linked_list.hpp"
#include "binary_tree.hpp"
#include "doubly_linked_list.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
	// check if we are passed a movie data file
	if( argc < 2 )
	{
		cout << "Usage: ./movies <movie_input_file>" << endl;

		return -1; // this is ok in very obvious cases
	}

	// these are for timekeeping
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	auto diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

	start = std::chrono::high_resolution_clock::now();
	//this is an untrustworthy database
	FinickyDatabase<Movie> finicky_database;
	finicky_database.populate( argv[1] );
	end = std::chrono::high_resolution_clock::now();
	
	diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
	cerr
		<< "Populated the finicky database with "
		<< finicky_database.size()
		<< " items in "
		<< diff
		<< " seconds"
		<< endl
		;

	Movie movie; // this is a placeholder/iterator
// *****************************************************************************************************
	// step 1: get the following code to work to work.
	// this requires implementing a copy constructor and the operator= function for the Movie class.
	// while( finicky_database.readFirst(movie) )
	// {
	// 	cout << movie << endl;
	// }
	// cout << "Finicky database contained " << finicky_database.size() << " movies." << endl;

	// // try 10 times to output the data a second time
	// for(int i = 0; i < 10; i ++ )
	// {
	// 	cout << "Trying to output the movies again..." << endl;
	// 	while( finicky_database.readFirst(movie) )
	// 	{
	// 		cout << movie << endl;
	// 	}
	// 	cout << "Done trying to output the movies again." << endl;
	// }

	// you can comment the code for step 1 above once you're done.
	// you will use similar functionality below
	// (leave the copy constructor and operator= for the Movie class)
// *****************************************************************************************************
	// step 1.5: get a bunch of info from stdin, describing what to do next in the test case
	string operation;
	string name;
	std::vector<std::string> operations;
	start = std::chrono::high_resolution_clock::now();
	while( std::getline(cin, operation, '\t' ) && std::getline(cin, name, '\n' ) )
	{
		operations.push_back( operation );
		operations.push_back( name );
	}
	end = std::chrono::high_resolution_clock::now();
	diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
	cerr << "Received " << (operations.size()-2) / 2 << " operations in " << diff << " s" << endl;
	bool linked_list = false;
	
	// instantiate your inventory 
	//Inventory* inventory;		// if not using templates
	Inventory<Movie>* inventory = nullptr;	// if using templates

// *****************************************************************************************************
	// step 2: instantiate an inventory as a linked list
	start = std::chrono::high_resolution_clock::now();
	if( operations[0] == "type" && operations[1] == "linked_list" )
	{
		cerr << "Instantiating the inventory as a linked list!" << endl;

		linked_list = true;
		inventory = new SinglyLinkedList<Movie>();
		cout<<"list defined"<<endl;
		
	}
// *****************************************************************************************************
	// step 3: instantiate an inventory as a binary tree
	else if( operations[0] == "type" && operations[1] == "binary_tree" )
	{
		cerr << "Instantiating the inventory as a binary tree!" << endl;
		inventory = new Binary_Tree<Movie>();
	
	}
	
// *****************************************************************************************************
	// something is wrong here so we end
	else
	{
		cerr << "Malformed test file!" << endl;
		return -1;
	}
	end = std::chrono::high_resolution_clock::now();
	//Report time for inventory
	diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
	cerr
		<< "Instantiated the linked list/binary tree in "
		<< diff
		<< " seconds"
		<< endl
		;
// *****************************************************************************************************
	// step 3.5: populate your inventory from the finicky database

	// show the current state of the inventory
	while (finicky_database.readFirst(movie)){
		inventory->insert(movie);

	}
	cout<<"Populated inventory with "<<inventory->size()<<" items."<<endl;
// *****************************************************************************************************
	// step 4: implement a user list as a doubly linked list
	// process each command in the test case according to the inventory interface
	start = std::chrono::high_resolution_clock::now();
	DoubleList<Movie> user_list;

	//adding the loop for operations
	for (int i = 2; i < operations.size(); i+=2){

		if (operations[i] == "insert"){
			//needs to run contains for the insert term. 
			//must check if the value does not get a nullptr

			//if the pointer isn't null (movie found), add its value.
			if (nullptr != inventory->contains(operations[i+1])){
				Movie insert_movie = *inventory->contains(operations[i+1]);
				user_list.insert(insert_movie);

			}
			//otherwise, continue.
			
		}
		if (operations[i] == "remove"){
			//needs to run contains for the remove term on the user list.
			cout<<"removing "<<operations[i+1]<<endl;
			
			//if the pointer isn't null (movie found), add its value.
			if (user_list.contains(operations[i+1]) != nullptr){
				Movie remove_movie = *user_list.contains(operations[i+1]);
				user_list.remove(remove_movie);
			}
			//otherwise, continue.
		}
		if (operations[i] == "swap"){
			//break up operations[i+1] along the '|'
			cout<<"swapping "<<operations[i+1]<<endl;
			string movie_1_str = operations[i+1].substr(0, operations[i+1].find("|"));
			string movie_2_str = operations[i+1].substr(operations[i+1].find("|")+1, string::npos);
			//run contains for both.
			
			//if contains is valid for both and they are not the same movie, run swap.
			if (user_list.contains(movie_1_str) != nullptr && user_list.contains(movie_2_str) != nullptr){
				Movie movie_1 = *user_list.contains(movie_1_str);
				Movie movie_2 = *user_list.contains(movie_2_str);
				if (&movie_1 != &movie_2){
					user_list.swap(movie_1, movie_2);
				}
			}

		}
		
	}


	// step 4.5: output the user list to stdout
	cerr << "Outputting user list." << endl;
	cout << user_list << endl;
	end = std::chrono::high_resolution_clock::now();
	//report time for doubly linked list
	diff  = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
	cerr
		<< "Implemented the doubly linked list in "
		<< diff
		<< " seconds"
		<< endl
		;
	//put the output to a file
	std::fstream fout;

	//open the filestream--trunc erases all its current contents.
	fout.open("results.txt", std::ofstream::out | std::ofstream::trunc);
	fout<<user_list;
	fout.close();


	cerr << "At the end of main!" << endl;
	//need to delete because it's a pointer
	delete inventory;

	return 0;
}
