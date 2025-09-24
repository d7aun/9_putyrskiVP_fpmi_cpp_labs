// Lab 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
//Lab 2 task 5

void getValue(int& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number." << std::endl;
		exit(0);
	}
}

void switchPlace(int realNum, int &reNum)
{
	while (realNum > 0)
	{
		int t = realNum;
		int d = t % 10;
		realNum /= 10;
		reNum = (reNum + d) * 10;
	}
	reNum /= 10;
}
int main()
{
	std::cout << "Input num:\n";
	int num;
	while (true)
	{
		getValue(num);
		if (num < 1)
			std::cout << "Try positive number!\n";
		else break;
	}

	int realNum, reNum;
	int realSqrNum, reSqrNum;
	int buf, counter = 10;
	std::cout << "Double palindroms less than num:\n";
	for (int i = 10; i <= num; i++)
	{
		reNum = 0;
		reSqrNum = 0;
		realNum = counter;
		/*while (realNum > 0)
		{
			t = realNum;
			d = t % 10;
			realNum /= 10;
			reNum = (reNum + d) * 10;
		}*/
		switchPlace(realNum, reNum);

		buf = counter * counter;
		realSqrNum = buf;
		/*while (buf > 0)
		{
			t = buf;
			d = t % 10;
			buf /= 10;
			reSqrNum = (reSqrNum + d) * 10;
		}*/
		switchPlace(buf, reSqrNum);
		if (reNum == counter && reSqrNum == realSqrNum)
		{
			std::cout << counter << std::endl;
		}

		counter++;
	}
	return 0;
	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


