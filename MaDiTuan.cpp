#include <iostream>
#include<stdio.h>
using namespace std;
int a[9]= {0,2,1,-1,-2,-2,-1,1,2}; 
//buoc di tren ban co theo chieu ngang
int b[9]= {0,1,2,2,1,-1,-2,-2,-1}; 
//buoc di tren ban co theo chieu doc
int **H; //Mang 2 chieu bieu dien ban co
int n; //Kich thuoc ban co
void Try(int k, int x, int y, int &success){
//Thu nuoc di tiep theo
//success = true neu di duoc
    int u, v, suc1;
    int i = 0;
    do{
        i++;
        suc1 = 0;
        u = x + a[i];
        v = y + b[i];
        if (1 <= u && u <= n && 1 <= v && v <= n && H[u][v] == 0){
            H[u][v] = k;
            if (k < n*n){ //Chua het cac o trong ban co
                Try(k + 1, u, v, suc1);
                if (!suc1)
                    H[u][v] = 0;
            }
            else suc1 = 1;
        }
    }
    while(!suc1 && (i < 8));
    success = suc1;
}
int main(){
    int x, y, suc;
//Khoi tao ban co
    n = 5;
    H = new int*[n+1];
    for (int i=1; i<=n; i++)
    	H[i] = new int[n+1];
    
	for (int i=1; i<=n; i++)
        for (int j=1; j<=n; j++)
            H[i][j] = 0;
//Chon nuoc di dau tien
	x = 5; y = 1;
	H[x][y] = 1;
	//Thu tu nuoc di thu 2
    Try(2, x, y, suc);
    if (suc)
        for (int i=1; i<=n; i++){
            for (int j=1; j<=n; j++)
                cout<<H[i][j]<<"\t";
            cout<<endl<<endl;
        }
    else cout<<"Khong tim duoc duong di nao...!";
}
