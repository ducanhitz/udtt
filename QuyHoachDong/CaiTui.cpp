#include <iostream>

using namespace std;

int n = 6, m = 10;
//Giá trị
int v[7] = {4, 3, 2, 5, 1, 6};
//Trọng Lượng
int w[7] = {3, 6, 2, 7, 1, 5};
int F[7][11];

void algo()
{
    for (int i = 0; i <= m; i++)
    {
        F[0][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            F[i][j] = F[i - 1][j];
            int temp = F[i - 1][j - w[i]] + v[i];
            if (w[i] <= j && F[i][j] < temp)
                F[i][j] = temp;
        }
    }
}

void result()
{
    cout << "Max value = " << F[n][m] << endl;
    int i = n, j = m;
    while (i != 0)
    {
        if (F[i][j] != F[i - 1][j])
        {
            cout << i << " ";
            j = j - w[i];
        }
        i--;
    }
}



int main()
{
    algo();
    cout << "Bang phuong an: " << endl;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            cout << F[i][j] << " ";
        cout << endl;
    }
    result();
}