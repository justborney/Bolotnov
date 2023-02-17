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
//	file.setf(ios::fixed);
//	file.precision(6);
//	for (int i = 1; i < N; i++)
//	{
//		file.precision(8);
//		for (int j = 1; j < N; j++)
//		{
//			file<<"["<<A[i][j].left<<", "<<A[i][j].right<<"] \t" <<" ";
//		}
//		file.precision(4);
//		file<<" \t"<<"B["<<B[i].left<<", "<<B[i].right<<"] " <<endl;
//	}
//	file<<endl;
	for (int i = 1; i < N; i++)
	{
		file.precision(10);
		file<<"X["<<X[i].left<<", "<<X[i].right<<"]";
		file.precision(6);
		file<<"\t r["<<r[i].left<<", "<<r[i].right<<"] " <<endl;
	}
}

void gauss() 
{
  	double max;
  	int k, index;
  	k = 1;
	while (k < N) 
  	{
    // Поиск строки с максимальным a[i][k]
    max = fabs(modul(A[k][k]));
    index = k;
    for (int i = k; i < N; i++) 
    {
    	if (fabs(modul(A[i][k])) > max)
    	{
        	max = fabs(modul(A[i][k]));
        	index = i;
    	}
    }
    file<<A[index][k].left<<" , "<<A[index][k].right<<endl;
    // Перестановка строк
    for (int j = 1; j < N; j++) 
    {
      interval temp = A[k][j];
      A[k][j] = A[index][j];
      A[index][j] = temp;
    }
    interval temp = B[k];
    B[k] = B[index];
    B[index] = temp;
    // Нормализация уравнений
    for (int i = k; i < N; i++) 
    {
      	interval temp = A[i][k];
      	for (int j = 1; j < N; j++) 
      	{
        	A[i][j] = divide(A[i][j], temp);
	  	}	
      	B[i] = divide(B[i], temp);
      	if (i == k)  continue; // уравнение не вычитать само из себя
      	for (int j = 1; j < N; j++)
      	{
        	A[i][j] = subtraction(A[i][j], A[k][j]);
        }
      	B[i] = subtraction(B[i], B[k]);
    }
    file<<k<<endl;
    printAB();
//	cout<<k<<endl; 
	k++;
	}
//	cout<<k<<endl;
  // обратная подстановка
	X[N - 1] = B[N - 1];
	for (k = N - 2; k >= 1; k--)
	{
    	X[k] = B[k];
    	for (int i = 1; i < k; i++)
    	X[i] = subtraction(X[i], multiply(A[i][k], X[k]));
  	}
  
//	for (int i = N - 2; i >= 1; i--)	
//	{
//		X[i] = B[i];
//		for (int j = i + 1; j < N; j++)
////			X[i] = X[i] - A[i][j] * X[j];
//			X[i] = subtraction(X[i], multiply(A[i][j], X[j]));
//	}
}

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
