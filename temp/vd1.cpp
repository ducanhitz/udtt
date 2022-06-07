#include <iostream>

using namespace std;

struct SinhVien
{
    char ten[32];
    float diem;
};

void next_config(SinhVien sv[], int k, int i)
{
    sv[i] += 1;
    i++;
    while (i <= k)
    {
        sv[i] = sv[i - 1] + 1;
        i++;
    }
}

void view_config(SinhVien sv[], int k)
{
    for (int i = 1; i <= k; i++)
    {
        cout << sv[i].ten;
    }
    cout << endl;
}
void listing_config(SinhVien sv[], int k, int n)
{
    int i;
    int x[k + 1];
    for (i = 1; i <= k; i++)
    {
        x[i] = i;
    }
    do
    {
        view_config(x, k);
        while (i > 0 && x[i] == (n - k + i))
        {
            i--;
        }
        if (i > 0)
        {
            next_config(x, k, i);
        }
    } while (i > 0);
}

int main()
{
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    SinhVien sv[n+1];

    for(int i = 0; i < n; i++)
    {
        cout << "Nhap ten sv " << i+1 << ": ";
        fflush(stdin);
        cin.getline(sv[i].ten, 32);
        cout << "Nhap diem sv " << i+1 << ": ";
        cin >> sv[i].diem;
    }

    listing_config(4, n);
}
