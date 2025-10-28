// WorkOnPara.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
void tryRead(int& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number\n" << std::endl;
		exit(0);
	}
}
void tryReadDouble(double& number)
{
	if (!(std::cin >> number))
	{
		std::cout << "Fail on reading the number\n" << std::endl;
		exit(0);
	}
}
bool isGreaterThan(int a, int b)
{
	if (a >= b)
		return true;
	return false;
}
int matrixLength(int** matrix, int maxNumberColumns)
{
	std::cout << "Input number of columns of matrix:\n";
	int numberCol;
	tryRead(numberCol);
	if (numberCol > maxNumberColumns || numberCol < 1)
	{
		std::cout << "Less than 100 (or maybe more than 0), please\n";
		exit(0);
	}
	return (numberCol);
}
int matrixWidth(int** matrix, int maxNumberLines)
{
	std::cout << "Input number of lines of matrix:\n";
	int numberLin;
	tryRead(numberLin);
	if (numberLin > maxNumberLines || numberLin < 1)
	{
		std::cout << "Less than 100 (or maybe more than 0), please\n";
		exit(0);
	}
	return (numberLin);
}
void swap(int& a, int& b)
{
	a += b;
	b = a - b;
	a = a - b;
}
void byHandMatrixFilling(int** matrix, int numberLin, int numberCol)
{
	int arNmbr;
	std::cout << "Enter:\n";
	for (int i = 0; i < numberLin; i++)
	{
		for (int j = 0; j < numberCol; j++)
		{
			tryRead(arNmbr);
			matrix[i][j] = arNmbr;
		}
	}
}
void randomMatrixFilling(int** matrix, int numberLin, int numberCol)
{
	int strt, fnsh;
	std::cout << "Enter an interval of randomization:\n";
	tryRead(strt);
	tryRead(fnsh);
	if (strt > fnsh)
		swap(strt, fnsh);
	std::mt19937 gen(45218965);
	for (int i = 0; i < numberLin; i++)
	{
		for (int j = 0; j < numberCol; j++)
		{
			std::uniform_int_distribution<int> dist(strt, fnsh);
			matrix[i][j] = dist(gen);
		}
	}
}
int orderToSort(int** matrix, int numberLin, int numberCol)
{
	std::cout << "In which order to sort the matrix (enter the number):\nIncreasingly(1)    Decreasingly(2)\n";
	int nmbrOrd;
	tryRead(nmbrOrd);
	if (nmbrOrd != 1 && nmbrOrd != 2)
	{
		std::cout << "Follow the rules!\n";
		exit(0);
	}
	return(nmbrOrd);
}
void yourMatrixIs(int** matrix, int numberLin, int numberCol)
{
	std::cout << "Your matrix:\n";
	for (int i = 0; i < numberLin; i++)
	{
		for (int j = 0; j < numberCol; j++)
		{
			std::cout << std::setw(3) << matrix[i][j];
		}
		std::cout << std::endl;
	}
}
void bubbleSort(int** matrix, int numberCol, int line)
{
	for (int i = 0; i < numberCol; i++)
		for (int column = 0; column < numberCol - i - 1; column++)
			if (isGreaterThan(matrix[line][column], matrix[line][column + 1]))
				std::swap(matrix[line][column], matrix[line][column + 1]);
}
int partition(int** matrix, int low, int high, int line)
{
	int pivot = matrix[line][high];
	int i = (low - 1);
	for (int j = low; j < high; j++)
		if (matrix[line][j] <= pivot)
		{
			i++;
			std::swap(matrix[line][i], matrix[line][j]);
		}
	std::swap(matrix[line][i + 1], matrix[line][high]);
	return (i + 1);
}
void quickSort(int** matrix, int low, int high, int line)
{
		if (low < high)
		{
			int pi = partition(matrix, low, high, line);

			quickSort(matrix, low, pi - 1, line);
			quickSort(matrix, pi + 1, high, line);
		}
}
void selectionSort(int** matrix, int numberCol, int line)
{
	
	int j = numberCol - 1;
	for (int i = 0; i < numberCol; i++)
	{
		int max = matrix[line][0];
		int colMax = 0;
		for (int column = 1; column < numberCol - i; column++)
			if (isGreaterThan(matrix[line][column], max))
			{
				colMax = column;
				max = matrix[line][column];
			}
		std::swap(matrix[line][colMax], matrix[line][j]);
		j--;
	}
}
void insertionSort(int** matrix, int numberCol, int line)
{
	int i, j;
	int x;
	for (i = 1; i < numberCol; ++i)
	{
		x = matrix[line][i];
		for (j = i - 1; j >= 0 && isGreaterThan(matrix[line][j], x); --j)
			matrix[line][j + 1] = matrix[line][j];
		matrix[line][j + 1] = x;
	}
}
void merge(int** matrix, int left, int mid, int right, int line)
{
	int n1 = mid - left + 1,
		n2 = right - mid;
	int* L = new int[n1];
	int* R = new int[n2];
	for (int i = 0; i < n1; ++i)
		L[i] = matrix[line][left + i];
	for (int j = 0; j < n2; ++j)
		R[j] = matrix[line][mid + j + 1];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2)
	{
		if (L[i] > R[j])
		{
			matrix[line][k] = R[j];
			++j;
		}
		else
		{
			matrix[line][k] = L[i];
			++i;
		}
		++k;
	}
	while (i < n1)
	{
		matrix[line][k] = L[i];
		++i;
		++k;
	}
	while (j < n2)
	{
		matrix[line][k] = R[j];
		++j;
		++k;
	}
	delete[] R;
	delete[] L;

}
void mergeSort(int** matrix, int left, int right, int line)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		mergeSort(matrix, left, mid, line);
		mergeSort(matrix, mid + 1, right, line);
		merge(matrix, left, mid, right, line);
	}
}
void countingSort(int** matrix, int numberCol, int line)
{
	int min = matrix[line][0], max = min;
	int* count = new int[numberCol] {};
	int* ar = new int[numberCol];
	for (int x = 0; x < numberCol - 1; ++x)
		for (int y = x + 1; y < numberCol; ++y)
		{
			if (matrix[line][x] > matrix[line][y])
				++count[x];
			else
				++count[y];
		}
	for (int i = 0; i < numberCol; ++i)
		ar[count[i]] = matrix[line][i];
	for (int i = 0; i < numberCol; ++i)
		matrix[line][i] = ar[i];
	delete[]ar;
	delete[]count;
}
void howToSort(int** matrix, int numberLin, int numberCol, int nmbrOrd)
{
	std::cout << "How to sort the matrix (enter the number):\nBubble sorting(1)\nQuicksort(2)\nSelection sorting(3)\nInsertion sorting(4)\nMerge sorting(5)\nCounting sorting(6)\n";
	int nmbrSort;
	tryRead(nmbrSort);
	switch (nmbrSort)
	{
	case 1:
		for (int line = 0; line < numberLin; line++)
			bubbleSort(matrix, numberCol, line);
		break;
	case 2:
		for (int line = 0; line < numberLin; line++)
			quickSort(matrix, 0, numberCol - 1, line);
		break;
	case 3:
		for (int line = 0; line < numberLin; line++)
			selectionSort(matrix, numberCol, line);
		break;
	case 4:
		for (int line = 0; line < numberLin; line++)
			insertionSort(matrix, numberCol, line);
			break;
	case 5:
		for (int line = 0; line < numberLin; line++)
			mergeSort(matrix, 0, numberCol - 1, line);
			break;
	case 6:
		for (int line = 0; line < numberLin; line++)
			countingSort(matrix, numberCol, line);
			break;
	default:
		std::cout << "Follow the rules!\n";
		exit(0);
	}

	if (nmbrOrd == 2)
		for (int line = 0; line < numberLin; line++)
			for (int i = 0; i < numberCol / 2; i++)
				std::swap(matrix[line][i], matrix[line][numberCol - i - 1]);
}
void fillMatrix(int** matrix, int numberLin, int numberCol)
{
	std::cout << "How to fill the matrix (enter the number):\nRandom(1)    By hand(2)\n";
	int nmbrFil;
	tryRead(nmbrFil);
	if (nmbrFil != 1 && nmbrFil != 2)
	{
		std::cout << "Follow the rules!\n";
		exit(0);
	}
	if (nmbrFil == 2)
		byHandMatrixFilling(matrix, numberLin, numberCol);
	else
		randomMatrixFilling(matrix, numberLin, numberCol);
}

int main()
{
	int maxNumberLines = 100, maxNumberColumns = 100;
	int** matrix;
	matrix = new int* [maxNumberLines];
	for (int i = 0; i < maxNumberLines; i++)
		matrix[i] = new int[maxNumberLines];

	int numberLin = matrixWidth(matrix, maxNumberLines);
	int numberCol = matrixLength(matrix, maxNumberColumns);

	fillMatrix(matrix, numberLin, numberCol);

	yourMatrixIs(matrix, numberLin, numberCol);

	int nmbrOrd = orderToSort(matrix, numberLin, numberCol);

	howToSort(matrix, numberLin, numberCol, nmbrOrd);
	yourMatrixIs(matrix, numberLin, numberCol);

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
