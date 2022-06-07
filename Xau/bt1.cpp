#include <iostream>
#include <string>

using namespace std;

string s = "abccabdad123";
int n = s.length();
string kq[12];
int k[12];
int m = 0;

int KiemTra(char x, int k)
{
    for (int i = k+1; i < m; i++)
    {
        if(x == s[i])
            return 0;
        return 1;
    }
}

void Dem()
{
    for(int i = 0; i<n; i++)
    {
        kq[m] = s[i];
        m++;
        int dem = 0;
        if(KiemTra(s[i], i))
        {
            for (int j = i + 1; j < n; i++)
            {

                if (s[i] == s[j])
                    dem++;
            }
            
        }
        
    }
}

int main()
{

    for (int i =0; i < m; i++)
    {
        cout<<kq[i]<<"  "<<k[i]<<endl;
    }
    return 0;
}
