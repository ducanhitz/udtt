// de3
#include <iostream>
#include <string>

using namespace std;

struct MayTinh
{
    string nhanHieu;
    float giaNhap;
    float giaBan;
};

string NH[7] = {"Toshiba", "LG", "HP", "Lenovo", " Toshiba VN", " LG VN", " HP VN"};
float GN[7] = {1000, 2000, 3000, 1300, 2100, 4200, 2200};
float GB[7] = {1000, 2000, 3000, 1300, 2100, 4200, 2200};

void nhapMay(MayTinh M[])
{
    for (int i = 0; i < 7; i++)
    {
        M[i].nhanHieu = NH[i];
        M[i].giaNhap = GN[i];
        M[i].giaBan = GB[i];
    }
}

int Xuat(MayTinh M[], int n, int i = 0)
{
    if (i == n)
        return 0;
    cout << "\nThong Tin May Thu: " << i + 1;
    cout << "\nNhan hieu may thu: " << i + 1 << "\t" << M[i].nhanHieu;
    cout << "\nGia Nhap :" << M[i].giaNhap;
    cout << "\nGia Ban :" << M[i].giaBan;
    return Xuat(M, n, i + 1);
}

int XepHang(MayTinh *M, int n, float k)
{
    int i = 0;
    while (k > 0 && k > M[i].giaBan)
    {
        k -= M[i].giaBan;
        i++;
    }
    return i;
}

void Sort(MayTinh *M, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (M[i].giaBan < M[j].giaBan)
            {
                MayTinh temp = M[i];
                M[i] = M[j];
                M[j] = temp;
            }
        }
    }
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void next_config(int x[], int n, int i)
{
    int k = n;
    while (x[k] < x[i])
        k--;
    swap(x[i], x[k]);
    int j = n;
    i++;
    while (i < j)
    {
        swap(x[i], x[j]);
        i++;
        j--;
    }
}

void display(int x[], int k, MayTinh M[])
{
    for (int i = 1; i <= k; i++)
        cout << M[x[i] - 1].nhanHieu << " ";
    cout << "\n";
}

void listing_configs(int n, MayTinh M[])
{
    int i, x[n + 1];
    for (int i = 1; i <= n; i++)
        x[i] = i;
    do
    {
        display(x, n, M);
        i = n - 1;

        while (i > 0 && x[i] > x[i + 1])
            i--;

        if (i > 0)
        {
            next_config(x, n, i);
        }
    } while (i > 0);
}

int main()
{
    int n = 7;
    MayTinh m[7];
    nhapMay(m);
    Xuat(m, n, 0);
    cout << endl;
    listing_configs(3, m);

    int k;
    float q = 10000;
    int sokien = XepHang(m, n, q);
    cout << "So may can ban it nhat: " << sokien << endl;
    for (int i = 0; i < sokien; i++)
    {
        cout << m[i].nhanHieu << " " << m[i].giaBan << endl;
    }

    return 0;
}