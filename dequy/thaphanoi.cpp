#include <iostream>

using namespace std;

void thaphanoi(int n, char a, char b, char c)
{
	if(n==1)
	{
		cout << a << "---" << c << endl;
		return;
	}
	thaphanoi(n-1, a, c, b);
	thaphanoi(1, a, b, c);
	thaphanoi(n-1, b, a, c);
}

int main()
{
	char a='A', b='B', c='C';
	int n;
	cout << "Nhap n: ";
	cin >> n;
	thaphanoi(n, a, b, c);
}
