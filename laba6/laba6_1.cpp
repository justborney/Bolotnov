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
const int N = 2000001;
const int Variant = 2.0;
TYPE1 A[N]; 
TYPE1 B[N]; 
TYPE1 C[N]; 
TYPE1 D[N]; 
TYPE1 P[N]; 
TYPE1 Q[N]; 
TYPE1 X[N]; 
TYPE1 r[N]; 

double rad = 0.01;
//unsigned int start, end;
void print ()
{
	cout.precision(8);
	//cout.setf (ios::showpos);
	cout<<"X1"<<"\t\t"<<"med"<<"\t\t"<<"X2"<<"\t\t"<<"r1"<<"\t\t"<<"r2"<<endl;
	for (int i = 1000001; i < 1000006; i++) 
	{
		cout<<X[i].left<<'\t'<< (double)(X[i].left+X[i].right)/2.0<<'\t' <<X[i].right<<'\t'<<r[i].left<<'\t'<<r[i].right<<endl;
	}
	
}

void printArr () 
{
	cout.precision(2);
	cout.setf (ios::scientific);
	cout<<"A"<<"\t\t\t"<<"B"<<"\t\t\t"<<"C"<<"\t\t\t"<<"D"<<"\t\t\t"<<"alfa"<<"\t\t\t"<<"beta"<<endl;
	for (int i = 1;i<11;i++)
	{
		cout<<(double)(A[i].left+A[i].right)/2.0<<"\t\t"<<(double)(B[i].left+B[i].right)/2.0<<"\t\t"<<(double)(C[i].left+C[i].right)/2.0<<"\t\t"<<(double)(D[i].left+D[i].right)/2.0<<"\t\t"<<(double)(P[i].left+P[i].right)/2.0<<"\t\t"<<(double)(Q[i].left+Q[i].right)/2.0<<endl;
	}
	
}


/* Инициализация */
void initArr () 
{
	for (int i = 1; i < N; i++) 
	{
		if (i >= 2) 
		{
			A[i].left = (double)0.3 *sin( (double) i) / (double) Variant - rad;
			A[i].right = (double)0.3 *sin( (double) i) / (double) Variant + rad;
		}
		if (i < N - 1) 
		{
			C[i].left = (double)0.4 * cos( (double) i) / (double) Variant - rad;
			C[i].right = (double)0.4 * cos( (double) i) / (double) Variant + rad;
		}
		B[i].left = (double) 10.0 * Variant + i / (double) Variant - rad; // Берем со знаком минус
		B[i].right = (double) 10.0 * Variant + i / (double) Variant +rad;
		D[i].left = 1.3 + (double) i / (double) Variant - rad;
		D[i].right = 1.3 + (double) i / (double) Variant + rad;
	}
}

/* Нахождение P и Q прогоночных коэфф-в */
void findPQ () 
{
	P[1] = divide(multiply(-1, C[1]),  B[1]);

	Q[1] =  divide(D[1], B[1]);

	
	for (int i = 2; i < N - 1; i++) 
	{
		P[i] =  divide(multiply(-1, C[i]), fold(B[i], multiply(A[i], P[i - 1])));
		Q[i]= divide( subtraction(D[i], multiply(A[i], Q[i - 1])),  fold(B[i], multiply(A[i], P[i - 1])));
	}
}

/* Функция нахождения иксов */
void findX () 
{
	X[N - 1] = divide( subtraction(D[N - 1], multiply(A[N - 1], Q[N - 2])), fold(B[N - 1], multiply(A[N - 1], P[N - 2])));
	for (int i = N - 2; i > 0; i--) 
	{
		X[i] = fold(multiply(P[i], X[i + 1]), Q[i]);
	}
}

/* Функция нахождения вектора невязки и его нормы */
void findR () 
{
	r[1] = subtraction(subtraction(D[1],multiply(B[1], X[1])), multiply(C[1], X[2]));
	for (int i = 2; i < N - 1; i++) 
	{
		r[i] = subtraction(subtraction(subtraction(D[i], multiply(A[i], X[i - 1])), multiply(B[i], X[i])), multiply(C[i], X[i + 1]));
	}
	r[N - 1] = subtraction(subtraction(D[N - 1], multiply(A[N - 1], X[N - 2])), multiply(B[N - 1], X[N - 1]));

//	for (int k = 1; k < N; k++) {
//		normR += abs(r[k]);
//	}
}

int main()
{
	
	//start=clock();
	initArr();
	findPQ();
	findX();
	findR();
	//end=clock();
	if (N<20)
	{
		printArr ();
	}
	print();
	//printf("Time = %.0f\n", difftime(end, start));
	return 0;
}
