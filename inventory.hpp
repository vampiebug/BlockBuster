#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

#define TEMPLATE true // choose whether you want to use templates or not

#if TEMPLATE // use this code if you want to use templates
template<typename T>
class Inventory
{
public:
	// typical constructor, just initializes an empty inventory
	Inventory()						= default;
	
	// copy constructor
	Inventory(const Inventory&)				= default;
	
	// destructor
	virtual ~Inventory()					= default;
	
	// insert an item into the list, duplication allowed, insertion order preserved
	virtual void	insert(const T&)			= 0;
	
	// check if an item with a given ID string exists,
	// returns const pointer to the item if it exists
	// returns null if the item is not in the inventory
	virtual const T* contains(const std::string&) const	= 0;
	
	// return the number of elements in the inventory
	virtual size_t	size() const				= 0;

	// public function to print the whole inventory to a stream
	virtual void print(std::ostream&) const			= 0;
	
	// function to make the printing more convenient
	friend std::ostream& operator<<( std::ostream& os, const Inventory<T>& inv )
	{
		inv.print(os);
		return os;
	}
};

#else // use this code if you do not want to use templates
class Inventory
{
public:
	// typical constructor, just initializes an empty inventory
	Inventory()						= default;
	// copy constructor
	Inventory(const Inventory&)				= default;
	// destructor
	virtual ~Inventory()					= default;
	// insert an item into the list, duplication allowed, insertion order preserved
	virtual void	insert(const Movie&)			= 0;
	// check if a Movie with a given title string exists,
	// returns const pointer to the movie if it exists
	// returns null if the movie is not in the inventory
	virtual const Movie*	contains(const std::string&)		= 0;
	// return the number of movies in the inventory
	virtual size_t	size() const				= 0;

	// public function to print the whole inventory to a stream
	virtual void print(std::ostream&) const		= 0;
	// function to make the printing more convenient
	friend std::ostream& operator<<( std::ostream& os, const Inventory& inventory )
	{
		inventory.print(os);
		return os;
	}
};
#endif // TEMPLATE

#endif // INVENTORY_H
