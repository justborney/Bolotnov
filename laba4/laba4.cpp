#include "interval.h"
#include <iomanip>
#include <iostream>
#include <cmath>
#define TYPE1 float
using namespace std;

int main()
{
	const int V=10.0;
	const int N=5;
	const double rad=0.01;

//	TYPE1 A1[N][N];
//	TYPE1 b1[N];
	interval A[N+1][N+1];
	interval b[N+1];
	interval s[N+1];


//	
	for (int i=1;i<=N;i++)
	{
			cout << fixed << setprecision(4);
		for (int j=1;j<=N;j++)
		{
			if (i==j)
			{
				A[i][j].left=31+V*sin(i)-rad;
				A[i][j].right=31+V*sin(i)+rad;	
			}
			else
			{
				A[i][j].left=0.01*V+log(i+j)-rad;
				A[i][j].right=0.01*V+log(i+j)+rad;
			}
		cout<<"["<<A[i][j].left<<"; "<<A[i][j].right<<"] \t";
		}
		//cout.setf(ios::scientific);	
		//cout<<"\t["<<b[i].left<<"; "<<b[i].right<<"]"<<endl;
		//cout<<12*V<<endl;
		b[i].left=(double)12.0*V/log(6.0+i)-rad;
		b[i].right=(double)12.0*V/log(6.0+i)+rad;
		cout<<"\t["<<b[i].left<<"; "<<b[i].right<<"]"<<endl;
		//cout<<"["<<b[i].left<<"; "<<b[i].right<<"]";
	} 
	cout << fixed << setprecision(3);
	for (int i=1;i<=N;i++)
	{
		s[i].left=0;
		s[i].right=0;
		for (int j=1;j<=N;j++)
		{

			s[i]=fold(s[i],multiply(A[i][j],b[j]));
		}
		cout << "s= "<< (s[i].left+s[i].right)/2<<";\t rad= "<<(s[i].right-s[i].left)/2<<';'<<endl;
	}
	
	return 0;
}
