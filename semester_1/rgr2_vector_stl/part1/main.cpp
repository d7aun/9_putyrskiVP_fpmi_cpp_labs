#include <iostream>
#include <vector>
#include <string>

using vec = std::vector<int>;

bool isDigit(const std::string& s)
{
	if (s == "")
		return false;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '-')
		return true;
	return false;
}
bool isInt(const std::string& s)
{
	if (!isDigit(s))
		return false;
	if (s.size() > 9)
		return false;
	int a = stoi(s);
	std::string reS = std::to_string(a);
	if (reS != s)
		return false;
	return true;
}
void fillVector(vec& v)
{
	std::cout << "Enter numbers devided with a space.\nOnly integers would be counted:\n";
	std::string numbers, numSt;
	getline(std::cin, numbers);
	if (numbers == "")
		return;
	size_t begN = 0;
	size_t endN = numbers.find_first_of(' ');
	while (endN != std::string::npos)
	{
		numSt = numbers.substr(begN, endN-begN);
		if (isInt(numSt))
			v.push_back(stoi(numSt));
		begN = endN + 1;
		endN = numbers.find_first_of(' ', begN);
	}
	endN = size(numbers);
	numSt = numbers.substr(begN, endN - begN);
	if (isInt(numSt))
		v.push_back(stoi(numSt));
}
void myVec(const vec& v)
{
	size_t size = v.size();
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << v[i] << ' ';
	}
	std::cout << "\n\n";
}
double arMean(const vec& v)
{
	size_t size = v.size();
	double sum = 0;
	for (size_t i = 0; i < size; ++i)
		sum += v[i];
	sum /= size;
	return sum;
}
size_t quanEq(vec& v, int num)
{
	size_t quan = 0;
	vec::iterator begV = v.begin();
	vec::iterator endV = v.end();
	vec::iterator it = std::find(begV, endV, num);
	while (it != endV)
	{
		++quan;
		it = std::find(++it, endV, num);
	}
	return quan;
}
size_t quanLess(vec& v, int num)
{
	size_t quan = 0;
	vec::iterator begV = v.begin();
	vec::iterator endV = v.end();
	vec::iterator it = std::find_if(begV, endV, [num](int n) {return n < num; });
	while (it != endV)
	{
		++quan;
		it = std::find_if(++it, endV, [num](int n) {return n < num; });
	}
	return quan;
}
void change0toArMean(vec& v)
{
	size_t size = v.size();
	vec::iterator begV = v.begin();
	vec::iterator endV = v.end();
	vec::iterator it = std::find(begV, endV, 0);
	double arM = arMean(v);
	while (it != endV)
	{
		*it = arM;
		it = std::find(++it, endV, 0);
	}
}
void addIntervalSum(vec& v)
{
	size_t sum = 0;
	size_t size = v.size();
	std::string tmp;
	getline(std::cin, tmp);
	if (isInt(tmp))
	{
		int strt = stoi(tmp);
		getline(std::cin, tmp);
		if (isInt(tmp))
		{
			int fnsh = stoi(tmp);

			if (strt > fnsh)
				std::swap(strt, fnsh);
			if (strt == fnsh)
				throw "The borders coinside";
			if (fnsh - strt == 1)
				throw "No numbers between the borders";
			if (strt <= 0)
				throw "The borders cannot be less or equal to 0";
			if (fnsh>size)
				throw "The interval exceeds the quantity of numbers";
			for (int i = strt; i < fnsh - 1; ++i)
				sum += v[i];
			std::cout << "The sum is " << sum << '\n';
			for (int i = 0; i < size; ++i)
				v[i]+=sum;
		}
		else
		{
			throw "Oops, not a number";
		}
	}
	else
	{
		throw "Oops, not a number";
	}
}
void replaceEvensWDif(vec& v)
{
	int max = v[0], min = v[0], dif = 0;
	size_t size = v.size();
	for (int i = 1; i < size; ++i)
	{
		if (v[i] > max)
			max = v[i];
		if (v[i] < min)
			min = v[i];
	}
	std::cout << "Max is " << max << ", min is " << min << '\n';
	dif = max - min;
	for (int i = 0; i < size; ++i)
		if (v[i] % 2 == 0)
			v[i] = dif;
}
void deleteCoinside(vec& v)
{
	vec::iterator begV = v.begin();
	size_t size = v.size();
	for (size_t i = 0; i < v.size(); ++i)
	{
		for (size_t j = i + 1; j < v.size();)
		{
			if (v[i] == v[j])
				v.erase(begV + j);
			else
				++j;
		}
	}
	/*
	vec::iterator begV = v.begin();
	vec::iterator endV = v.end();
	for (vec::iterator it = begV; it != endV;)
	{
		vec::iterator forDelete = std::find(it + 1, endV, *it);
		while (forDelete != endV)
		{
			v.erase(forDelete);
			forDelete = std::find(it + 1, endV, *it);
		}
		++it;
	}
	*/
}

int main()
{
	vec v;

	fillVector(v);
	std::cout << "The numbers are: ";
	size_t size = v.size();
	if (size == 0)
	{
		std::cout << "-";
		return 0;
	}
	myVec(v);
	std::cout << "Quantity of the numbers is " << size << "\n\n";


	std::cout << "Arithmetic mean of the numbers is " << arMean(v) << "\n\n";

	std::cout << "Enter an integer: ";
	std::string j;
	getline(std::cin, j);
	std::cout << "Quantity of the numbers equal to " << j << " is ";
	if (isInt(j))
	{
		int num = stoi(j);
		std::cout << quanEq(v, num) << "\n\n";


		std::cout << "Quantity of the numbers less than " << j << " is ";
		std::cout << quanLess(v, num) << "\n\n";
	}
	else
		std::cout << "0 - " << j << " is not an int\n";

	std::cout << "Change 0's to arithmetic mean:\n";
	change0toArMean(v);
	myVec(v);

	try
	{
		std::cout << "Enter 2 numbers as borders of an interval (max value is " << v.size() << "):\n";
		addIntervalSum(v);
		std::cout << "Add sum of the interval to all numbers: \n";
		myVec(v);
	}
	catch (const char* er)
	{
		std::cerr << "Cannot find sum of numbers in the interval: " << er << "\n\n";
	}

	std::cout << "Replace all even numbers with difference of max and min:\n";
	replaceEvensWDif(v);
	myVec(v);

	std::cout << "Delete all numbers that coinside except one:\n";
	deleteCoinside(v);
	myVec(v);

	return 0;
}
