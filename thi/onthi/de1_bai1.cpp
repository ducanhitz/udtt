#include <iostream>

using namespace std;

string tenGiay[6] = {"Giay 1", "Giay 2", "Giay 3", "Giay 4", "Giay 5", "Giay 6"};
float gia[6] = {100, 70, 150, 80, 200, 300};

struct Giay
{
    string tenGiay;
    float gia;
};

void Nhap(Giay g[], int n = 6)
{
    for (int i = 0; i < n; i++)
    {
        g[i].tenGiay = tenGiay[i];
        g[i].gia = gia[i];
    }
}

int MuaGiay(Giay g[], int m)
{
    int i = 0, count = 0;
    while (m > 0 && m >= g[i].gia)
    {
        m -= g[i].gia;
        count++;
        i++;
    }
    return count;
}

void Sort(Giay g[], int n = 6)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (g[i].gia < g[j].gia)
            {
                Giay temp = g[i];
                g[i] = g[j];
                g[j] = temp;
            }
        }
    }
}

int a[6];
int k;
void display()
{
    for (int i = 1; i <= k; i++)
        cout << gia[a[i] - 1] << " ";
    cout << endl;
}

void Try(int i, int n = 6)
{
    for (int j = a[i - 1] + 1; j <= n - k + i; j++)
    {
        a[i] = j;
        if (i == k)
            display();
        else
            Try(i + 1);
    }
}

int main()
{
    Giay g[7];

    Nhap(g);

    Sort(g);
    int m;
    cout << "Nhap so tien T co: ";
    cin >> m;
    int count = MuaGiay(g, m);
    cout << "T co the mua nhieu nhat " << count << " doi giay!" << endl;

    cout << "Nhap so doi giay can mua: ";
    cin >> k;
    cout << "Cac phuong an de mua " << k << " doi giay la: " << endl;
    Try(1);

    return 0;
}