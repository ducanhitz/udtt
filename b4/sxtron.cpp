#include <bits/stdc++.h>
using namespace std;

int b[100];

void display(int a[], int m)
{
	for(int i=0; i<m; i++)
		cout<<a[i]<<"	";
	cout<<endl;
}



void sort1(int a[], int x, int y)
{
	for(int i=x; i<y-1; i++)
		for(int j=i+1; j<y; j++)
			if(a[j]<a[i]){
				int tg = a[i];
				a[i]=a[j];
				a[j]=tg;
			}	
}
void sort2(int a[], int x, int y)
{
	for(int i=x; i<y-1; i++)
		for(int j=i+1; j<y; j++)
			if(a[j]>a[i]){
				int tg = a[i];
				a[i]=a[j];
				a[j]=tg;
			}	
}
void MergeSort(int a[], int l, int r){
	if(r>l)
	{
		int m = (l+r)/2;
		sort1(a, l, m);
		sort2(a, m+1, r);
		
		MergeSort(a, l, m);
		MergeSort(a, m+1, r);
		
		
		for(int i = m; i>=l; i--)
			b[i]=a[i];
		for(int j = m+1 ; j<=r ; j++)
			b[r+m+1-j]=a[j];
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