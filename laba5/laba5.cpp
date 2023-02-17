#include "interval.h"
#include <iostream>
#include <cmath>
#define TYPE1 float
using namespace std;

int main()
{
	const int V=10;
	const int N=10000;
//	cout<<"Vvedite N> "<<endl;
//	cin>>N;
	const double rad=0.001;
//	TYPE1 A1[N][N];
//	TYPE1 b1[N];
	double buf;
	interval A[N+1];
	interval s1,s2;
	s1.left=0;
	s1.right=0;
	s2.left=0;
	s2.right=0;	
	
	for (int i=1;i<=N;i++)
	{
		A[i].left=sin(V+i)-rad;
		A[i].right=sin(V+i)+rad;
//		cout<<"["<<A[i].left<<";"<<A[i].right<<"] ";	
	} 
	
	for (int i=1;i<=N;i++)
	{
		s1=fold(s1,A[i]);
	}
//	cout<<"A[1]=["<<A[1].left<<";\t"<<A[1].right<<"];A[n]=["<<A[N].left<<";\t"<<A[N].right<<"]; "<<endl;
	for (int i=1;i<=N-1;i++)
	{
		for (int j=i+1;j<=N;j++)
		{
			if (A[i].left>A[j].left)
			{
				buf=A[i].left+rad;
				A[i].left=A[j].left;
				A[i].right=A[j].right;
				A[j].left=buf-rad;
				A[j].right=buf+rad;
			}
		}
	}
	cout<<endl;
	//cout<<"A[1]=["<<A[1].left<<";\t"<<A[1].right<<"];A[n]=["<<A[N].left<<";\t"<<A[N].right<<"]; "<<endl;	
	for (int i=1;i<=N;i++)
	{
//		cout<<"["<<A[i].left<<";"<<A[i].right<<"] ";	
		s2=fold(s2,A[i]);
	}
	
	cout.precision(16);	
	cout<<endl;
	cout<<"s1=["<<s1.left<<";\t"<<s1.right<<"];\r\ns2=["<<s2.left<<";\t"<<s2.right<<"]; "<<endl;
	return 0;
}
