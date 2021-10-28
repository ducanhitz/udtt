#include <iostream>

using namespace std;

int daonguoc(int n, int sdn)
{
	if (n == 0)
		return sdn;
	else
	{
		sdn = sdn*10 + n%10;
		return daonguoc(n/10, sdn);
	}
}

int main()
{
	int n, sdn;
	cout << "Nhap so nguyen duong n: ";
	cin >> n;
	cout << "So dao nguoc cua n la: " << daonguoc(n, sdn) << endl;
}
