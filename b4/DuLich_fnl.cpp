#include <iostream>

using namespace std;

int n = 9; // so dinh
// ma hoa dinh: a: 0, b: 1, c: 2, d: 3, ...
int u = 0; // dinh bat dau
int v = 7; // dinh ket thuc
int p[9];
int m = 0;
bool go[9] = {false};

int c[9][9] = {
    {-1, -1, 10, 10, 9, -1, -1, -1, -1},
    {-1, -1, 10, 10, 9, -1, 8, 12, 5},
    {10, -1, 10, 6, -1, -1, -1, 20, -1},
    {10, -1, 6, 7, 7, 8, -1, -1, 6},
    {-1, -1, -1, 7, -1, -1, 10, 15, -1},
    {-1, -1, 10, 10, 9, -1, -1, -1, -1},
    {-1, 8, -1, 8, -1, 10, -1, -1, 5},
    {-1, 12, 20, -1, -1, 15, -1, -1, -1},
    {-1, 5, -1, -1, 6, -1, 5, -1, -1},
};

int cost = 0;

bool greedy_travel_sales_man()
{
    p[m] = u;     // tap muc tieu chua dinh xuat phat
    go[u] = true; // danh dau dinh u da tham
    while (u != v)
    {
        // tim dinh ke voi dinh u chua tham, co chi phi tu u di sang dat min
        // 1: tim dinh ke dau tien
        int w = 0;
        while (w < n && (go[w] == true || c[u][w] == -1))
            w++;
        // 2: kiem tra co dinh ke khong
        if (w == n)
            return false;
        else
        {
            u = w; // di tam sang w
            w++;
            while (w < n)
            {
                if (go[w] == false && c[p[m]][w] != -1 && c[p[m]][w] < c[p[m]][u])
                    u = w;
                w++;
            }
            cost += c[p[m]][u];
            m++;
            p[m] = u;
            go[u] = true;
        }
    }
    return true;
}

int main()
{
    if (greedy_travel_sales_man())
    {
        cout << "Tim duoc duong di: ";
        for (int i = 0; i <= m; i++)
            cout << (char)(p[i] + 65) << " ";
        cout << "\nVoi tong chi phi: " << cost << endl;
    }
    else
        cout << "Khong tim duoc duong di: " << endl;
}

