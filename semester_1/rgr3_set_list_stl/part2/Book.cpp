#include "Book.h"


bool isDigit(const std::string& s)
{
	if (s[0] >= '0' && s[0] <= '9')
		return true;
	return false;
}
bool isInt(const std::string& s)
{
	if (!isDigit(s))
		return 0;
	int a = stoi(s);
	std::string reS = std::to_string(a);
	int dif = size(s) - size(reS);
	std::string xreS;
	for (int i = 0; i < dif; ++i)
		xreS += '0';
	xreS += reS;
	if (xreS != s && reS != s)
		return false;
	return true;
}
std::vector<author> stoa(const std::string& info)
{
	size_t beg;
	size_t end;
	size_t counter = 0;
	author a;
	std::vector<author> v;
	bool finalStep = false;

	beg = 0;
	end = info.find_first_of(' ');

	while (!finalStep)
	{
		if (info.find_first_of(',', beg) == std::string::npos)
		{
			finalStep = true;
		}
		a.sur_ = info.substr(beg, end - beg);

		beg = end + 1;
		end = info.find_first_of(' ', beg);
		a.name_ = info.substr(beg, end - beg);

		beg = end + 1;
		end = info.find_first_of(',', beg);
		if (end == std::string::npos)
			end = size(info);
		a.fath_ = info.substr(beg, end - beg);

		counter = 0;
		bool mm = true;
		for (author xa : v)
		{
			if (xa.sur_ > a.sur_)
			{
				v.insert(v.begin() + counter, a);
				mm = false;
				break;
			}
			++counter;
		}
		if (mm)
			v.push_back(a);

		beg = end + 2;
		end = info.find_first_of(' ', beg);
	}

	return v;
}




book::book()
{
	id_ = 0;
	title_ = "";
	edition_year_ = 0;
}
book::book(const book& rhs)
{
	id_=rhs.id_;
	title_ = rhs.title_;
	edition_year_ = rhs.edition_year_;
	authors_ = rhs.authors_;
}
book::book(int id, std::string& title, int editionYear, std::string& authors)
{
	id_ = id;
	title_ = title;
	edition_year_= editionYear;
	authors_ = stoa(authors);
}
void book::setID(int id)
{
	id_ = id;
}
void book::setTitle(const std::string& title)
{
	title_ = title;
}
std::string book::getTitle()
{
	return title_;
}
std::string book::getTitle() const
{
	return title_;
}
void book::setEY(int editionYear)
{
	edition_year_ = editionYear;
}
void book::setAuthors(const std::vector<author>& authors)
{
	authors_ = authors;
}
std::vector<author> book::getAuthors()
{
	return authors_;
}
std::vector<author> book::getAuthors() const
{
	return authors_;
}
void book::addAuthor(const author& a)
{
	int counter = 0;
	bool mm = false;
	for (author xa : authors_)
	{
		if (xa.getSur() > a.getSur())
		{
			authors_.insert(authors_.begin() + counter, a);
			mm = true;
			break;
		}
		++counter;
	}
	if (!mm)
		authors_.push_back(a);
}
void book::deleteAuthor(const author& a)
{
	int counter = 0;
	for (author xa : authors_)
	{
		if (xa.getSur() == a.getSur() && xa.getName() == a.getName() && xa.getFath() == a.getFath())
		{
			authors_.erase(authors_.begin() + counter);
		}
		++counter;
	}
}
book::~book(){}
void book::print()
{
	std::cout << id_ << " \"" << title_ << "\" " << edition_year_ << " ";
	bool mm = false;
	for (author a : authors_)
	{
		if (mm)
		{
			std::cout << ", ";
		}
		std::cout << a.getSur() << " " << a.getName() << " " << a.getFath();
		mm = true;
	}
}





author::author()
{
	sur_ = "Unknown";
	name_ = "";
	fath_ = "";
}
author::author(std::string& s, std::string& n, std::string& f)
{
	sur_ = s;
	name_ = n;
	fath_ = f;
}
std::string author::getSur()
{
	return sur_;
}
std::string author::getSur() const
{
	return sur_;
}
std::string author::getName()
{
	return name_;
}
std::string author::getName() const
{
	return name_;
}
std::string author::getFath()
{
	return fath_;
}
std::string author::getFath() const
{
	return fath_;
}

bool author::operator == (author oth)
{
	return (sur_ == oth.sur_ && name_ == oth.name_ && fath_ == oth.fath_);
}





void library::init(const std::string& inFile)
{
	std::ifstream in(inFile);
	if (!in)
		return;

	size_t beg, end;
	std::string info, tmp;
	book b;
	while (!in.eof())
	{
		getline(in, info);
		beg = 0;
		end = info.find_first_of(' ');
		b.setID(stoi(info.substr(beg, end - beg)));

		beg = end + 1;
		end = info.find_first_of(' ', beg);
		b.setTitle(info.substr(beg, end - beg));

		beg = end + 1;
		end = info.find_first_of(' ', beg);
		b.setEY(stoi(info.substr(beg, end - beg)));

		beg = end + 1;
		end = size(info);
		tmp = info.substr(beg, end - beg);
		b.setAuthors(stoa(tmp));


		lib_.push_back(b);
	}
	lib_.sort([](book a, book b) {return a.getTitle() < b.getTitle(); });
}
std::list<book> library::getLib()
{
	return lib_;
}
void library::addBook(const book& b)
{
	lib_.push_back(b);
	lib_.sort([](book a, book b) {return a.getTitle() < b.getTitle(); });
}
void library::deleteBook(const book& b)
{
	std::list<book>::iterator it = lib_.begin();
	for (book xb : lib_)
	{
		if (xb.getAuthors().size() != b.getAuthors().size())
		{
			++it;
			continue;
		}
		int N=xb.getAuthors().size();


		bool mm = true;
		for (int i = 0; i < N; ++i)
			if (!(xb.getAuthors()[i]== b.getAuthors()[i]))
			{
				++it;
				mm = false;
				break;
			}
		if (!mm)
			continue;


		if (xb.getTitle()==b.getTitle())
		{
			lib_.erase(it);
			break;
		}
		++it;
	}
}
void library::findByTitle(const std::string& t)
{
	for (book xb : lib_)
	{
		if (xb.getTitle() == t)
		{
			xb.print();
			std::cout << "\n";
		}
	}
}
void library::findByAuthor(const std::string& aSur)
{
	for (book xb : lib_)
	{
		std::vector<author> v = xb.getAuthors();
		for (author xa : v)
		{
			if (xa.getSur() == aSur)
			{
				xb.print();
				break;
			}
		}
	}
}