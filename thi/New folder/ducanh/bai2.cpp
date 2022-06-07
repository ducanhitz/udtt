#include <iostream>
#include <iomanip>

using namespace std;

string tenTS[10] = {
    "Tai San 1",
    "Tai San 2",
    "Tai San 3",
    "Tai San 4",
    "Tai San 5",
    "Tai San 6",
    "Tai San 7",
    "Tai San 8",
    "Tai San 9",
    "Tai San 10",
};
int soLuong[10] = {
    10,
    20,
    50,
    30,
    40,
    15,
    25,
    45,
    60,
    70,
};

struct TaiSan
{
    string tenTS;
    int soLuong;
};

void Nhap(TaiSan ts[], int n)
{
    for (int i = 0; i < n; i++)
    {
        ts[i].tenTS = tenTS[i];
        ts[i].soLuong = soLuong[i];
    }
}

int TimKiemNhiPhan(TaiSan ts[], int left, int right, int x)
{
    if (left >= right)
        return left;
    int middle = (left + right) / 2;
    if (x > ts[middle].soLuong)
        return TimKiemNhiPhan(ts, left, middle - 1, x);
    return TimKiemNhiPhan(ts, middle + 1, right, x);
}

void ChenX(TaiSan ts[], int &n, TaiSan X, int k)
{
    for (int i = n; i >= k; i--)
        ts[i] = ts[i - 1];
    ts[k] = X;
    n++;
}

void LaySoLuong(TaiSan ts[], int m)
{
    int i = 0;
    while (m > 0)
    {
        m -= ts[i].soLuong;
        cout << setw(18) << left << ts[i].tenTS << " " << ts[i].soLuong << endl;
        i++;
    }
}

void Sort(TaiSan ts[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (ts[i].soLuong < ts[j].soLuong)
            {
                TaiSan temp = ts[i];
                ts[i] = ts[j];
                ts[j] = temp;
            }
        }
    }
}


int main()
{
    TaiSan ts[11];
    int n = 10;

    Nhap(ts, n);
    Sort(ts, n);

    TaiSan ts_new = {"Tai San Test", 22};
    int vitri = TimKiemNhiPhan(ts, 0, n - 1, ts_new.soLuong) + 1;
    cout << "Vi tri de chen cong nhan moi vao danh sach la: " << vitri << endl;
    ChenX(ts, n, ts_new, vitri);
    cout << "Danh sach tai san sau khi chen la: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(18) << left << ts[i].tenTS << " " << ts[i].soLuong << endl;
    }
    
    int p = 100;
    cout << "Can lay tai san sau de so luong lon hon " << p << ": " << endl;
    LaySoLuong(ts, p);

    return 0;
}