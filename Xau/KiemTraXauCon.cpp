#include <iostream>
#include <string>

using namespace std;

string T = "a428hq2jeqjr83";
string P = "a42";


int indexOf(string p,string t)
{
    int m = p.length();
    int n = t.length() - m;
    for (int i = 0; i <= n; i++)
    {
        int j = 0;
        while (j < m && t[i + j] == p[j])
        {
            j++;
        }
        if (j == m)
            return i;
    }
    return -1;
}

int main()
{
    if (indexOf(P, T) != -1)
        cout<<"True";
    else cout<<"False";
    return 0;
}