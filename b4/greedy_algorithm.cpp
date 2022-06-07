#include <iostream>

using namespace std;

void sort(int *C, int m)
{
	for(int i=0; i<m-1; i++)
		for(int j=i+1; j<m; j++)
			if(C[j]<C[i]){
				int tg = C[i];
				C[i]=C[j];
				C[j]=tg;
			}	
}

int GA(int *C, int m, int n)
{
    int i=0;
    while (n>0 && i<m && n >= C[i])
    {
        n -= C[i];
        i++;
    }
    return i;
}

int main()
{
    int *C;
    int m, n;
    cout<<"Nhap so luong chai: ";
    cin>>m;
    C = new int[m];
    for (int i = 0; i < m; i++)    
    {
        cout<<"Nhap dung tich chai "<<i+1<<": ";
        cin>>C[i];
    }
    cout<<"Nhap so luong nuoc co: ";
    cin>>n;
    sort(C, m);
    cout<<"Luong nuoc co: "<<n<<endl;
    cout<<"So chai toi da duoc su dung: "<<GA(C, m, n)<<endl;                        

}