#include "interval.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <math.h>
#include <limits>
#include <cstdio>
#define TYPE1 interval
//#define TYPE1 double
using namespace std;

ofstream file("./result_householder.txt");
const int N = 8;
const int V = 10;
TYPE1 A[N][N];
TYPE1 B[N];
TYPE1 X[N];
TYPE1 r[N];
TYPE1 SaveA[N][N];
TYPE1 SaveB[N];
TYPE1 S[N];
TYPE1 I[N];
TYPE1 W[N];
TYPE1 U[N][N];
TYPE1 bufA[N][N];
TYPE1 bufB[N];
double rad = 0.0001;

void initArr()
{
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (i != j)
			{
				A[i][j].left = -1 * fabs(0.01 * V + sin(i - j)) - rad; 
				A[i][j].right = -1 * fabs(0.01 * V + sin(i - j)) + rad;
			} 
			else
			{
				A[i][i].left = fabs(99.0 + sin(i) / V) - rad;
				A[i][i].right = fabs(99.0 + sin(i) / V) + rad;					
			}  
			SaveA[i][j] = A[i][j];
		}
		B[i].left = 2.0 * cos(i + V) - rad;
		B[i].right = 2.0 * cos(i + V) + rad;
		SaveB[i] = B[i];
	}
}

void findIS(int k)
{
	for (int i = 1; i < N; i++)
	{
		if (i < k)
		{
			S[i].left = 0.0;
			S[i].right = 0.0;
		}
		else
		{
			S[i] = A[i][k];
		}
//		S[i] = A[k][i];
		if (i == k)
		{
			I[i].left = 1.0;
			I[i].right = 1.0;
		}
		else
		{
			I[i].left = 0.0;
			I[i].right = 0.0;
		}
	}
}

TYPE1 skalar(TYPE1 *A, TYPE1 *B)
{
	TYPE1 sum;
	sum.left = 0.0;
	sum.right = 0.0;
	for (int i = 1; i < N; i++)
	{
		sum = fold(sum, multiply(A[i], B[i]));
	}
	return sum;
}

double argVec(TYPE1 *A, TYPE1 *B)
{
//	TYPE1 arg = 0.0;
	TYPE1 divA;
	divA.left = 0.0;
	divA.right = 0.0;
	TYPE1 divB;
	divB.left = 0.0;
	divB.right = 0.0;
	for (int i = 1; i < N; i++)
	{
		divA = fold(divA, multiply(A[i], A[i]));
		divB = fold(divB, multiply(B[i], B[i]));
	}
	return acos(modul(divide(skalar(A,B), multiply(divA, divB))));
}

void HouseHolder()
{
	TYPE1 alpha = sqrtinter(skalar(S,S));
	TYPE1 ro = sqrtinter(fold(multiply(multiply(2, alpha), alpha), multiply(multiply(2, alpha), skalar(S,I))));
	if ((argVec(S,I) - M_PI) < 0.1)
	{
		alpha = multiply(-1.0, alpha);
	}
	for (int i = 1; i < N; i++)
	{
//		W[i] = multiply(divide(1.0, ro), subtraction(S[i], multiply(alpha, I[i])));
		W[i] = divide(subtraction(S[i], multiply(alpha, I[i])), ro);
		
//		cout<<"W: "<<W[i]<<" ";
	} 
//	cout<<endl;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (i == j)
			{
				U[i][j] = subtraction(1.0, multiply(multiply(2.0, W[i]), W[j]));
			}
			else
			{
				U[i][j] = multiply(multiply(- 2.0, W[i]), W[j]);
			}
//			cout<<"U: "<<U[i][j]<<" ";
//			bufA[i][j].left = 0.0;
//			bufA[i][j].right = 0.0;			
		}	
//		bufB[i] = 0.0;			
//		cout<<endl;
	}

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			TYPE1 sumA;
			sumA.left = 0.0;
			sumA.right = 0.0;
			TYPE1 sumB;
			sumB.left = 0.0;
			sumB.right = 0.0;
			
			for (int k = 1; k < N; k++)
			{	
				sumA = fold(sumA, multiply(U[i][k], A[k][j])); 
				sumB = fold(sumB, multiply(U[i][k], B[k])); ///////////////////////sumB += U[i][k] * B[k];
			}
//			cout<<"sumA: "<<sumA<<endl;
			bufA[i][j] = sumA;
//			cout<<"bufA:"<<bufA[i][j]<<" ";	
			bufB[i] = sumB;
		}
	}
//	A = bufA;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			A[i][j] = bufA[i][j];
			
		}
		B[i] = bufB[i];
	}
}

void nevyazka()
{
	for (int i = 1; i < N; i++)
	{
		TYPE1 sum;
		sum.left = 0.0;
		sum.right = 0.0;
		for (int j = 1; j < N; j++)
			sum = fold(sum, multiply(SaveA[i][j], X[j]));
		r[i] = subtraction(SaveB[i], sum);
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
		file.setf(ios::fixed);
		file<<"X["<<X[i].left<<", "<<X[i].right<<"]";
		file.precision(6);
//		file.setf(ios::scientific);
		file<<"\t r["<<r[i].left<<", "<<r[i].right<<"] " <<endl;
	}
}
int main()
{
	initArr();
	printAB();
	for (int k = 1; k < N; k++)
	{
		findIS(k);
//		for (int i = 1; i < N; i++)
//		{
//			cout<<"S: "<<S[i]<<"; I: "<<I[i]<<endl;
//		}
		HouseHolder();
		file<<k<<endl;
		printAB();
	}
	X[N - 1] = divide(B[N - 1], A[N - 1][N - 1]);
	for (int i = N - 2; i >= 1; i--)
	{
		for (int j = i + 1; j < N; j++)
			B[i] = subtraction(B[i], multiply(A[i][j], X[j]));
		X[i] = divide(B[i], A[i][i]);		
	}
//	printAB();
//	gauss();
//	printAB();
	nevyazka();
	printXr();
	for (int i = 1; i < N; i++)
	{
		cout.precision(10);
		cout.setf(ios::fixed);
		cout<<"X["<<X[i].left<<", "<<X[i].right<<"]";
		cout.precision(6);
//		file.setf(ios::scientific);
		cout<<"\t r["<<r[i].left<<", "<<r[i].right<<"] " <<endl;
	}
	return 0;
}
