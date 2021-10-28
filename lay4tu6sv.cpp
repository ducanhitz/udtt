#include <iostream>

using namespace std;

string str[6] = {"Tam", "Toan", "Trang", "Cong", "Trung", "Tu"};

void next_config(int x[], int k, int i)
{
	x[i] += 1;
	i++;
	while (i <= k)
	{
		x[i] = x[i-1] + 1;
		i++;
	}
}

void view_config(int x[], int k)
{
	for (int i = 1; i <= k; i++)
	{
		cout << str[x[i]-1];
	}
	cout << endl;
}
void listing_config(int k, int n)
{
	int i;
	int x[k + 1];
	for (i = 1; i <= k; i++)
	{
		x[i] = i;
	}
	do
	{
		view_config(x, k);
		while (i > 0 && x[i] == (n-k+i))
		{
			i--;
		}
		if (i > 0)
		{
			next_config(x, k, i);
		}
	}
	while (i > 0);
}

int main()
{
	listing_config(4, 6);
}
