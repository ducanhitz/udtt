#include <iostream>
using namespace std;

bool check[1] = {false};
char P[4] = "Cho";

#define n 1

int char_in_string(char c, char a[])
{
    int leng = strlen(a);
    for (int i = 0; i < leng; i++)
    {
        if (a[i] == c)
        {
            return i;
        }
    }
    return -1;
}

void Boyer_Moore_Horspool()
{ // P là chuỗi con, T là chuỗi cha
    int i = strlen(P) - 1, v = strlen(P);
    char T[10] = "MyChoMyyy";
    while (i < strlen(T))
    {
        int x = v - 1, j = i;
        while (T[j] == P[x] && x > -1) // mỗi phần tử chuỗi P = phần tử chuỗi T, duyệt từ cuối duyệt về
        {
            j--;
            x--;
        }
        if (x < 0) // nếu trừ đến khi x < 0, tức là chuỗi P là con chuỗi T
        {
            check[0] = true;
            i = i + v;
        }
        else
        {
            int k = char_in_string(T[j], P);
            if (k < 0)
            {
                i = i + v;
            }
            else
            {
                i = j + v - k - 1;
            }
        }
    }
}

int main()
{
    Boyer_Moore_Horspool();
    for (int i = 0; i < n; i++)
        cout << check[i] << '\t';
}