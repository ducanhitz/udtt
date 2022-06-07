#include<iostream>
using namespace std;

int Acker(int m, int n)
{
	if(m==0)
		return (n+1);
	else if(n == 0)
		return Acker(m-1,1);
	else
		return Acker(m-1,Acker(m,n-1));
	
}
void hienthi(int n)
{
	for(int i = 0; i<n; i++)
		cout<<A(i)<<", ";
	cout<<endl;
}
int main()
{
	int n;
	cout<<"Nhap n: ";
	cin>>n;
	cout<<"Day A(n): ";
	hienthi(n);
	return 0;
}