#include <bits/stdc++.h>
using namespace std;


void display(int a[], int m)
{
	for(int i=0; i<m; i++)
		cout<<a[i]<<"	";
}

int TKNP_DQ(int a[100], int c, int l, int r)
{
	if(l>=r)
		return -1;
	int m = (l + r)/2;
	if(a[m] == c)
		return m;
	else if(a[m] > c)
		TKNP_DQ(a,c,l,m-1);
	else
		TKNP_DQ(a,c,m+1,r);
	return -1;
}

int tim(int a[], int c, int l, int r)
{
	if(c>a[r])
		return r+1;
	if(c<a[l] || l>=r)
		return l;
	else{
		int m = (l + r)/2;
		if(a[m] > c)
			tim(a,c,l,m-1);
		else
			tim(a,c,m+1,r);
	}
}

void chen(int a[], int &n, int c, int vt)
{
	n++;
	for(int i = n; i>vt; i--)
		a[i] = a[i-1];
	a[vt] = c;
	
	display(a,n);
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
	int a[100];
	int c, n;
	cout<<"\nNhap so phan tu: ";
	cin>>n;
	cout<<"\nNhap phan tu can tim: ";
	cin>>c;
	
	srand(time(NULL));
	for(int i=0; i<n; i++)
		a[i] = 0 + rand() % (10 + 1 - 0);
	cout<<"\nMang duoc tao: ";
	
	
	sort(a,n);
	display(a,n);
	
	if(TKNP_DQ(a,c,0,n-1) == -1){
		cout<<"\nKhong co phan tu "<<c<<" trong day";
		int vt = tim(a,c,0,n-1);
		cout<<"\nDay sau khi chen ";
		chen(a,n,c,vt);
	}
		
	else
		cout<<"\nCo phan tu "<<c<<" o trong day";
}