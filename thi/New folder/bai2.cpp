#include <bits/stdc++.h>

using namespace std;
const int N = 50;
int a[N];
int n, Min, cnt = 0;


void nhap()
{
    cout << "Nhap n: ";
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Nhap a[" << i << "] = ";
        cin >> a[i];
        Min += a[i]; 
    }
}


void timMin(int i, int A, int B)
{
    if (i > n)
    {
        Min = min(Min, abs(A - B));
        return;
    }
    timMin(i + 1, A + a[i], B);
    timMin(i + 1, A, B + a[i]);
}

void truyvet(int i, int A, int B, string trangthai)
{
    if (i > n)
    {
        if (Min == abs(A - B))
        {

            cnt++;
            cout << "Cach thu : " << cnt << "\n";
            cout << "Chi so cua cac so thuoc day 1 : ";
            for (int k = 0; k < trangthai.size(); ++k)
            {
                if (trangthai[k] == '0')
                    cout << k + 1 << " ";
                //nêu in ra số thia a[k+1]
            }
            cout << "\n";

            cout << "Chi so cua cac so thuoc day 2 : ";
            for (int k = 0; k < trangthai.size(); ++k)
            {
                if (trangthai[k] == '1')
                    cout << k + 1 << " ";
            }
            cout << "\n\n";
        }
        return;
    }
    truyvet(i + 1, A + a[i], B, trangthai + "0");
    truyvet(i + 1, A, B + a[i], trangthai + "1");
}
int main()
{
    nhap();
    timMin(1, 0, 0);
    cout << "Chenh lech nho nhat la: " << Min << "\n";

    truyvet(2, a[1], 0, "0");

    return 0;
}
