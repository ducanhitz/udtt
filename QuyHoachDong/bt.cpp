#include <iostream>

using namespace std;

int f[100][100];


int analys01(int m, int n)
{
    for(int i=1; i<=m; i++)
        for(int j=0; j<=n; j++)
            if(j<i)
                f[i][j] = f[i-1][j];
            else
                f[i][j] = f[i-1][j] + f[i][j-i];   
    return f[n][n];        
}

int main()
{
    int m, n;
    cout<<"Nhap m: ";
    cin>>m;
    cout<<"Nhap n: ";
    cin>>n;
    
    f[0][0] = 1;
    for(int i=1; i<=m; i++)
        f[0][i] = 0;
    analys01(m,n);
    cout<< "f(" << m << "," << n << ") = " << f[m][n] << endl;
    cout <<  f[5][5] << endl;

    return 0;
}
