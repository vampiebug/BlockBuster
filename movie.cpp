// Movie.cpp
#include "movie.hpp"
#include <sstream>
#include <iostream>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

// constructor
Movie::Movie()
	: year(0),
    //ask about this line: commented out the version with error, replaced it with fixed one
	  //date_published{},
      date_published(),
	  num_genres(0),
	  genre(nullptr),
	  duration_min(0),
	  country(),
	  language(),
	  directors(nullptr),
	  writer(),
	  production_company(),
	  num_actors(0),
	  actors(nullptr),
	  usa_gross_income(-1),
	  worldwide_gross_income(-1)
{
	// nothing to do here
}

//BIG 3:
//copy ctor --check if these should be shallow or deep references. Shallow might work because movies are big objects, but check for best practice. copy operator at least needs to be deep because things will be deleted.
//need to be deep copies for dynamic objects 
Movie::Movie(const Movie& movie) : 
//everything that isn't dynamic is just declared normally
    title(movie.title),
    year(movie.year),
	date_published(movie.date_published),
	//std::string genre;
	num_genres(movie.num_genres),
    //everything that is dynamic needs a new object. Need to actually fill that in in the brackets, but initialize here.
    genre(new std::string[this->num_genres]),
	duration_min(movie.duration_min),
	country(movie.country),
	language(movie.language),
	num_directors(movie.num_directors),
	directors(new std::string[this->num_directors]),
	writer(movie.writer),
	production_company(movie.production_company),
	num_actors(movie.num_actors),
	actors(new std::string[this->num_actors]),
	usa_gross_income(movie.usa_gross_income),
	worldwide_gross_income(movie.worldwide_gross_income)

{
    //fill in the genres
    for (int i = 0; i < this->num_genres; i++){
        //should work bc accessing element is dereferencing
        this->genre[i] = movie.genre[i];
    }
    //fill in the directors
    for (int i = 0; i < this->num_directors; i++){
        this->directors[i] = movie.directors[i];
    }
    //fill in the genres
    for (int i = 0; i < this->num_actors; i++){
        this->actors[i] = movie.actors[i];
    }
}
//assignment op--also check if this should be done by pointer or copy.
Movie& Movie::operator=(const Movie& movie){
    //check this isn't self-assign by comparing addresses
    if (this != &movie){
        //delete the heap objects.
        delete[] this->actors;
        delete[] this->genre;
        delete[] this->directors;
        //reassign everything
        this->title = movie.title;
        this->year = movie.year;
        this->date_published = movie.date_published;
        //std::string genre;
        this->num_genres = movie.num_genres;
        this->genre = new std::string[this->num_genres];
        for (int i = 0; i < this->num_genres; i++){
            //should work bc accessing element is dereferencing
            this->genre[i] = movie.genre[i];
        }
        this->duration_min = movie.duration_min;
        this->country = movie.country;
        this->language = movie.language;
        this->num_directors = movie.num_directors;
        this->directors = new std::string[this->num_directors];
        for (int i = 0; i < this->num_directors; i++){
            //should work bc accessing element is dereferencing
            this->directors[i] = movie.directors[i];
        }
        this->writer = movie.writer;
        this->production_company = movie.production_company;
        this->num_actors = movie.num_actors;
        this->actors = new std::string[this->num_actors];
        for (int i = 0; i < this->num_actors; i++){
            //should work bc accessing element is dereferencing
            this->actors[i] = movie.actors[i];
        }
        this->usa_gross_income = movie.usa_gross_income;
        this->worldwide_gross_income = movie.worldwide_gross_income;
    }
    //return *this (pointer to current object)
    return *this;

}
//dtor--delete all dynamic members. Again, check requirements. Should just be genres, actors, and directors
Movie::~Movie(){
    delete[] this->actors;
    delete[] this->genre;
    delete[] this->directors;
}




bool operator==(const Movie& movie, const std::string& title)
{
	return movie.title == title;
}

bool operator!=(const Movie& movie, const std::string& title)
{
	return ! (movie == title);
}

bool operator==(const Movie& movie_1, const Movie& movie_2)
{
    // 1) Simple members
    if (movie_1.title                  != movie_2.title)                  return false;
    if (movie_1.year                   != movie_2.year)                   return false;
    if (movie_1.duration_min           != movie_2.duration_min)           return false;
    if (movie_1.country                != movie_2.country)                return false;
    if (movie_1.language               != movie_2.language)               return false;
    if (movie_1.writer                 != movie_2.writer)                 return false;
    if (movie_1.production_company     != movie_2.production_company)     return false;
    if (movie_1.usa_gross_income       != movie_2.usa_gross_income)       return false;
    if (movie_1.worldwide_gross_income != movie_2.worldwide_gross_income) return false;

    // 2) tm fields inline
    const std::tm& a = movie_1.date_published;
    const std::tm& b = movie_2.date_published;
    if (a.tm_year != b.tm_year
     || a.tm_mon  != b.tm_mon
     || a.tm_mday != b.tm_mday
     || a.tm_hour != b.tm_hour
     || a.tm_min  != b.tm_min
     || a.tm_sec  != b.tm_sec)
        return false;

    // 3) genres array
    if (movie_1.num_genres != movie_2.num_genres) return false;
    if (!std::equal(
            movie_1.genre,
            movie_1.genre + movie_1.num_genres,
            movie_2.genre))
        return false;

    // 4) directors array
    if (movie_1.num_directors != movie_2.num_directors) return false;
    if (!std::equal(
            movie_1.directors,
            movie_1.directors + movie_1.num_directors,
            movie_2.directors))
        return false;

    // 5) actors array
    if (movie_1.num_actors != movie_2.num_actors) return false;
    if (!std::equal(
            movie_1.actors,
            movie_1.actors + movie_1.num_actors,
            movie_2.actors))
        return false;

    // all checks passed
    return true;
}

