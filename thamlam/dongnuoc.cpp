#include <iostream>

using namespace std;

void Sort(int *C, int m)
{
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            if (C[i] > C[j])
            {
                int temp = C[i];
                C[i] = C[j];
                C[j] = temp;
            }
        }
    }
}

int DongNuoc(int *C, int m, int n)
{
    int i = 0;
    while (n > 0 && i < m && n >= C[i])
    {
        n -= C[i];
        i++;
    }
    return i;
}

int main()
{
    int *C;
    int m, n;

    cout << "Nhap so luong chai nuoc: ";
    cin >> m;
    C = new int[m];
    for (int i = 0; i < m; i++)
        cin >> C[i];

    Sort(C, m);

    cout << "Nhap dung tich nuoc: ";
    cin >> n;

    cout << "So luong chai nuoc nhieu nhat la: " << DongNuoc(C, m, n);
}