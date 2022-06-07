#include <iostream>

using namespace std;

struct Hang
{
    char ten[20];
    float khoiluong;
};

int XepHang(Hang *h, int n, float k)
{
    int i = 0;
    while (k > 0 && k > h[i].khoiluong)
    {
        k -= h[i].khoiluong;
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
            if (h[i].khoiluong > h[j].khoiluong)
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
        cin.ignore();
        cin.getline(h[i].ten, 20);
        cout << "Khoi luong: ";
        cin >> h[i].khoiluong;
    }

    Sort(h, n);

    int k;
    cout << "Nhap kich thuoc thung xe: ";
    cin >> k;
    int n_kh = XepHang(h, n, k);
    cout << "So kien hang nhieu nhat co the xep len xe la: " << n_kh << endl;
    for (int i = 0; i < n_kh; i++)
    {
        cout << h[i].ten << " " << h[i].khoiluong << endl;
    }

    return 0;
}