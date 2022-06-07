#include <bits/stdc++.h>

using namespace std;

double pow(float a, int n)
{
    if(n == 1) {
        return a;
    } else { 
        if(n % 2 == 0)
            return pow(a, n/2) * pow(a, n/2);
        else
            return pow(a, n/2) * pow(a, n/2) * a;
    }
}

int main()
{
    float a;
    cout << "Nhap co so a: ";
    cin >> a;

    int n;
    cout << "Nhap so mu n: ";
    cin >> n;

    cout << "Pow(a, n) = " << pow(a,n) << endl;

    return 0;
}