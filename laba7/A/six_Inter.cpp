#include <iostream>
#include <fstream>
#include <cmath>
#include "interval.hpp"

using namespace std;

const int N = 8; /* Матрица инервалов 7*7, т.к. отсчет с 1 */
const double delta   = 0.01, /* радиус для интервалов */
	         VARIANT = 22.0;

Interval<double> A[N][N];
Interval<double> SaveA[N][N]; /* Сохраняет А, чтобы считать невязки */
Interval<double> B[N];
Interval<double> SaveB[N];
Interval<double> X[N]; // Вектор решений
Interval<double> r[N]; // Вектор невязок
ofstream file("./out_six.txt");

/* 
 * Инициализирует матрицу, вектор 
*/
void initialize ()
{
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (i != j)
			{
				double calcA = 0.01 * VARIANT + sin(i - j);
				A[i][j] = Interval<double>(calcA - delta, calcA + delta);
				SaveA[i][j] = A[i][j];
			}
		}

		double calcDiag = 31 + sin(i) / VARIANT,
			   calcB    = 10 * cos(i + VARIANT);
		A[i][i] = Interval<double>(calcDiag - delta, calcDiag + delta);
		B[i]    = Interval<double>(calcB - delta, calcB + delta);
		SaveA[i][i] = A[i][i];
		SaveB[i]    = B[i];
	}
}

/* Меняет местами строку под номером
 * currIn с stIn строкой
 * Также меняет свободные члены из
 * массива B[]
 * */
void swapRow (int stIn, int currIn)
{
	for (int j = 1; j < N; j++)
	{
		swap(&A[stIn][j], &A[currIn][j]);
	}
	swap(&B[stIn], &B[currIn]);
}

/* Меняет currIn столбец с
 * stIn столбцом
 * */
void swapCol (int stIn, int currIn)
{
	for (int i = 1; i < N; i++)
	{
		swap(&A[i][stIn], &A[i][currIn]);
	}
}

/* Функция, к-я ищет максимальный
 * элемент по заданному столбцу в матрице.
 * Не возвращает значений, а исп-ет
 * указатель для возвращения
 * индекса макс. элемента
*/
void findingMax (int colInd, int* i)
{
	double max = -1;
	for (int k = colInd; k < N; k++)
	{
		/* По модулю (интервальный) больше */
		if (iabs(A[k][colInd]) > max)
		{
			max = iabs(A[k][colInd]);
			*i = k;
			file << "R = " << *i << " C = " << colInd << " max = " << max << endl;
		}
	}
}

/* Делит в строке indRow к-й элемент
 * на div, также делит соот-й элемент
 * из массива свобод. членов B[]
*/
void divideRow (Interval<double> div, int indRow)
{
	for (int j = 1; j < N; j++)
	{
		A[indRow][j] = A[indRow][j] / div;
	}
	B[indRow] = B[indRow] / div;
}

/* Вычитает к-й элем. строки indF(irst)
 * на к-й элем. строки indS(econd) домноженный на mult
 * Незабывем и о свобод. членах
*/
void subtRow (int indF, int indS, Interval<double> mult)
{
	for (int j = 1; j < N; j++)
	{
		A[indF][j] = A[indF][j] - mult * A[indS][j];
	}
	B[indF] = B[indF] - mult * B[indS];
}

/* Выводит матрицу и
 * вектор свободных членов
*/
void print (void)
{
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			file << A[i][j] << " ";
		}
		file << B[i] << endl;
	}
}

int main ()
{
	int maxRow = 1;

	cout.setf(ios::scientific);

	/* Инициализация */
	initialize();
	print();

	/* Прямой ход */
	for (int i = 1; i < N; i++)
	{
		findingMax(i, &maxRow);
		swapRow(i, maxRow);
		divideRow(A[i][i], i);

		for (int j = i + 1; j < N; j++)
		{
			subtRow(j, i, A[j][i]);
		}
	}
	print();

	/* Обратный ход */
	X[N - 1] = B[N - 1];
	for (int i = N - 2; i >= 1; i--)
	{
		X[i] = B[i];
		for (int j = i + 1; j < N; j++)
		{
			X[i] = X[i] - A[i][j] * X[j];
		}
	}


	for (int k = 1; k < N; k++)
	{
		file << "X[" << k << "] = " << X[k] << endl;
	}

	/* Считаем интервальные невязки */
	for (int i = 1; i < N; i++)
	{
		Interval<double> sum(0.0, 0.0);

		for (int j = 1; j < N; j++)
		{
			sum = sum + SaveA[i][j] * X[j];
		}
		r[i] = SaveB[i] - sum;
	}

	file << "============= R =============" << endl;
	for (int i = 1; i < N; i++)
	{
		file << "R[" << i << "] = " << r[i] << endl;
	}

	file.close();
	return 0;
}
