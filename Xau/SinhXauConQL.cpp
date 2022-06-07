#include <iostream>
#include <string>

using namespace std;

string s = "abccaba";
int n = s.length();
int dem = 0;
int k = 3;
char xc[3];

bool comat(char x, char tam[])
{
    for (int i = 0; i < strlen(tam); i++)
    {
        if (x == tam[i])
            return true;
        
    }
    return false;
}
void them(char a[], char x)
{
    int n = strlen(a);
    a[n+1] = '\0';
    a[n] = x;
}

void xoa(char a[])
{
    int n = strlen(a);
    a[n - 1] = '\0';
}

    void ThucHien(int i)
{
    char tam[100]; // Túi để "soi" các ký tự ở vị trí i
    tam[0] = '\0';
    
    if (strlen(xc) == k)
    {
        cout << xc << endl;
        dem++;
    }
    else
    {
        for (int j = i; j < n; j++)
        {
            if (comat(s[j], tam) == false)
            {
                them(tam, s[j]); // thêm s[j] vào "túi" tam
                them(xc, s[j]);  // thêm s[j] vào xâu con xc
                ThucHien(j + 1); // thực hiện tiếp |xc|=j+1
                xoa(xc);         // xoá ký tự cuối cùng của xâu xc
            }
        }
    }
}
int main()
{

    ThucHien(0);
    return 0;
}