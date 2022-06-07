#include<iostream>
using namespace std;

int A(int n)
{
	if(n==0)
		return 1;
	else{
		int tg = 0;
		for(int i = 0; i<n; i++)
			tg = tg + (n-i)*(n-i)*A(i);
		return tg;
	}
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