#include <iostream>

using namespace std;


int fibo( int *F, int n)
{
    F[1] = F[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }
    return F[n];
}

int main()
{
    int n;
    int *F;
    cout << "Nhap n: ";
    cin >> n;
    F = new int[n];
    cout << "f("<<n<<") = "<< fibo(F, n) << endl;

    return 0;
}

