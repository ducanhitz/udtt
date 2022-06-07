#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//float a[10] = {100003.3, 100011.4, 123000.5, 300000.6, 400001.7, 500000.8, 230000.9, 240001, 420000, 888888};
float a[10] = {0,0,0,0,0,0,0,0,2.5,2.5};
int dem = 0;

float tongmangduong(float a[], int n)
{
    if (n == 0)
        return a[0];
    if (a[n - 1] > 0)
    {
        dem++;
        return a[n - 1] + tongmangduong(a, n - 1);
    }
    return tongmangduong(a, n - 1);
}

void xuatmangnguoc(float a[], int n)
{
    if (n == 0)
        return;
    cout << "a[" << n - 1 << "]= " << fixed << setprecision(1) << a[n-1] << endl;
    xuatmangnguoc(a, n - 1);
}

int main()
{
    cout << "Danh sach theo thu tu nguoc la: " << endl;
    xuatmangnguoc(a, 10);

    float sum = tongmangduong(a, 10);
    cout << "Trung binh cong cac phan tu duong la: " << fixed << setprecision(1) << sum/dem << endl;

    return 0;
}
