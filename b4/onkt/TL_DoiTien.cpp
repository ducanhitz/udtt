#include <iostream>

using namespace std;

bool Min_coin(int *C, int m, int n, int *s)
{
    int i = 0;
    while (n > 0 && i < m)
    {
        s[i] = n / C[i];
        n = n % C[i];
        i++;
    }
    if (n > 0)
        return false;
    else
        return true;
}

void Sort(int *c, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (c[i] < c[j])
            {
                int temp = c[i];
                c[i] = c[j];
                c[j] = temp;
            }
        }
    }
}

int main()
{
    int *C, *s;
    int n, m;
    cout << "Nhap so luong menh gia: ";
    cin >> m;
    C = new int[m];
    s = new int[m];
    for (int i = 0; i < m; i++)
    {
        s[i] = 0;
        cout << "Nhap C[" << i << "] = ";
        cin >> C[i];
    }
    Sort(C, m);


    cout << "Nhap so tien: ";
    cin >> n;
    if (Min_coin(C, m, n, s))
    {
        cout << "So tien: " << n << endl;
        cout << "So luong cac menh gia: " << endl;
        int tong = 0;
        for (int i = 0; i < m; i++)
        {
            cout << "Menh gia " << C[i] << ": " << s[i] << endl;
            tong += s[i];
        }

        cout << "Tong so to it nhat can su dung: " << tong << endl;
    }
}