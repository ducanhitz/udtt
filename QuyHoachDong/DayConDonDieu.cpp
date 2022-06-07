#include <iostream>

using namespace std;

int a[11] = {0, 1, 8, 3, 4, 9, 10, 5, 11, 7, 12};
int L[11];
int T[11];
int n = 9;
int jmax;

const int int_min = -2147483647;
const int int_max = 2147483647;

void algo()
{
    a[0] = int_min;
    a[n + 1] = int_max;
    L[n + 1] = 1;
    for (int i = n; i > 0; i--)
    {
        jmax = n + 1;
        for (int j = i + 1; j <= n; j++)
        {
            if (a[j] > a[i] && L[j] > L[jmax])
                jmax = j;
        }
        L[i] = L[jmax] + 1;
        T[i] = jmax;
    }
}

void result()
{
    int k = T[0];
    cout << "Day con: ";
    while (k != n + 1)
    {
        cout << "a[" << k << "]: " << a[k] << " ";
        k = T[k];
    }
}

int main()
{
    algo();
    result();
    return 0;
}
