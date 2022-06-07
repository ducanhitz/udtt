#include <bits/stdc++.h>
using namespace std;

int tongChuSo(int n)
{
	if(n < 10)
		return n;
	else return n%10 + tongChuSo(n/10);
}

int tong(int n)
{
	int tong = 0;
	while(n != 0){
		tong += n%10;
		n = n/10;
	}
	return tong;
}

int main()
{
	int n;

	cout << "=================MENU================\n";
	cout << "Phim 1: Tinh tong cac chu so bang phuong phap de quy\n";
	cout << "Phim 2: Tinh tong cac chu so bang phuong phap lap\n";
	cout << "=====================================\n";
	
	cout<<"Nhap so nguyen n: ";
	cin>>n;
	int chon;
	cout<<"Nhap lua chon: ";
	cin>>chon;
	switch (chon)
	{
	case 1:		
		cout<<"Tong cac chu so cua "<<n<<" la: "<<tongChuSo(n)<<endl;
		break;
	case 2:
		cout<<"Tong cac chu so cua "<<n<<" la: "<<tong(n);	
		break;
	default:
    {
        cout << "Thoat!!!\n";
		exit(1);
		break;
    }
	}
	return 0;
	



}