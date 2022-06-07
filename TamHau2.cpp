#include<bits/stdc++.h>
using namespace std;
int x[9], a[9], b[15], c[15];
void Try(int k, int &suc) {
	int j = 0;
   	do {
   		j++;
      	suc = 0;
      	if (a[j] && b[k + j - 2] && c[k - j + 7]) {
      		x[k] = j;
        	a[j] = 0; b[k + j - 2] = 0; c[k - j + 7] = 0;
         	if (k < 8) {
         	Try(k + 1, suc);
            if (!suc) {
               a[j] = 1; b[k + j - 2] = 1; c[k - j + 7] = 1;
            }
         }
      	else suc = 1;
      }
   }while (!suc && j < 8);
}
int main() {
	int i, suc;
   	for (i = 1; i <= 8; i++)  a[i] = 1;
    for (i = 0; i <= 14; i++) b[i] = 1;
   	for (i = 0; i <= 14; i++) c[i] = 1;
   	Try(1, suc);
   	if (suc) 
		for (i = 1; i <= 8; i++)
      		cout<<"Hang "<<i<<" cot "<<x[i]<<endl;
   else cout<<"Khong dat duoc...!";
}

