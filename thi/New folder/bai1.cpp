#include <iostream>

using namespace std;

int n = 6;
int khoiLuong[6] = {3, 1, 2, 3, 5, 4};
int giaTri[6] = {200, 250, 100, 300, 500, 800};

struct ThungHang
{
    int khoiLuong;
    int giaTri;
};

void Nhap(ThungHang th[])
{
    for (int i = 0; i < n; i++)
    {
        th[i].khoiLuong = khoiLuong[i];
        th[i].giaTri = giaTri[i];
    }
}

//Tham Lam
void LayHang(ThungHang th[], int m)
{
    cout << "Cac thung hang de tai trong khong vuot qua " << m << " va gia tri nhieu nhat la: (Tham lam)" << endl;
    int i = 0;
    while (m > 0 && m >= th[i].khoiLuong)
    {
        m -= th[i].khoiLuong;
        cout << th[i].giaTri << " " << th[i].khoiLuong << endl;
        i++;
    }
}

void Sort(ThungHang th[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (th[i].giaTri < th[j].giaTri)
            {
                ThungHang temp = th[i];
                th[i] = th[j];
                th[j] = temp;
            }
        }
    }
}

//Quy hoach dong
int F[7][20];

void Algorithm(ThungHang th[], int m)
{
    for (int i = 0; i <= m; i++)
        F[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            F[i][j] = F[i - 1][j];
            int temp = F[i - 1][j - th[i].khoiLuong] + th[i].giaTri;
            if (th[i].khoiLuong <= j && F[i][j] < temp)
                F[i][j] = temp;
        }
    }
}

void KetQua(ThungHang th[], int m)
{
    int i = 6, j = m;
    cout << "Cac thung hang de tai trong khong vuot qua " << m << " va gia tri nhieu nhat la: (Quy hoach dong)" << endl;
    while (i != 0)
    {
        if (F[i][j] != F[i - 1][j])
        {
            cout << th[i].giaTri << " " << th[i].khoiLuong << endl;
            j = j - th[i].khoiLuong;
        }
        i--;
    }
}

int main()
{
    ThungHang th[6];

    Nhap(th);
    cout << "Danh sach thung hang: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << th[i].giaTri << " " << th[i].khoiLuong << endl;
    }
    int m = 10;

    //quy hoach dong
    Algorithm(th, m);
    KetQua(th, m);

    //tham lam
    Sort(th);
    LayHang(th, m);
    
    return 0;
}