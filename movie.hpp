#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <cstddef>
#include <istream>
#include <vector>
#include <ctime>

class Movie
{
public:
	// ctor / dtor
	Movie();

	// the big 3: copy constructor, operator= and destructor
	Movie(const Movie&);			// for step 1
	Movie& operator=(const Movie& other);		// for step 1
	~Movie();				// for step 1

	// for easy .csv input
	friend std::istream& operator>>(std::istream&, Movie&);

	const std::string get_title() const;
	const std::string id() const { return this->get_title(); }
	const std::string get_year() const;

	// human-readable easy output
	std::string to_string() const;
	std::string one_liner() const;
	friend std::ostream& operator<<(std::ostream&, const Movie&);

	friend bool operator<(const Movie&, const Movie&);
	friend bool operator==(const Movie&, const std::string&);
	friend bool operator!=(const Movie&, const std::string&);
	friend bool operator==(const Movie&, const Movie&);
	// operator!= also exists
	friend bool operator>(const Movie&, const Movie&);

private:
	std::string title;
	static bool sanitized_read(std::istream&, std::string&, char);
	int year;
	std::tm date_published;
	//std::string genre;
	size_t num_genres;
	std::string* genre;
	int duration_min;
	std::string country;
	std::string language;
	size_t num_directors;
	std::string* directors;
	std::string writer;
	std::string production_company;
	size_t num_actors;
	std::string* actors;
	long usa_gross_income;
	long worldwide_gross_income;
};

#endif // MOVIE_HPP
