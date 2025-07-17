#include "movie.hpp"
#include "inventory.hpp"
#include "finicky_database.hpp"

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
	// this is an untrustworthy database
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
//	while( finicky_database.readFirst(movie) )
//	{
//		cout << movie << endl;
//	}
//	cout << "Finicky database contained " << finicky_database.size() << " movies." << endl;
//
//	// try 10 times to output the data a second time
//	for(int i = 0; i < 10; i ++ )
//	{
//		cout << "Trying to output the movies again..." << endl;
//		while( finicky_database.readFirst(movie) )
//		{
//			cout << movie << endl;
//		}
//		cout << "Done trying to output the movies again." << endl;
//	}
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
	//Inventory<Movie>* inventory;	// if using templates

// *****************************************************************************************************
	// step 2: instantiate an inventory as a linked list
	if( operations[0] == "type" && operations[1] == "linked_list" )
	{
		cerr << "Instantiating the inventory as a linked list!" << endl;

		linked_list = true;
	}
// *****************************************************************************************************
	// step 3: instantiate an inventory as a binary tree
	else if( operations[0] == "type" && operations[1] == "binary_tree" )
	{
		cerr << "Instantiating the inventory as a binary tree!" << endl;
	}
// *****************************************************************************************************
	// something is wrong here so we end
	else
	{
		cerr << "Malformed test file!" << endl;
		return -1;
	}

// *****************************************************************************************************
	// step 3.5: populate your inventory from the finicky database

	// show the current state of the inventory
	//cerr << *inventory << endl;
// *****************************************************************************************************
	// step 4: implement a user list as a doubly linked list
	// process each command in the test case according to the inventory interface

	// step 4.5: output the user list to stdout
	//cerr << "Outputting user list." << endl;
	//cout << user_list << endl;

	cerr << "At the end of main!" << endl;

	return 0;
}
