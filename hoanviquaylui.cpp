 #include<iostream>
#define MAX 20
using namespace std;
 
int n;
int dd[MAX] = { 0 };
int x[MAX];
 
void show() {
    for (int i = 1; i <= n; i++)
        cout << x[i] << " ";
    cout << endl;
}
 
void Try(int k) {
    for (int i = 1; i <= n; i++) {
        if (dd[i] == 0) {
            x[k] = i;
            if (k == n)
                show();
            else{
                dd[i] = 1;
                Try(k + 1);
                dd[i] = 0;
            }
            
        }
    }
}
 
int main() {
    cout << "Nhap n: ";
    cin >> n;
    Try(1);
}