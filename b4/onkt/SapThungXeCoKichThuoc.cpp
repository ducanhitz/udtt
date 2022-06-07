#include <iostream>

using namespace std;

struct Hang
{
    char ten[20];
    float kichthuoc;
    float khoiluong;
};

int XepHang(Hang *h, int n, float k)
{
    int i = 0;
    while (k > 0 && k > h[i].kichthuoc)
    {
        k -= h[i].kichthuoc;
        i++;
    }
    return i;
}

void Sort(Hang *h, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (h[i].kichthuoc > h[j].kichthuoc)
            {
                Hang temp = h[i];
                h[i] = h[j];
                h[j] = temp;
            }
        }
    }
}

int main()
{
    int n;
    cout << "Nhap so kien hang: ";
    cin >> n;

    Hang *h;
    h = new Hang[n];
    cout << "Nhap khoi luong cua cac kien hang: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Nhap khoi luong cua kien hang thu " << i + 1 << ": " << endl;
        cout << "Nhap ten: ";
        fflush(stdin);
        cin.getline(h[i].ten, 20);
        cout << "Kich thuoc: ";
        cin >> h[i].kichthuoc;
        cout << "Khoi luong: ";
        cin >> h[i].khoiluong;
    }

    Sort(h, n);

    int k;
    float q = 10000;
    cout << "Nhap kich thuoc thung xe: ";
    cin >> k;
    int sokien = XepHang(h, n, q);
    cout << "So kien hang nhieu nhat co the xep len xe la: " << sokien << endl;
    for (int i = 0; i < sokien; i++)
    {
        cout << m[i].nhanHieu << " " << m[i].giaBan << endl;
    }

    return 0;
}