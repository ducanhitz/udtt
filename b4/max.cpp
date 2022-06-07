#include <bits/stdc++.h>

using namespace std;

void Max(int a[], int l, int r, int &max)
{
    int max1, max2;
    if (l == r)
    	max = a[l];
    else
    {
        int m = (l + r) / 2;
        Max(a, l, m, max1);
        Max(a, m + 1, r, max2);
        if (max1 > max2)
            max = max1;
        else
            max = max2;
    }
}

void Show(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a[100], n;
    cout << "Nhap so phan tu mang a: ";
    cin >> n;

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        a[i] = 0 + rand() % (9 + 1 - 0);
    
    cout << "\nMang a: ";
    Show(a, n);

    int max = a[n - 1];
    Max(a, 0, n - 1, max);
    cout << "Gia tri lon nhat la: " << max << endl;

    return 0;
}