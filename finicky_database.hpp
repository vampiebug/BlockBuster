#ifndef FINICKY_DATABASE_HPP
#define FINICKY_DATABASE_HPP

#include "movie.hpp"

#include <vector>
#include <memory>
#include <stdexcept>
#include <queue>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <iomanip>

template<typename T>
class FinickyDatabase
{
public:
	FinickyDatabase() = default;

	// Disable copying
	FinickyDatabase(const FinickyDatabase&) = delete;
	FinickyDatabase& operator=(const FinickyDatabase&) = delete;

	// Allow moving
	FinickyDatabase(FinickyDatabase&&) noexcept = default;
	FinickyDatabase& operator=(FinickyDatabase&&) noexcept = default;

	~FinickyDatabase() = default;

	// Database takes ownership
	void add(T* item)
	{
		data_.emplace_back(item);
		available_indices_.push(data_.size() - 1);
	}

	std::size_t size() const noexcept
	{
		return data_.size();
	}

	void read(T& out, std::size_t index)
	{
		if (index >= data_.size())
		{
			throw std::out_of_range("FinickyDatabase: index out of range");
		}
		auto& ptr = data_[index];
		if (!ptr)
		{
			throw std::runtime_error("FinickyDatabase: slot already read");
		}
		out = *ptr;
		ptr.reset();
	}

	bool readFirst(T& out)
	{
		while (!available_indices_.empty())
		{
			auto idx = available_indices_.front();
			auto& ptr = data_[idx];
			available_indices_.pop();
			if (ptr)
			{
				out = *ptr;
				ptr.reset();
				return true;
			}
		}
		return false;
	}

bool populate(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        return false;
    }

    std::string header;
    if (!std::getline(file, header))
    {
        file.close();
        return false; // invalid or empty file
    }

    while (true)
    {
        T* item = new T();

        if (!(file >> *item))
        {
            delete item;  // delete the last item if reading failed
            break;
        }

        add(item); // ownership transferred to database
    }

    file.close();

    return true;
}

private:
	std::vector<std::unique_ptr<T>> data_;
	std::queue<std::size_t> available_indices_; // quickly find next available slot
};

std::istream& operator>>(std::istream& is, Movie& m)
{
	std::string field;
	if (!std::getline(is, m.title, '\t'))
		return is;

	// Year
	std::getline(is, field, '\t');
	m.year = std::stoi(field);

	// Date published
	std::getline(is, field, '\t');
	std::istringstream ss(field);
	ss >> std::get_time(&m.date_published, "%Y-%m-%d");
	if (ss.fail())
	{
		ss.clear();
		ss.str("0000-00-00");
		ss >> std::get_time(&m.date_published, "%Y-%m-%d");
	}

	// Genres
	std::getline(is, field, '\t');
	std::vector<std::string> genres;
	{
		std::istringstream gss(field);
		std::string token;
		while (std::getline(gss, token, ','))
		{
			auto start = token.find_first_not_of(" \t");
			auto end   = token.find_last_not_of(" \t");
			if (start != std::string::npos)
				token = token.substr(start, end - start + 1);
			else
				token.clear();
			genres.push_back(token);
		}
	}
	m.num_genres = genres.size();
	delete[] m.genre;
	m.genre = new std::string[m.num_genres];
	for (size_t i = 0; i < m.num_genres; ++i)
		m.genre[i] = std::move(genres[i]);

	// Duration
	std::getline(is, field, '\t');
	m.duration_min = std::stoi(field);

	// Simple string fields
	std::getline(is, m.country, '\t');

	std::getline(is, m.language, '\t');

	std::getline(is, field, '\t');
	std::vector<std::string> directors;
	{
		std::istringstream dss(field);
		std::string token;
		while (std::getline(dss, token, ','))
		{
			auto start = token.find_first_not_of(" \t");
			auto end   = token.find_last_not_of(" \t");
			if (start != std::string::npos)
				token = token.substr(start, end - start + 1);
			else
				token.clear();
			directors.push_back(token);
		}
	}

	m.num_directors = directors.size();

	m.directors = new std::string[m.num_directors];
	for (size_t i = 0; i < m.num_directors; ++i)
		m.directors[i] = std::move(directors[i]);
	std::getline(is, m.writer, '\t');
	std::getline(is, m.production_company, '\t');

	// Actors
	std::getline(is, field, '\t');
	std::vector<std::string> actors_list;
	{
		std::istringstream ass(field);
		std::string token;
		while (std::getline(ass, token, ','))
		{
			auto start = token.find_first_not_of(" \t");
			auto end   = token.find_last_not_of(" \t");
			if (start != std::string::npos)
				token = token.substr(start, end - start + 1);
			else
				token.clear();
			actors_list.push_back(token);
		}
	}
	m.num_actors = actors_list.size();
	delete[] m.actors;
	m.actors = new std::string[m.num_actors];
	for (size_t i = 0; i < m.num_actors; ++i)
		m.actors[i] = std::move(actors_list[i]);

	std::getline(is, field, '\t');
	{
		std::string digits;
		for (char c : field)
			if (std::isdigit(static_cast<unsigned char>(c)))
				digits.push_back(c);
		m.usa_gross_income = digits.empty() ? -1 : std::stol(digits);
	}

	if (std::getline(is, field))
	{
		std::string digits;
		for (char c : field)
			if (std::isdigit(static_cast<unsigned char>(c)))
				digits.push_back(c);
		m.worldwide_gross_income = digits.empty() ? -1 : std::stol(digits);
	}

	return is;
}


#endif // FINICKY_DATABASE_HPP

