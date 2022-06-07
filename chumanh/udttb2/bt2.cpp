#include <bits/stdc++.h>
using namespace std;

int SoMien=0;
/*

*/
		
int a[12][12];			
bool flag[12][12]={false};

void loang( int i, int j)
{
   flag [i][j]=true;
   if(a[i-1][j] == a[i][j] && !flag[i-1][j] && i>0)
      loang(i-1,j);
   
   if(a[i+1][j] == a[i][j] && !flag[i+1][j] &&i<11)
      loang(i+1,j);
   
   if(a[i][j-1] == a[i][j] && !flag[i][j-1]  && j>0 )
      loang(i,j-1);
   
   if(a[i][j+1] == a[i][j] && !flag[i][j+1] && j<11)
      loang(i,j+1);
      
}

int main()
{
	
	
	srand(time(NULL));
	for(int i=0;i<12;i++)
		for(int j=0;j<12;j++)
		a[i][j]	= rand() % 6;	
	
	for(int i=0;i<12;i++){
		for(int j=0;j<12;j++)
    		cout<<a[i][j]<<" ";
		cout<<endl;
	}
	
	
   for(int i=0;i<12;i++)
      for(int j=0;j<12;j++)
         if(!flag[i][j] && a[i][j] == 5)
         { 
            SoMien++;
            loang(i,j);
         }
    cout<<"\n\n";
	for(int i=0;i<12;i++){
		for(int j=0;j<12;j++)
    		cout<<flag[i][j]<<" ";
		cout<<endl;
	}
	
   cout<<"\nSo mien lien thong la :"<<SoMien<<endl;

}