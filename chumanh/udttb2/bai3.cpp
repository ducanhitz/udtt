#include <iostream>

using namespace std;

string str[6] = {"tam", "toan", "trang", "cong", "trung", "tu"};

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void next_config(int x[], int n, int i)
{
    int k = n;
    while (x[k] < x[i])
        k--;
    swap(x[i], x[k]);
    int j = n;
    i++;
    while (i < j)
    {
        swap(x[i], x[j]);
        i++;
        j--;
    }
}

void display_config(int x[], int k)
{
    for (int i = 1; i <= k; i++)
        cout << str[x[i] - 1] << " ";
    cout << "\n";

}

void listing_configs(int n)
{
    int i, x[n + 1];
    for (int i = 1; i <= n; i++)
        x[i] = i;
    do
    {
        display_config(x, n);
        i = n - 1;

        while (i > 0 && x[i] > x[i + 1])
            i--;

        if (i > 0)
        {
            next_config(x, n, i);
        }
    } while (i > 0);
}

int main()
{
    listing_configs(6);
}