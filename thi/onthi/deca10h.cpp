#include <iostream>

using namespace std;

int a[10] = {100003, 100011, 123000, 300000, 400001, 500000, 230000, 240001, 420000, 888888};
int dem = 0;

float tongmangle(int a[], int n)
{
    if (n == 0)
        return a[0];
    if (a[n - 1] % 2 != 0)
    {
        dem++;
        return a[n - 1] + tongmangle(a, n - 1);
    }
    return tongmangle(a, n - 1);
}

void xuatmang(int a[], int n)
{
    if (n == 0)
        return;
    xuatmang(a, n - 1);
    cout << a[n - 1] << " ";
}

int main()
{
    cout << tongmangle(a, 10) / dem << endl;

    xuatmang(a, 10);

    cout << endl;
}