#include <iostream>
#include <string>
#include <windows.h>
std::string findPalyndroms(std::string s)
{
	std::string palyndroms;
	std::string punct=" .,:;?!()/";
	bool noMoreWords = false;
	size_t Length = 0;
	while (!noMoreWords)
	{
		size_t strt = s.find_first_not_of(punct);
		size_t end = s.find_first_of(punct, strt);
		if (end == std::string::npos)
		{
			end = s.size();
			noMoreWords = true;
		}
		end -= 1;
		size_t util = (end - strt) / 2;
		bool isPaly = true;
		if (end != strt)
		{
			for (int i = 0; i <= util; ++i)
				if (s.compare(strt + i, 1, s, end - i, 1) != 0)
				{
					isPaly = false;
					break;
				}
			if (isPaly == true)
			{
				size_t palyLength = end - strt;
				if (palyLength > Length)
				{
					palyndroms = s.substr(strt, end - strt + 1);
					Length = palyLength;
				}
				else if (palyLength == Length)
					palyndroms += ", " + s.substr(strt, end - strt + 1);
			}
		}
		s.erase(0, end + 1);
	}
	if (palyndroms == "")
		return "No palyndroms";
	return palyndroms;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Input list of words separated with punctuation marks (or blanks):\n";
	std::string s;
	getline(std::cin, s);
	if (s.empty())
	{
		//throw "No words in your text";
		std::cout << "No words in your text";
		return 1;
	}
	std::string palyndroms = findPalyndroms(s);

	std::cout << "Longest palyndroms in your text:\n" << palyndroms;

	return 0;
}
