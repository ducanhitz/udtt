#include <iostream>
#include <string>

using namespace std;


string A="Vietx";
string B="Ban Viet o Viet Nam";
char xc[4];
int L[5][20];

int algo()
{
    int m = A.length(), n=B.length();
    for (int i = 0; i <= m; i++)
        L[i][0] = 0;
    for (int j = 0; j <= n; j++)
        L[0][j] = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }
    return L[m][n];
}

void Xau_con()
{
    int i=A.length(), j=B.length(), k=0;
    while(L[i][j] != 0)
    {
        if(A[i-1] == B[j-1]){
            xc[k] = A[i-1];
            k++; i--; j--;
        }
        else{
            if(L[i-1][j] > L[i][j-1])
                i--;
            else j--;
        }
    }
    xc[k] = '\0'; strrev(xc);
}

int main()
{
    cout<<"Do dai xau con lon nhat: "<<algo()<<endl;
    Xau_con();
    cout<<"Xau con chung lon nhat: "<<xc<<endl;
    return 0;
}