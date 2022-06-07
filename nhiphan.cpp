 #include<iostream>
#define MAX 20
using namespace std;
 
int n;
int x[MAX];
 
void show() {
    for (int i = 1; i <= n; i++)
        cout << x[i] << " ";
    cout << endl;
}
 
void Try(int k) {
    for (int i = 0; i <= 1; i++) {
        x[k] = i;
        if (k == n)
            show();
        else
            Try(k + 1);    
    }
}
 
int main() {
    cout << "Nhap n: ";
    cin >> n;
    Try(1);
}