const std::string Movie::get_title() const
{
	return this->title;
}

bool operator!=(Movie& movie_1, Movie& movie_2)
{
    return !(movie_1 == movie_2);
}

bool operator<(const Movie& movie_1, const Movie& movie_2)
{
	return movie_1.title < movie_2.title;
}

bool operator>(const Movie& movie_1, const Movie& movie_2)
{
	return movie_2.title > movie_1.title;
}

// Static helper to read and sanitize a field
bool Movie::sanitized_read(std::istream& is, std::string& field, char delim)
{
	std::string raw;
	if (!std::getline(is, raw, delim))
		return false;

	// Remove leading/trailing punctuation
	auto is_punct = [](char c)
	{
		return std::ispunct(static_cast<unsigned char>(c));
	};
	while (!raw.empty() && is_punct(raw.front())) raw.erase(raw.begin());
	while (!raw.empty() && is_punct(raw.back())) raw.pop_back();

	// Remove all dollar signs
	raw.erase(std::remove(raw.begin(), raw.end(), '$'), raw.end());

	// Trim whitespace
	auto is_space = [](char c)
	{
		return std::isspace(static_cast<unsigned char>(c));
	};
	raw.erase(raw.begin(), std::find_if_not(raw.begin(), raw.end(), is_space));
	raw.erase(std::find_if_not(raw.rbegin(), raw.rend(), is_space).base(), raw.end());

	field = std::move(raw);
	return true;
}


// Convert to human-readable string
std::string Movie::to_string() const
{
	std::ostringstream oss;
	oss << "Title:                 " << title << "\n"
	    << "Year:                  " << year << "\n"
	    << "Date Published:        " << std::put_time(&date_published, "%Y-%m-%d") << "\n"
	    << "Genres:                ";
	for (size_t i = 0; i < num_genres; ++i)
	{
		if (i > 0) oss << ", ";
		oss << genre[i];
	}
	oss << "\n"
	    << "Duration (min):        " << duration_min << "\n"
	    << "Country:               " << country << "\n"
	    << "Language:              " << language << "\n"
//	    << "Director:              " << director << "\n"
	    << "Directors:"
	    ;
	for (size_t i = 0; i < num_directors; ++i)
	{
		if (i > 0) oss << ", ";
		oss << directors[i];
	}

	oss << "Writer:                " << writer << "\n"
	    << "Production Company:    " << production_company << "\n"
	    << "Actors:                ";
	for (size_t i = 0; i < num_actors; ++i)
	{
		if (i > 0) oss << ", ";
		oss << actors[i];
	}
	oss << "\n"
	    << "USA Gross Income:      " << (usa_gross_income != -1 ? std::to_string(usa_gross_income) : "N/A") << "\n"
	    << "Worldwide Gross Income:" << (worldwide_gross_income != -1 ? std::to_string(worldwide_gross_income) : "N/A") << "\n";
	return oss.str();
}

std::string Movie::one_liner() const
{
    std::ostringstream oss, genre_ss, directors_ss, actors_ss;

    // Helpers to convert between UTF-8 and UTF-32 (one char == one code point)
    static std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;

    auto to_u32 = [&](const std::string& s) {
        return conv.from_bytes(s);
    };
    auto to_utf8 = [&](const std::u32string& u) {
        return conv.to_bytes(u);
    };

    // fmt works in code points, so multi-byte UTF-8 is counted correctly
    auto fmt = [&](const std::string& s, int length = 30) {
        std::u32string u = to_u32(s);
        if (static_cast<int>(u.size()) > length) {
            // truncate to (length-3) code points, then add "..."
            std::u32string u2 = u.substr(0, length - 3);
            return to_utf8(u2) + "...";
        } else {
            // pad with spaces so that visible chars == length
            int pad = length - static_cast<int>(u.size());
            return s + std::string(pad, ' ');
        }
    };

    // Title padded/truncated to 35 chars
    oss << fmt(title, 35) << " (" 
        << year << ", ";

    // Genres
    for (size_t i = 0; i < num_genres; ++i) {
        genre_ss << genre[i];
        if (i + 1 < num_genres) genre_ss << ", ";
    }
    oss << fmt(genre_ss.str());

    // Directors
    for (size_t i = 0; i < num_directors; ++i) {
        directors_ss << directors[i];
        if (i + 1 < num_directors) directors_ss << ", ";
    }
    oss << fmt(directors_ss.str());

    // Actors
    for (size_t i = 0; i < num_actors; ++i) {
        actors_ss << actors[i];
        if (i + 1 < num_actors) actors_ss << ", ";
    }
    oss << fmt(actors_ss.str());

    oss << "]";
    return oss.str();
}

// output operator
std::ostream& operator<<(std::ostream& os, const Movie& m)
{
	return os << m.one_liner();
}

