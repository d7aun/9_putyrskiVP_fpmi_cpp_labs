#include "Book.h"

int main()
{
	std::string inFile = "input.txt";

	library lib;
	lib.init(inFile);

	lib.findByAuthor("Abidov"); //findByAuthor
	std::cout << "\n\n";
	lib.findByTitle("BBB"); //findByTitle
	std::cout << "\n\n";

	std::string a = "Gabidov G G", t="GGG";
	book b(345, t, 2900, a);
	lib.addBook(b); //addBook
	lib.findByTitle("GGG");
	std::cout << "\n\n";

	a = "Dabidov D D", t = "BBB";
	book bb(98, t, 287, a);
	lib.deleteBook(bb); //deleteBook
	lib.findByTitle("BBB");
	std::cout << "\n\n";


	std::string s = "Cabidov", nf = "C";
	author auth(s, nf, nf);
	bb.addAuthor(auth); //addAuthor
	lib.addBook(bb);
	lib.findByTitle("BBB");
	std::cout << "\n\n";
	lib.deleteBook(bb);


	s = "Dabidov", nf = "D";
	author auth2(s, nf, nf);
	bb.deleteAuthor(auth2); //deleteAuthor
	lib.addBook(bb);
	lib.findByTitle("BBB");
	std::cout << "\n\n";



	return 0;
}
