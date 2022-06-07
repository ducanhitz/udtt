#include <iostream>

using namespace std;

void Sort(float *c, int m)
{
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            if (c[i] < c[j])
            {
                float temp = c[i];
                c[i] = c[j];
                c[j] = temp;
            }
        }
    }
}


int ChiaXeTai(float *c, int n, int m)
{
    int i = 0;
    while (n > 0 && i < m)
    {
        n -= c[i];
        i++;
    }
    return i;
}

int main()
{
    int n;
    cout << "Nhap so xe tai: ";
    cin >> n;

    float *c;
    c = new float[n];
    cout << "Nhap tai trong cua cac xe tai: ";
    for (int i = 0; i < n; i++)
        cin >> c[i];

    Sort(c, n);
    for(int i = 0; i < n; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;

    int m;
    cout << "Nhap khoi luong hang muon chuyen: ";
    cin >> m;
    cout << "So xe can thiet de chuyen so luong hang tren la: " << ChiaXeTai(c, m, n) << endl;

    return 0;
}
