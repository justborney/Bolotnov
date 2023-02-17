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
const int Variant = 2;
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
	cout.precision(6);
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
	P[1].left = - C[1].left / (double) B[1].left;
	P[1].right =   - C[1].right / (double) B[1].right;
	Q[1].left =  D[1].left / (double) B[1].left;
	Q[1].right =  D[1].right / (double) B[1].right;
	
	for (int i = 2; i < N - 1; i++) 
	{
		P[i].left =  - (double) C[i].left / (double) (B[i].left + A[i].left * P[i - 1].left);
		P[i].right =  - (double) C[i].right / (double) (B[i].right + A[i].right * P[i - 1].right);
		Q[i].left = (double) (D[i].left - A[i].left * Q[i - 1].left) / (double) (B[i].left + A[i].left * P[i - 1].left);
		Q[i].right = (double) (D[i].right - A[i].right * Q[i - 1].right) / (double) (B[i].right + A[i].right * P[i - 1].right);
	}
}

/* Функция нахождения иксов */
void findX () 
{
	X[N - 1].left = (double)  (D[N - 1].left - A[N - 1].left * Q[N - 2].left) / (double) (B[N - 1].left + A[N - 1].left * P[N - 2].left);
	X[N - 1].right = (double)  (D[N - 1].right - A[N - 1].right * Q[N - 2].right) / (double) (B[N - 1].right + A[N - 1].right * P[N - 2].right);
	for (int i = N - 2; i > 0; i--) 
	{
		X[i].left = P[i].left * X[i + 1].left + Q[i].left;
		X[i].right = P[i].right * X[i + 1].right + Q[i].right;
	}
}

/* Функция нахождения вектора невязки и его нормы */
void findR () 
{
	r[1].left = D[1].left - B[1].left * X[1].left - C[1].left * X[2].left;
	r[1].right = D[1].right - B[1].right * X[1].right - C[1].right * X[2].right;
	for (int i = 2; i < N - 1; i++) 
	{
		r[i].left = D[i].left - A[i].left * X[i - 1].left - B[i].left * X[i].left - C[i].left * X[i + 1].left;
		r[i].right = D[i].right - A[i].right * X[i - 1].right - B[i].right * X[i].right - C[i].right * X[i + 1].right;
	}
	r[N - 1].left = D[N - 1].left - A[N - 1].left * X[N - 2].left - B[N - 1].left * X[N - 1].left;
	r[N - 1].right = D[N - 1].right - A[N - 1].right * X[N - 2].right - B[N - 1].right * X[N - 1].right;
	
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
