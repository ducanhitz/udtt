#include <bits/stdc++.h>
using namespace std;

int c[100];

void display(int a[], int m)
{
	for(int i=0; i<m; i++)
		cout<<a[i]<<"	";
	cout<<endl;
}


void Tron(int a[], int n, int b[], int m)
{
	int Max = a[n-1];
	if(Max < b[m-1])
		Max = b[m-1];
	
	a[n] = b[m] = Max+1;
	
	int i = 0, j = 0;
	for(int k=0; k<n+m; k++)
		if(a[i]<b[j]){
			c[k] = a[i];
			i++;
		}
		else{
			c[k] = b[j];
			j++;
		}

}




void sort(int a[], int m)
{
	for(int i=0; i<m-1; i++)
		for(int j=i+1; j<m; j++)
			if(a[j]<a[i]){
				int tg = a[i];
				a[i]=a[j];
				a[j]=tg;
			}	
}



int main()
{
	int a[50], b[50], n, m;
	cout<<"\nNhap so phan tu mang a: ";
	cin>>n;
	cout<<"\nNhap so phan tu mang b: ";
	cin>>m;
	
	srand(time(NULL));
	for(int i=0; i<n; i++)
		a[i] = 0 + rand() % (9 + 1 - 0);
	for(int i=0; i<m; i++)
		b[i] = 0 + rand() % (9 + 1 - 0);
	
	sort(a,n);
	sort(b,m);
	
	cout<<"\nMang a: ";
	display(a,n);
	cout<<"\nMang b: ";
	display(b,m);
	
	Tron(a,n,b,m);
	cout<<"\nTron mang a va b: ";
	display(c,n+m);
		
	return 0;
}