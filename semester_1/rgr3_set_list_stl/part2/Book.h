#pragma once
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>

class author
{

	std::string sur_;
	std::string name_;
	std::string fath_;

public:
	author();
	author(std::string& s, std::string& n, std::string& f);
	std::string getSur();
	std::string getSur() const;
	std::string getName();
	std::string getName() const;
	std::string getFath();
	std::string getFath() const;
	friend std::vector<author> stoa(const std::string& s);
	bool operator == (author oth);
};



class book
{
	int id_;
	std::string title_;
	int edition_year_;
	std::vector<author> authors_;

public:
	book();
	book(const book& rhs);
	book(int id, std::string& title, int editionYear, std::string& authors);
	void setID(int id);
	void setTitle(const std::string& title);
	std::string getTitle();
	std::string getTitle() const;
	void setEY(int editionYear);
	void setAuthors(const std::vector<author>& authors);
	std::vector<author> getAuthors();
	std::vector<author> getAuthors() const;
	void addAuthor(const author& a);
	void deleteAuthor(const author& a);
	~book();
	void print();
};



class library
{
	std::list<book> lib_;
public:
	library(){}
	std::list<book> getLib();
	void init(const std::string& inFile);
	void addBook(const book& b);
	void deleteBook(const book& b);
	void findByTitle(const std::string& t);
	void findByAuthor(const std::string& aSur);
	~library(){}
};