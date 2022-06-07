#include <bits/stdc++.h>
using namespace std;

int b[100];

void display(int a[], int m)
{
	for(int i=0; i<m; i++)
		cout<<a[i]<<"	";
	cout<<endl;
}

void sort(int *C, int a, int b)
{
	for (int i = a; i <= b; i++)
		for (int j = i + 1; j < b; j++)
			if (C[j] < C[i])
			{
				int tg = C[i];
				C[i] = C[j];
				C[j] = tg;
			}
}

void MergeSort(int a[], int l, int r){
	if(r>l)
	{
		int m = (l+r)/2;
		MergeSort(a, l, m);
		MergeSort(a, m+1, r);
		for(int i = m; i>=l; i--)
			b[i]=a[i];
		for(int j = m+1 ; j<=r ; j++)
			b[r+m+l-j]=a[j];
		sort(b,l,m);
		sort(b,m+1,r);
		int i=l, j=r;
		for(int k=l; k<=r; k++)
			if(b[i] < b[j]){
				a[k] = b[i];
				i++;
			}
			else{
				a[k] = b[j];
				j--;
			}
		
	}
}
int main()
{
	int a[100], n;
	cout<<"\nNhap so phan tu mang a: ";
	cin>>n;
	
	srand(time(NULL));
	for(int i=0; i<n; i++)
		a[i] = 0 + rand() % (9 + 1 - 0);

	cout<<"\nMang a: ";
	display(a,n);
	
	MergeSort(a,0,n-1);
	cout<<"\nTron mang a: ";
	display(b, n);
		
	return 0;
}