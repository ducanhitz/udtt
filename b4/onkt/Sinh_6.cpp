#include <iostream>
#include <string>

using namespace std;

string str[6] = {"tam", "toan", "trang", "cong", "trung", "tu"};
void view_config(int x[], int k)
{
    for (int i = 1; i <= k; i++)
        cout << str[x[i] - 1] << " ";
    cout << "\n";
}
void next_config(int x[], int k, int i)
{
    x[i]++;
    i++;
    while (i <= k)
    {
        x[i] = x[i - 1] + 1;
        i++;
    }
}

void listing_configs(int k, int n)
{
    int i, x[k + 1];
    //Cau hinh dau tien {1 2 … k}
    for (i = 1; i <= k; i++)
    {
        x[i] = i;
    }
    do
    {

        view_config(x, k); //In m?t c?u hình
        //Tim phan tu dau tien chua dat gh tren
        i = k;
        while (i > 0 && x[i] == n - k + i)
            i--;
        if (i > 0)
        { //Chua phai cau hinh cuoi
            next_config(x, k, i);
        }
    } while (i > 0);
}

int main()
{
    listing_configs(4, 6);
}