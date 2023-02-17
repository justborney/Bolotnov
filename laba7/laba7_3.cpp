#include "interval.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <math.h>
#include <limits>
#include <cstdio>
#define TYPE1 interval

using namespace std;
const int N = 8;
const int Variant = 10;
TYPE1 A[N][N]; 
TYPE1 B[N]; 
TYPE1 X[N]; 
TYPE1 r[N]; 
TYPE1 SaveA[N][N];
TYPE1 SaveB[N];
interval sum;
double rad = 0.01;
ofstream file("./result_gauss.txt");
/* Инициализация */
void initArr () 
{
	for (int i = 1; i < N; i++) 
	{
		for (int j = 1; j < N; j++)
		{
			if (i != j)
			{
				A[i][j].left = 0.01 * Variant + sin(i - j) - rad;
				A[i][j].right = 0.01 * Variant + sin(i - j) + rad;
				SaveA[i][j] = A[i][j];
			}
			else
			{
				A[i][i].left = 31.0 + sin(i) / (double) Variant - rad;
				A[i][i].right = 31.0 + sin(i) / (double) Variant + rad;
				SaveA[i][i] = A[i][i];
			}
		}
		B[i].left = 10.0 * cos(i + Variant) - rad;
		B[i].right = 10.0 * cos(i + Variant) + rad;
		SaveB[i] = B[i];
	}
}
void printAB()
{
	file.setf(ios::fixed);
	file.precision(6);
	for (int i = 1; i < N; i++)
	{
		file.precision(8);
		for (int j = 1; j < N; j++)
		{
			file<<"["<<A[i][j].left<<", "<<A[i][j].right<<"] \t" <<" ";
		}
		file.precision(4);
		file<<" \t"<<"B["<<B[i].left<<", "<<B[i].right<<"] " <<endl;
	}
	file<<endl;
}
void printXr()
{
	for (int i = 1; i < N; i++)
	{
		file.precision(10);
		file<<"X["<<X[i].left<<", "<<X[i].right<<"]";
		file.precision(6);
		file<<"\t r["<<r[i].left<<", "<<r[i].right<<"] " <<endl;
	}
}

void swapRow (int stIn, int currIn)
{
	for (int j = 1; j < N; j++)
	{
		interval temp = A[stIn][j];
		A[stIn][j] = A[currIn][j];
		A[currIn][j] = temp;
	}
	interval temp = B[stIn];
	B[stIn] = B[currIn];
	B[currIn] = temp;
}

void findingMax (int colInd, int* index)
{
	double max = modul(A[colInd][colInd]);
	for (int k = colInd; k < N; k++)
		// По модулю больше
		if (modul(A[k][colInd]) > max)
		{
			max = modul(A[k][colInd]);
			*index = k;
		}
}

void divideRow (interval div, int indRow)
{
	file<<div.left<<" , "<<div.right<<endl;/////////////////////////////
	for (int j = 1; j < N; j++)
		A[indRow][j] = divide(A[indRow][j], div);
	B[indRow] = divide(B[indRow], div);
}

void subtRow (int indF, int indS, interval mult)
{
	for (int j = 1; j < N; j++)
	{
		A[indF][j] = subtraction(A[indF][j], multiply(mult, A[indS][j]));
	}
	B[indF] = subtraction(B[indF], multiply(mult, B[indS]));
}
	
void gauss()
{
	int maxRow = 1;
	/* Прямой ход*/
	for (int i = 1; i < N; i++)
	{
		findingMax(i, &maxRow);
		swapRow(i, maxRow);
		divideRow(A[i][i], i);
		for (int j = i + 1; j < N; j++)
			subtRow(j, i, A[j][i]);	
		printAB();	
	}

	/* Обратный ход */
	X[N - 1] = B[N - 1];
	for (int i = N - 2; i >= 1; i--)
	{
		X[i] = B[i];
		for (int j = i + 1; j < N; j++)
			X[i] = subtraction(X[i], multiply(A[i][j], X[j]));
	}
}


//	cout<<k<<endl;
  // обратная подстановка
//	X[N - 1] = B[N - 1];
//	for (int k = N - 2; k >= 1; k--)
//	{
//    	X[k] = B[k];
//    	for (int i = 1; i < k; i++)
//    	X[i] = subtraction(X[i], multiply(A[i][k], X[k]));
  	
  
//	for (int i = N - 2; i >= 1; i--)	
//	{
//		X[i] = B[i];
//		for (int j = i + 1; j < N; j++)
////			X[i] = X[i] - A[i][j] * X[j];
//			X[i] = subtraction(X[i], multiply(A[i][j], X[j]));
//	}
//}

void nevyazka()
{
	for (int i = 1; i < N; i++)
	{
		sum.left = 0.0;
		sum.right = 0.0;
		for (int j = 1; j < N; j++)
			sum = fold(sum, multiply(SaveA[i][j], X[j]));
		r[i] = subtraction(SaveB[i], sum);

//		normR += fabs(r[i]);
	}
}

int main()
{
	initArr();
	printAB();
	gauss();
//	X[1].left =  0.00766;
//	X[1].right = 0.00766;
//	X[2].left =  0.27;
//	X[2].right = 0.27;
	printAB();
	nevyazka();
	printXr();
	return 0;
}
