#include <iostream>
#include <string>

using namespace std;

string T = "a428hq2jeqjr83";
string P = "j";

int char_in_string(char x, string a)
{
    for (int i = 0; i < a.length(); i++)
        if (a[i] == x)
            return i;
    return -1;
}

int Boyer_Moore_Horspool()
{
    int dem = 0, i = P.length() - 1, v = P.length();
    while (i < T.length())
    {
        int x = v - 1, j = i;
        while (T[j] == P[x] && x > -1)
        {
            j--;
            x--;
        }
        if (x < 0)
        {
            dem++;
            i = i + v;
        }
        else
        {
            int x = char_in_string(T[j], P);
            if (x < 0)
                i = i + v;
            else
                i = i + v - x - 1;
        }
    }
    return dem;
}

int main()
{
    if (Boyer_Moore_Horspool() == 1)
        cout << "Co chuoi P=" << P << " trong chuoi T=" << T;
    else
        cout << "False";
    return 0;
}