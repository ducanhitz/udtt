#include <iostream>

using namespace std;

int tong(int n)
{
	if(n>0)
	{
		return tong(n/10)+n%10;
	}
	return 0;
}

int main()
{
	int n;
	cout << "Nhap so nguyen duong n: ";
	cin >> n;
	cout << "Tong cac chu so cua n la: " << tong(n) << endl;
}
