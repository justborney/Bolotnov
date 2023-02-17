#include "interval.h"
#include <iostream>

#define TYPE double

using namespace std;

int main()
{
	interval X,S;
	TYPE A,B,R;
	int N;
	do
	{
	cout<<"Enter the number of splits (N)> ";
	cin>>N;
	cout<<"Enter the left boundary of the segment (A)> ";
	cin>>A;
	cout<<"Enter the right boundary of the segment (B)> ";
	cin>>B;
	cout<<"Enter the radius of the interval (R)> ";
	cin>>R;
	if (A-R<-3)
	{
		cout<<"Erorr with negatave numbers (A-R<-3)"<<endl;
	}
	if (A>B)
	{
		cout<<"Error with interval (A>B)"<<endl;
	}
	}
	while ((A-R<-3) or (A>B));
	//vvesti obrabotku bolshogo radiusa
	double h=(double)(B-A)/(N-1);
	X.left=A-R;
	X.right=A+R;
	for (int i=0;i<N;i++)
	{
		S=fold(subtraction(7, multiply(4,X)), sqrtinter(fold(X,3)));
		cout<<"N="<<i<<" X[ "<<X.left<<" ; "<<X.right<<" ] \t--->\tY[ "<<S.left<<" ; "<<S.right<<" ]"<<endl;	
		X.left=X.left+h;
		X.right=X.right+h;	
	}
//	cout.precision(16);
//	cout<<(double)1/3;
	return 0;
}
