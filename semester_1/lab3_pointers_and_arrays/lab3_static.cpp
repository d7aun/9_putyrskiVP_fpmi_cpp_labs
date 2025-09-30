
// solve task with usage of
// static arrays
#include <iostream>
#include <random>
//Lab 3 task 19

const int maxLength = 100;

void tryRead(int& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number" << std::endl;
		exit(0);
	}
}
void tryReadDbl(double& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number" << std::endl;
		exit(0);
	}
}

void f1(double ar[maxLength], int size)
{
	std::cout << "Number of unique elements of array:\n";
	for (int i = 0; i < size; i++)
		for (int j = 1; j < size; j++)
			if (ar[j] > ar[j - 1])
			{
				ar[j] += ar[j - 1];
				ar[j - 1] = ar[j] - ar[j - 1];
				ar[j] = ar[j] - ar[j - 1];
			}
	int counter = 1;
	for (int i = 1; i < size; i++)
		if (ar[i] != ar[i - 1])
			counter += 1;
	std::cout << counter << std::endl;
}

void f2(double ar[maxLength], int size)
{
	std::cout << "Sum between first and last negative elements in array:\n";
	int first = -1, last = -1;
	for (int i = 0; i < size; i++)
	{
		if (ar[i] < 0)
		{
			first = i;
			break;
		}
	}
	for (int i = size - 1; i >= 0; i--)
	{
		if (ar[i] < 0)
		{
			last = i;
			break;
		}
	}
	double sum = 0;
	if (first == last)
	{
		std::cout << "Not enough negative numbers\n";
	}
	else
	{
		for (int i = first + 1; i < last; i++)
			sum += ar[i];
		std::cout << sum << std::endl;
	}
}

void f3(double ar[maxLength], int size)
{
	std::cout << "Enter upper limit for elements in array:\n";
	double X;
	tryReadDbl(X);
	for (int i = 0; i < size; i++)
		if (ar[i] <= X)
		{
			ar[i] = 0;
			for (int j = size - 1; j > 0; j--)			
				if (i < j && ar[j] != 0 && ar[j] > X)
				{
					ar[j] += ar[i];
					ar[i] = ar[j] - ar[i];
					ar[j] = ar[j] - ar[i];
					break;
					
				}
			/*
			Этот цикл, служащий для переброски нулей в конец массива, нужен,
            если используем f3 отдельно
			(без f1, которая преобразует исходный массив)
			*/
		}
	std::cout << "Your reorganized array:\n";
	for (int i = 0; i < size; i++)
		std::cout << ar[i] << std::endl;
}

int main()
{
	int size, nmbr;
	double ar[maxLength], arNmbr;
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

	f2(ar, size);
	f1(ar, size);
	f3(ar, size);
	
	return 0;
}
