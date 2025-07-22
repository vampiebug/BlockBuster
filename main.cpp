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

	// //Caitlyn testing--able to build a singly list inverntory and find individual items.
	// Inventory<Movie>* test;
	// test = new SinglyLinkedList<Movie>;
	// //Movie movie;
	// while (finicky_database.readFirst(movie)){
	// 	test->insert(movie);
	// 	cout<<movie<<endl;
	// }
	// cout<<"read from finicky\n";
	// cout<<test->size()<<endl;
	// cout<<*(test->contains("Madame DuBarry"))<<endl;
	//finds the movie and prints its line
	//Binary_Tree<Movie>* test = new Binary_Tree<Movie>();
	
	//cout<<*(test->contains("Madame DuBarry"))<<endl;

	// finicky_database.readFirst(movie);
	// test->insert(movie);
	// int tracker = 0;
	// cout<<finicky_database.size()<<endl;
	// while (finicky_database.readFirst(movie)){
	// 	test->insert(movie);
	// 	//cout<<movie<<endl;
	// 	tracker++;
	// }

	// // //cout<<test->getRoot()<<endl;
	// // cout<<"read from finicky\n";
	// test->print(cout);
	// cout<<test->size()<<" "<<tracker<<endl;
	// cout<<(test->contains("Cleopatra"))<<endl;
	// //finds the movie and prints its line




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
	//inventory = new SinglyLinkedList<Movie>();

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
		//here's what's weird: when I run with the smaller count_test tsv, it finds the correct number of lines. When I run it with the full database, it finds one fewer. I want to assume this is not my error, based on the fact that starting from the beginning is fine but something towards the end seems not to be duplicating.
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
	//tested this above--works
	while (finicky_database.readFirst(movie)){
		inventory->insert(movie);
		//cout<<movie<<endl;
	}
	cout<<"Populated inventory with "<<inventory->size()<<" items."<<endl;
	//cerr << *inventory << endl;
// *****************************************************************************************************
	// step 4: implement a user list as a doubly linked list
	// process each command in the test case according to the inventory interface
	start = std::chrono::high_resolution_clock::now();
	DoubleList<Movie> user_list;
	// cout<<"defined user_list, size "<<user_list.size()<<endl;

	//adding the loop for operations
	for (int i = 2; i < operations.size(); i+=2){
		//cout<<"entered loop"<<endl;
		//cout<<operations[i+1]<<endl;
		if (operations[i] == "insert"){
			//cout<<"inserting "<<operations[i+1]<<endl;
			//needs to run contains for the insert term. 
			//contains returns a const. This can't be const, because it has to be resued loop to loop. instead, must check if the value does not get a nullptr

			//if the pointer isn't null (movie found), add its value.
			if (nullptr != inventory->contains(operations[i+1])){
				//cout<<"trying to insert"<<endl;
				Movie insert_movie = *inventory->contains(operations[i+1]);
				//cout<<insert_movie<<endl;
				user_list.insert(insert_movie);
				//cout<<"ran insert"<<endl;

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
		//cout<<user_list<<endl;
		// int a = user_list.size();
		// cout<<"ran user_list.size: "<<a<<endl;
		
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
	//getting occassional double free errors--ont sure why. task for Tues.

	//on test 3: getting an error in the binary tree. It's finding different movies of the same name. May need to change contains checks to make sure they match entirely up until the first tab in the full string. 
	//That will only fix the Hua pi case though--Girls Town is the same name exactly. Given just the name string, comes down to the one encountered first in the inventory.
}
