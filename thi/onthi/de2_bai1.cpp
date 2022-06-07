#include <iostream>

using namespace std;

int khoiLuong[6] = {3, 1, 2, 3, 5, 4};
int giaTri[6] = {4, 4, 5, 6, 3, 7};

struct ThungHang
{
    int khoiLuong;
    int giaTri;
};

void Nhap(ThungHang th[])
{
    for (int i = 0; i < 6; i++)
    {
        th[i].khoiLuong = khoiLuong[i];
        th[i].giaTri = giaTri[i];
    }
}

//Tham Lam
void LayHang(ThungHang th[], int m)
{
    int i = 0;
    while (m > 0 && m > th[i].khoiLuong)
    {
        m -= th[i].khoiLuong;
        i++;
        cout << th[i].giaTri << " " << th[i].khoiLuong << endl;
    }
}

void Sort(ThungHang th[])
{
    for (int i = 0; i < 6 - 1; i++)
    {
        for (int j = i + 1; j < 6; j++)
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
int F[6][16];

void Algorithm(ThungHang th[], int m)
{
    for (int i = 0; i <= m; i++)
        F[0][i] = 0;
    for (int i = 1; i <= 6; i++)
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
    cout << "Cac thung hang de tai trong khong vuot qua " << m << " va gia tri nhieu nhat la: " << endl;
    while (i != 0)
    {
        if (F[i][j] != F[i - 1][j])
        {
            cout << th[i].giaTri << " " << th[i].khoiLuong << endl;
            j = j - th[i].khoiLuong;
        }
        i--;
    }
    cout << endl;
}

int main()
{
    ThungHang th[6];

    Nhap(th);

    int m;
    cout << "Nhap vao tai trong toi da cua o to: ";
    cin >> m;

    //tham lam
    Sort(th);
    LayHang(th, m);

    //quy hoach dong
    Algorithm(th, m);
    KetQua(th, m);

    return 0;
}