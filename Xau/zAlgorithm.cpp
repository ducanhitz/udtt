#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;

struct HOCSINH
{
   string hoTen;
   int tuoi;
   float diemTK;
};
typedef struct HOCSINH HS;
//Cau 1: Tao danh sach 7 hoc sinh

HS d[7]={
   {"Vu Van Thanh",20,3.44},
   {"Nguyen Thuy Trang",29,3.0},
   {"Ngo Duc Trang",26,2.9},
   {"Dua Nay Gioi",23,3.87},
   {"Trang Ha Trang",21,3.36},
   {"Tran Duy Khanh",22,3.21},
   {"Thang Nay Ngu",25,2.3}
};
int n=7;
void outPutHS( HS x)
{
   cout<<left<<setw(30)<<x.hoTen;
   cout<<left<<setw(10)<<x.tuoi;
   cout<<left<<setw(10)<<x.diemTK<<endl;
}
void outPutList(HS x[], int n)
{
   for( int i=0;i<n;i++)
      outPutHS(x[i]);

}

// Thuật toán Z là thuật toán so khớp chuỗi, cũng giống với Boyer Moore Horspool
string P = "Trang";
int Z[100]{0};

void zAlgorithm(string S)
{
   int n = S.size();
   int l=0, r=0;
   for( int i=1;i<n;i++)
   {
      if( i > r)
      {
         l=r=i;
         while (r < n && S[r] == S[r-l])
            r++;
         Z[i] = r-l;
         r--;
      }
      else
      {
         int k =  i-l;
         if( Z[k] < r-i+1)
            Z[i] = Z[i-l];
         else
         {
            l=i;
            while ( r < n && S[r]==S[r-l] )
               r++;
            Z[i] = r-l;
            r--;   
         }
      }
   }
}

int checkName()
{
   int dem=0;// Bien dem so hoc sinh co cung ten.
   for( int i=0;i<n;i++)
   {
   string S = P +"*"+ d[i].hoTen;
   zAlgorithm(S);
   if(Z[S.size() - 5] == 5 && S[S.size() - 6] == 32 )
      dem++;
   }
   return dem;
}

int main()
{
   cout<<"\n =================Danh sach hoc sinh============="<<endl;
   // int n=7;
   outPutList(d,n);
   cout<<"\n================= Z Algorithm============="<<endl;
   int dem = checkName();
   cout<<" So hoc sinh co ten Trang la: "<<dem<<endl;
}