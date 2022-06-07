#include <iostream>

using namespace std;

long *d;
long Fibo(int n)
{
    if (n == 0 || n == 1)
    {
        d[n] = 1;
    }
    else if (d[n] < 0)
        d[n] = Fibo(n - 1) + Fibo(n - 2);
    return d[n];
}

int main()
{
    int n;
    cout << "Nhap n: ";
    cin >> n;

    d = new long[n + 1];
    for (int i = 0; i <= n; i++)
        d[i] = -1;

    cout << "So Fibo thu " << n << " la: "<< Fibo(n - 1);
    
}