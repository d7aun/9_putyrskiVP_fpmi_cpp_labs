#include <iostream>
#include <set>
#include <string>
bool isDigit(const std::string& s)
{
	if (s[0] >= '0' && s[0] <= '9')
		return true;
	return false;
}
bool isInt(const std::string& s)
{
	if (!isDigit(s))
		return false;
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
int main()
{
	std::set<int> s;

	//initializing
	std::cout << "Enter a positive number (greater than 1) for testing the sieve of Eratosthenes: ";
	std::string tmp;
	getline(std::cin, tmp);
	if (!isInt(tmp))
	{
		std::cerr << "Try to read instructions w/ some attention\n";
		return 0;
	}
	int num = stoi(tmp);
	for (int i = 2; i <= num; ++i)
	{
		s.insert(i);
	}

	//the sieve of Eratosthenes
	std::set<int>::iterator it = s.begin();
	int multiplier = 0;
	for (it = s.begin(); it!=s.end();)
	{
		if (num / (*it) < (*it))
			break;
		multiplier = num / (*it);
		for (int i = 2; i <= multiplier; ++i)
			s.erase((*it) * i);
		++it;
	}

	it = s.begin();
	std::cout << "Prime numbers not exceeding " << num << ":\n";
	std::cout << (*it);
	++it;
	while (it != s.end())
	{
		std::cout << ' ' << (*it);
		++it;
	}
	std::cout << '\n';
}
