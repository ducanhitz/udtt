#include<iostream>
#include<cstring>
using namespace std;

char T[] = "Huy khong thich Toyota";
char P[] = "Toyota";
void z_algo(const char *s, int *z) {
   int n = strlen(s), l = 0, r = 0;
   for (int i = 1; i < n; i++) {
      if (i > r) {
         l = r = i;
         while (r < n && s[r - l]== s[r]) r++;
            z[i] = r - l; r --;
      }
      else if (z[i - l] < r - i + 1)
         z[i] = z[i-l];
         else { l = i;
         while (r < n && s[r - l] == s[r]) r ++;
            z[i] = r - l; r --;
         }
   }
}

int main()
{
   char s[] = "Toyota$Huy khong thich Toyota";
   int z[29];
   z_algo(s,z);
   for (int i = 0; i < 29; i++)
   {
      if(z[i] == strlen(P))
         // cout<<z[i]<<"  ";
         cout<< i - strlen(P)<<" ";

   }
   
   

}