#include <iostream>
#include <random>
#include <iomanip>
//lab4 task5
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
void swap(int& a, int& b)
{
	a += b;
	b = b - a;
	a = b - a;
}
void byHandMatrixFilling(int** matrix, int numberLines)
{
	int arNmbr;
	std::cout << "Enter:\n";
	for (int i = 0; i < numberLines; i++)
	{
		for (int j = 0; j < numberLines; j++)
		{
			tryRead(arNmbr);
			matrix[i][j] = arNmbr;
		}
	}
}
void randomMatrixFilling(int** matrix, int numberLines)
{
	int strt, fnsh;
	std::cout << "Enter an interval of randomization:\n";
	tryRead(strt);
	tryRead(fnsh);
	if (strt > fnsh)
		swap(strt, fnsh);
	std::mt19937 gen(45218965);
	for (int i = 0; i < numberLines; i++)
	{
		for (int j = 0; j < numberLines; j++)
		{
			std::uniform_int_distribution<int> dist(strt, fnsh);
			matrix[i][j] = dist(gen);
		}
	}
}
void fillMatrix(int** matrix, int numberLines)
{
	std::cout << "How to fill the matrix (enter the number):\nRandom(1)    By hand(2)\n";
	int nmbr;
	tryRead(nmbr);
	if (nmbr != 1 && nmbr != 2)
	{
		std::cout << "Follow the rules!\n";
		exit(0);
	}
	if (nmbr == 2)
		byHandMatrixFilling(matrix, numberLines);
	else
		randomMatrixFilling(matrix, numberLines);
}

void swapNearbyMatrixLineElements(int** matrix, int line, int j)
{
	matrix[line][j - 1] += matrix[line][j];
	matrix[line][j] = matrix[line][j - 1] - matrix[line][j];
	matrix[line][j - 1] = matrix[line][j - 1] - matrix[line][j];
}
void swapNearbyMatrixColumnElements(int** matrix, int line, int j)
{
	matrix[line-1][j] += matrix[line][j];
	matrix[line][j] = matrix[line-1][j] - matrix[line][j];
	matrix[line - 1][j] = matrix[line - 1][j] - matrix[line][j];
}

void YourMatrixIs(int** matrix, int numberLines)
{
	std::cout << "Your matrix:\n";
	for (int i = 0; i < numberLines; i++)
	{
		for (int j = 0; j < numberLines; j++)
		{
			std::cout <<std::setw(3)<< matrix[i][j];
		}
		std::cout << std::endl;
	}
}
void matrixLineSorting(int** matrix, int numberLines)
{
	for (int line = 0; line < numberLines; line++)
		for (int j = 0; j < numberLines; j++)
			for (int column = 1; column < numberLines; column++)
				if (matrix[line][column - 1] < matrix[line][column])
					swapNearbyMatrixLineElements(matrix, line, column);
}
void matrixColumnSorting(int** matrix, int numberLines)
{
	for (int column = 0; column < numberLines; column++)
		for (int i = 0; i < numberLines; i++)
			for (int line = 1; line < numberLines; line++)
				if (matrix[line - 1][column] < matrix[line][column])
					swapNearbyMatrixColumnElements(matrix, line, column);
}

int main()
{
	int maxNumberLines = 100;
	int** matrix;
	matrix = new int* [maxNumberLines];
	for (int i = 0; i <  maxNumberLines; i++)
		matrix[i] = new int[maxNumberLines];

	std::cout << "The matrix is square. Input number of lines/columns of matrix:\n";
	int numberLines;
	tryRead(numberLines);
	if (numberLines > maxNumberLines || numberLines < 1)
	{
		std::cout << "Less than 100 (or maybe more than 0), please\n";
		exit(0);
	}

	fillMatrix(matrix, numberLines);

	YourMatrixIs(matrix, numberLines);

	std::cout << "Largest element in lower right triangle of the matrix:\n";
	int maxElement = matrix[0][numberLines - 1];
	int i = 1, j = numberLines - 1;
	while (i < numberLines)
	{
		while (j >= numberLines - i - 1)
		{
			if (matrix[i][j] > maxElement)
				maxElement = matrix[i][j];
			j--;
		}
		j = numberLines - 1;
		i++;
	}
	std::cout << maxElement << std::endl << std::endl;
	
	matrixLineSorting(matrix, numberLines);

	matrixColumnSorting(matrix, numberLines);

	YourMatrixIs(matrix, numberLines);

	for (int i = 0; i < numberLines; i++)
		delete[] matrix[i];
	delete[]matrix;

	return 0;
}