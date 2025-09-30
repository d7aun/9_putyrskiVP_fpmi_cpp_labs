
// solve task with usage of
// dymanic arrays
#include <iostream>
#include <random>
//Lab 3 task 37

void tryRead(int& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number\n" << std::endl;
		exit(0);
	}
}
void tryReadDbl(double& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number\n" << std::endl;
		exit(0);
	}
}

void f1(double* ar, int size)
{
	std::cout << "Number of elements of longest ordered chain:\n";
	int counterIncr, counterDecr, metaCounter = 1;
	for (int i = 0; i < size; i++)
	{
		counterIncr = 1, counterDecr = 1;
		for (int j = i + 1; j < size; j++)
		{
			if (ar[j - 1] <= ar[j])
				counterIncr++;
			else
				break;
		}
		for (int j = i + 1; j < size; j++)
		{
			if (ar[j - 1] >= ar[j])
				counterDecr++;
			else
				break;
		}
		if (counterDecr > counterIncr)
			counterIncr = counterDecr;
		if (metaCounter < counterIncr)
			metaCounter = counterIncr;
	}
	std::cout << metaCounter << std::endl;
}

void f2(double* ar, int size)
{
	std::cout << "Product of elements between elements with gratest & lowest absolute values in array:\n";
	int iMax = 0, iMin = 0;
	double bufMax = fabs(ar[0]), bufMin = fabs(ar[0]);
	for (int i = 1; i < size; i++)
	{
		double absNum = fabs(ar[i]);
		if (absNum > bufMax)
		{
			bufMax = absNum;
			iMax = i;
		}
		if (absNum < bufMin)
		{
			bufMin = absNum;
			iMin = i;
		}
	}
	if (iMin > iMax)
	{
		iMin += iMax;
		iMax = iMin - iMax;
		iMin = iMin - iMax;
	}
	if (abs(iMin - iMax) == 1)
	{
		std::cout << "Elements with gratest & lowest absolute values are next to each other.\nCan't find the product...\n";
	}
	else
	{
		double prod = 1;
		if (iMax == iMin)
		{
			std::cout << "All elements are the same. Can't find the product...\n";
		}
		else
		{
			for (int i = iMin + 1; i < iMax; i++)
				prod *= ar[i];
			std::cout << prod << std::endl;
		}
	}
}

void f3(double* ar, int size)
{
	for (int i = 0; i < size; i += 2)
		for (int j = 2; j < size; j += 2)
			if (ar[j] < ar[j - 2])
			{
				ar[j] += ar[j - 2];
				ar[j - 2] = ar[j] - ar[j - 2];
				ar[j] = ar[j] - ar[j - 2];
			}
	for (int i = 1; i < size; i += 2)
		for (int j = 3; j < size; j += 2)
			if (ar[j] > ar[j - 2])
			{
				ar[j] += ar[j - 2];
				ar[j - 2] = ar[j] - ar[j - 2];
				ar[j] = ar[j] - ar[j - 2];
			}
	std::cout << "Your reorganized array:\n";
	for (int i = 0; i < size; i++)
		std::cout << ar[i] << std::endl;
}

int main()
{
	int size, nmbr, maxLength = 100;
	double arNmbr;
	double *ar = new double[maxLength];
	std::cout << "Input size of array:\n";
	tryRead(size);
	if (size > maxLength || size < 1)
	{
		std::cout << "Less than 100 (or maybe more than 0), please\n";
		exit(0);
	}
	std::cout << "How to fill the array (enter the number):\nRandom(1)    By hand(2)\n";
	tryRead(nmbr);
	if (nmbr != 1 && nmbr != 2)
	{
		std::cout << "Follow the rules!\n";
		exit(0);
	}
	if (nmbr == 2)
	{
		std::cout << "Enter:\n";
		for (int i = 0; i < size; i++)
		{
			tryReadDbl(arNmbr);
			ar[i] = arNmbr;
		}
	}
	else
	{
		double strt, fnsh;
		std::cout << "Enter an interval of randomization:\n";
		tryReadDbl(strt);
		tryReadDbl(fnsh);
		if (strt > fnsh)
		{
			strt += fnsh;
			fnsh = strt - fnsh;
			strt = strt - fnsh;
		}
		std::mt19937 gen(45218965);
		for (int i = 0; i < size; i++)
		{
			std::uniform_real_distribution<double> dist(strt, fnsh);
			ar[i] = dist(gen);
		}

	}
	std::cout << "Your array:\n";
	for (int i = 0; i < size; i++)
		std::cout << ar[i] << std::endl;

	f1(ar, size);
	f2(ar, size);
	f3(ar, size);

	delete[] ar;
	return 0;
}
