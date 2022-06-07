#include<bits/stdc++.h>
using namespace std;
int a[1000][1000],n,result[1000][1000],ans =0;
void print(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<result[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n=============================================\n";
}
//void printA(){
//	for(int i=0;i<n;i++){
//		for(int j=0;j<n;j++){
//			cout<<a[i][j]<<" ";
//		}
//		cout<<"\n";
//	}
//	cout<<"\n=============================================\n";
//}
void datHau(int x,int y){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
//			if(i==x&&j==y)continue;
			if(i==y)a[i][j]++;
			else if(j==x)a[i][j]++;
			else if( i-y==j-x ) a[i][j]++;
			else if( y-i == j-x ) a[i][j]++;        
		}
	}
}
void xoaHau(int x,int y){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]==0)continue;
			if(i==y)a[i][j]--;
			else if(j==x)a[i][j]--;
			else if( i-y==j-x ) a[i][j]--;
			else if( y-i == j-x ) a[i][j]--;
		}
	}
}
int checkHang(int y){
	for(int i=0;i<n;i++){
		if(a[y][i]==0)return 1;
	}
	return 0;
}

void solve(int t,int x,int y){
	result[y][x]=1;
	datHau(x,y);
//	printA();
//	print();
	if(t==n){
		ans++;
		print();
		return;
	}
	if(checkHang(y+1)==0)return;
	for(int i=0;i<n;i++){
		if(a[y+1][i]==0){
			solve(t+1,i,y+1);
			result[y+1][i]=0;
			xoaHau(i,y+1);
//			printA();
			
		}
	}
}
int main(){
	n=8;
	for(int i=0;i<n;i++){
		solve(1,i,0);
		xoaHau(i,0);
		result[0][i]=0;
	}
	cout<<ans;
//	datHau(4,4);
//	printA();
}
