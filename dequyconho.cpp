#include<iostream>
using namespace std;

int **d;

int C(int k, int n){
	if(k == 0 || k == n)
		d[k][n] = 1;
	else if(d[k][n] < 0)
		d[k][n] = C(k, n-1) + C(k-1, n-1);
	return d[k][n];
}
int main()
{
	int k,n;
	cout<<"Nhap k: ";
	cin>>k;
	cout<<"Nhap n: ";
	cin>>n;
	
	d = new int*[k+1];
	for(int i = 0; i<=k; i++)
		d[i] = new int[n+1];
	
	for(int i=0;i<=k;i++)
		for(int j=0;j<=n;j++)
		d[i][j]	= -1;	
	
	
	cout<<"C("<<k<<","<<n<<") = "<<C(k,n);
	return 0;
}