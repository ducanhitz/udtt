#include <iostream>
#include <string>

using namespace std;

string T = "Viet$Ban Viet o Viet Nam";
int z[100] = {0};

void z_algo(string s, int z[])
{
    int n = s.length(), l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i > r)
        {
            l = r = i;
            while (r < n && s[r - l] == s[r])
                r++;
            z[i] = r - l;
            r--;
        }
        else if (z[i - l] < r - i + 1)
            z[i] = z[i - l];
        else
        {
            l = i;
            while (r < n && s[r - l] == s[r])
                r++;
            z[i] = r - l;
            r--;
        }
    }
}



int main()
{
    z_algo(T, z);
    for (int i = 0; i < T.length(); i++)
    {
        cout << " " << T[i];
    }
    cout<<endl;
    for(int i=0; i<T.length(); i++)
    {
        cout<<" "<<z[i];
    }
    return 0;
}