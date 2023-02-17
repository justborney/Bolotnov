#include "interval.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <math.h>
#include <limits>
#include <cstdio>
//#define TYPE1 interval
#define TYPE1 double
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
				A[i][j] = -1 * fabs(0.01 * V + sin(i - j)); 
			} 
			else
			{
				A[i][i] = fabs(99.0 + sin(i) / V);				
			}  
			SaveA[i][j] = A[i][j];
		}
		B[i] = 2.0 * cos(i + V);
		SaveB[i] = B[i];
	}
}

void findIS(int k)
{
	for (int i = 1; i < N; i++)
	{
		if (i < k)
		{
			S[i] = 0.0;
		}
		else
		{
			S[i] = A[i][k];
		}
				
		if (i == k)
		{
			I[i] = 1.0;
		}
		else
		{
			I[i] = 0.0;
		}
	}	
}

double skalar(TYPE1 *A, TYPE1 *B)
{
	TYPE1 sum = 0.0;
	for (int i = 1; i < N; i++)
	{
		sum += A[i] * B[i];
	}
	return sum;
}

double argVec(TYPE1 *A, TYPE1 *B)
{
//	TYPE1 arg = 0.0;
	TYPE1 divA = 0.0;
	TYPE1 divB = 0.0;
	for (int i = 1; i < N; i++)
	{
		divA += A[i] * A[i];
		divB += B[i] * B[i];
	}
	return acos(skalar(A,B) / sqrt(divA * divB));
}

void HouseHolder()
{
	TYPE1 alpha = sqrt(skalar(S,S));
	TYPE1 ro = sqrt(2.0 * alpha * alpha + 2.0 * alpha * skalar(S,I));
	cout<<"alpha: "<<alpha<<" ro: "<<ro<<endl;
	cout<<" (S,I): "<<skalar(S,I)<<endl;
	if ((argVec(S,I) - M_PI) < 0.1)
	{
		alpha *= -1;
		cout<<"!!!!!!!!!!!!!!!!!!!!"<<endl;
	}
	for (int i = 1; i < N; i++)
	{
		W[i] = (1.0 / ro) * (S[i] - alpha * I[i]);
		cout<<"W: "<<W[i]<<" ";
	} 
	cout<<endl;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			if (i == j)
			{
				U[i][j] = 1.0 - 2.0 * W[i] * W[j];
			}
			else
			{
				U[i][j] = - 2.0 * W[i] * W[j];
			}
			cout<<"U: "<<U[i][j]<<" ";
			bufA[i][j] = 0.0;			
		}	
		bufB[i] = 0.0;			
		cout<<endl;
	}

	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < N; j++)
		{
			TYPE1 sumA = 0.0;
			TYPE1 sumB = 0.0;

			for (int k = 1; k < N; k++)
			{	
				sumA += U[i][k] * A[k][j];
				sumB += U[i][k] * B[k];//////
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
		TYPE1 sum = 0.0;
		for (int j = 1; j < N; j++)
			sum += SaveA[i][j] * X[j];
		r[i] = SaveB[i] - sum;
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
			file<<"["<<A[i][j]<<"] \t" <<" ";
		}
		file.precision(4);
		file<<" \t"<<"B["<<B[i]<<"] " <<endl;
	}
	file<<endl;
}

void printXr()
{
	for (int i = 1; i < N; i++)
	{
		file.precision(10);
		file<<"X["<<X[i]<<"]";
		file.precision(6);
		file<<"\t r["<<r[i]<<"] " <<endl;
	}
}

int main()
{
	initArr();
	printAB();
	for (int k = 1; k < N; k++)
	{
		findIS(k);
		for (int i = 1; i < N; i++)
		{
			cout<<"S: "<<S[i]<<"; I: "<<I[i]<<endl;
		}
		HouseHolder();
		file<<k<<endl;
		printAB();
	}
	X[N - 1] = B[N - 1] / A[N - 1][N - 1];
	for (int i = N - 2; i >= 1; i--)
	{
		for (int j = i + 1; j < N; j++)
			B[i] = B[i] - A[i][j] * X[j];
		X[i] = B[i] / A[i][i];		
	}
	printAB();
	nevyazka();
	printXr();
	return 0;
}
