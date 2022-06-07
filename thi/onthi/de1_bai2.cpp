#include <iostream>
#include <string.h>

using namespace std;

char S[] = "Nguyen Van Van Duc Anh";
char P[] = "Van";

void z_algo(const char *t, int *z)
{
    int count = 0;
    int leng = strlen(t), l = 0, r = 0;
    for (int i = 1; i < leng; i++)
    {
        if (i > r)
        {
            l = r = i;
            while (r < leng && t[r - l] == t[r])
                r++;
            z[i] = r - l;
            r--;
        }
        else if (z[i - l] < r - i + 1)
            z[i] = z[i - l];
        else
        {
            l = i;
            while (r < leng && t[r - l] == t[r])
                r++;
            z[i] = r - l;
            r--;
        }
    }
}

int main()
{
    char t[200];

    strcpy(t, P);
    strcat(t, "$");
    strcat(t, S);

    int temp = strlen(t);
    int z[temp];
    z_algo(t, z);
    int count = 0;
    for (int i = 0; i < strlen(t); i++)
    {
        if (z[i] == strlen(P))
            count++;
    }
    cout << "So lan xuat hien chuoi \"" << P << "\": " << count << endl;
}