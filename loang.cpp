#include<iostream>
using namespace std;

int a[5][6] = {(1,1,1,1,1) (1,1,1,1,1) (1,1,1,1,1) (1,1,1,1,1) (1,1,1,1,1) (1,1,1,1,1)};

void loang(int i, int j, int m, int n)
{
	flag[i][j] = true;
	if(a[i-1][j]) == a[i][j] && ! flag([i-1][j]))
		loang(i-1, j);
	if(a[i+1][j]) == a[i][j] && ! flag([i+1][j]))
		loang(i+1, j);
	if(a[i][j-1]) == a[i][j] && ! flag([i][j-1]))
		loang(i, j-1);
	if(a[i][j+1]) == a[i][j] && (! flag([i-1][j]))
		loang(i, j+1);
	
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