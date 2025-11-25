#include <iostream>
#include <fstream>
#include <string>
size_t longestChainSize(std::string str)
{
	size_t inCount = 1, maxCount = 1;
	size_t sz = str.size();
	if (sz == 1)
		return 1;
	if (sz == 0)
		return 0;
	for (size_t i = 0; i < sz - 1; ++i)
	{
		if (str[i] < str[i + 1])
			inCount++;
		else
		{
			if (inCount > maxCount)
				maxCount = inCount;
			inCount = 1;
		}
	}
	if (inCount > maxCount)
		maxCount = inCount;
	return maxCount;
}
int main()
{
	//std::ofstream("yt.txt");
	std::string inputFile = "input.txt";
	std::ifstream in;
	in.open(inputFile);
	if (!in)
	{
		std::cerr << "Input file error";
		return 1;
	}

	std::string str, longestChains = "";
	std::cout << longestChains;
	size_t maxChain = 0;
	int numOfStr = 0;
	while (!in.eof())
	{
		getline(in, str);
		if (longestChainSize(str) > maxChain)
		{
			maxChain = longestChainSize(str);
			longestChains = str;
			numOfStr = 9;
		}
		else if (longestChainSize(str) == maxChain && numOfStr > 0)
		{
			longestChains += "\n" + str;
			numOfStr--;
		}
	}
	std::cout << "Lines with longest increasing sublines (" << maxChain << " chars):\n" << longestChains;
}

