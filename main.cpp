#include <iostream>

int main() {
    using std::cout; // будем использовать cout из std
    cout << "Hello, world!\n";
    return 0;
}


// Lab 1 task 2

#include <iostream>
using namespace std;

int getValue()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{

		int z;
		cin >> z;

		// Проверка на предыдущее извлечение
		if (cin.fail() || cin.peek() != '\n') // если предыдущее извлечение оказалось неудачным(с буквами) или частично
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";

		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения


			return z;
		}
	}
}
int main()
{
	cout << "Input n: " << endl;
	int n;
	while (true)
	{
		n = getValue();
		if (n <= 0)
		{
			cout << "Try again!" << endl;
		}
		else break;
	}
	int s=0, p=1;

	for (int i = 1; i <= n; i++)
	{
		if (i % 2 == 0)
			p = p * i;
		else
			s = s + i;

	}
	cout << "Summa: " << s << " Proizvedenie: " << p << endl;
	return 0;


// Lab 1 task 3

#include <iostream> 
#include <math.h>
using namespace std;

int getValue()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{

		int z;
		cin >> z;

		// Проверка на предыдущее извлечение
		if (cin.fail() || cin.peek() != '\n') // если предыдущее извлечение оказалось неудачным(с буквами) или частично
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";

		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения


			return z;
		}
	}
}
int main()
{
	cout << "Input n: " << endl;
	int n;
	while (true)
	{
		n = getValue();
		if (n <= 0)
		{
			cout << "Try again!" << endl;
		}
		else break;
	}
	unsigned int s=0;

	for (int i = 1; i <= n; i++)
	{
		s = s + pow(i, i);
	}
	cout << "Summa: " << s << endl;
	return 0;
}
/* При больших n (напр. 100, 200 и т. д.) значение полученной суммы s превышает максимальное
* значение, которое может принять переменная (в моем случае, unsighned int), потому s выставляется 
* на максимальное допустимое число 4294967295
*/


// Lab 1 task 7

#include <iostream> 
#include <math.h>
using namespace std;

int get_int_Value()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{

		int z;
		cin >> z;

		// Проверка на предыдущее извлечение
		if (cin.fail() || cin.peek() != '\n') // если предыдущее извлечение оказалось неудачным(с буквами) или частично
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";

		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения


			return z;
		}
	}
}

double get_dbl_Value()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{

		double z;
		cin >> z;

		// Проверка на предыдущее извлечение
		if (cin.fail() || cin.peek() != '\n') // если предыдущее извлечение оказалось неудачным(с буквами) или частично
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";

		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения


			return z;
		}
	}
}
int main()
{
	cout << "Input quantity of numbers n: " << endl;
	int n;
	while (true)
	{
		n = get_int_Value();
		if (n <= 0)
		{
			cout << "Try again!" << endl;
		}
		else break;
	}
	double s=0;
	double mn = 0, mx = 0;

	for (int i = 1; i <= n; i++)
	{
		double d=get_dbl_Value();
		s += d;
		if (i == 1)
		{
			mx = d;
			mn = d;
		}
		else
		{
			if (d < mn)
				mn = d;
			if (d > mx)
				mx = d;
		}
	}
	s /= n;
	cout << "sr ar: " << s << endl;
	cout << "min: " << mn << endl;
	cout << "max: " << mx<< endl;
	return 0;
}


// Lab 1 task 8

#include <iostream> 
#include <math.h>
using namespace std;


double get_dbl_Value()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{

		double z;
		cin >> z;

		// Проверка на предыдущее извлечение
		if (cin.fail() || cin.peek() != '\n') // если предыдущее извлечение оказалось неудачным(с буквами) или частично
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";

		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения


			return z;
		}
	}
}
int main()
{
	int n=10;
	double ar[10];
	double s=0;

	for (int i = 0; i < n; i++)
	{
		double d=get_dbl_Value();
		ar[i] = d;
	}
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			if (ar[i] < ar[i + 1])
				count++;
		}
		else if (i == n-1)
		{
			if (ar[i] < ar[i - 1])
				count++;
		}
		else
		{
			if (ar[i] < ar[i + 1] && ar[i] < ar[i - 1])
				count++;
		}
	}
	cout << "Quantity: " << count << endl;
	cout << endl;
	return 0;
}


// Lab 1 task 14

#include <iostream> 
#include <math.h>
using namespace std;

int getValue()
{
	while (true) // цикл продолжается до тех пор, пока пользователь не введет корректное значение
	{

		int z;
		cin >> z;

		// Проверка на предыдущее извлечение
		if (cin.fail() || cin.peek() != '\n') // если предыдущее извлечение оказалось неудачным(с буквами) или частично
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			cout << "Oops, that input is invalid.  Please try again.\n";

		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем лишние значения


			return z;
		}
	}
}
int main()
{
	cout << "Input n: " << endl;
	int n;
	while (true)
	{
		n = getValue();
		if (n < 0)
		{
			cout << "Try again!" << endl;
		}
		else break;
	}
	int s = 0, t = 0;
	
	while (n > 0)
	{
		t = n % 10;
		s += t;
		n /= 10;
	}
	cout << "Summ of digits: " << s << endl;
	return 0;
}
