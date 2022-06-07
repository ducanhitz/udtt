#include<iostream>
#include<stdio.h>
using namespace std;
 
int A[8][8] = { 0 };//Khởi tạo mảng giá trị 0
int X[8] = { -2,-2,-1,-1, 1, 1, 2, 2};
int Y[8] = { -1, 1,-2, 2,-2, 2,-1, 1};
int dem = 0, n = 8;
 
void xuat() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout<<A[i][j]<<"	";
        cout << endl;
    }
    cout << endl;
}


void Try(int x, int y) {
    dem++;
    A[x][y] = dem;
    for (int i = 0; i < 8; i++) {
        if (dem == n*n) {
            cout << "Cac buoc di la: \n";
            xuat();
        }
        int u = x + X[i];
        int v = y + Y[i];
        if (A[u][v] == 0 && u >= 0 && u < n && v >= 0 && v < n)
            Try(u, v);
    }
    //ko co buoc di
    dem--;
    A[x][y] = 0;
}




int main() {
    int a, b;
    cout << "Nhap vi tri ban dau!"<<endl;
    cout<<"x: ";
    cin>>a;
    cout << "y: ";
    cin >> b;
    Try(a, b);
    cout << "Khong tim thay duong di.";
    return 0;
}
