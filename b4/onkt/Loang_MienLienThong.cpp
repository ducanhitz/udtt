#include <bits/stdc++.h>
using namespace std;

int SoMien = 0;
/*
int a[5][6]={ { 1,1,0,0,0,1},
              { 1,0,0,0,0,0},
              { 1,0,0,1,1,0},
              { 0,1,1,0,0,1},
              { 0,0,1,0,1,1},};
*/

int a[5][6];
bool flag[5][6] = {false};

void loang(int i, int j)
{
    flag[i][j] = true;
    if (a[i - 1][j] == a[i][j] && !flag[i - 1][j] && i > 0)
        loang(i - 1, j);

    if (a[i + 1][j] == a[i][j] && !flag[i + 1][j] && i < 4)
        loang(i + 1, j);

    if (a[i][j - 1] == a[i][j] && !flag[i][j - 1] && j > 0)
        loang(i, j - 1);

    if (a[i][j + 1] == a[i][j] && !flag[i][j + 1] && j < 5)
        loang(i, j + 1);
}

int main()
{

    srand(time(NULL));
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            a[i][j] = rand() % 2;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
            cout << a[i][j] << "	";
        cout << endl;
    }

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 6; j++)
            if (!flag[i][j])
            {
                SoMien++;
                loang(i, j);
            }

    cout << "So mien lien thong la :" << SoMien << endl;
}