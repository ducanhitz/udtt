#include <iostream>

using namespace std;

bool Min_coin(int *C, int m, int n, int *s)
{
    int i=0;
    while (n>0 && i<m)
    {
        s[i] = n/C[i];
        n -= s[i]*C[i];
        i++;
    }
    if(n>0) return false;
    else return true;
}

int main()
{
    int *C, *s;
    int n, m;
    cout<<"Nhap so luong menh gia: ";
    cin>>m;
    C = new int[m];
    s = new int[m];
    for(int i=0; i<m; i++)
    {
        s[i] = 0;
        cout<<"Nhap C["<<i<<"] = ";
        cin>>C[i];
    }
    cout<<"Nhap so tien: ";
    cin>>n;
    if(Min_coin(C,m,n,s))
    {
        cout<<"So tien: "<<n<<endl;
        cout << "So luong cac menh gia: "<<endl;

        for (int i = 0; i < m; i++)
            cout << "Menh gia " << C[i] << ": "<<s[i]<<endl;
    }

}
