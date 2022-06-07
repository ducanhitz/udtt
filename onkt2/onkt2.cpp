
#include <iostream>
#include <string>

using namespace std;

int F[10][20];


struct GoiHang
{
    string maGH;
    float khoiluong;
    float giaTien;
};

string GH[7] = {"GH001", "GH002", "GH003", "GH004", "GH005", "GH006", "GH007"};
int KL[7] = {10, 20, 15, 30, 5, 60, 45};
int GT[7] = {1000, 2000, 3000, 1300, 2100, 4200, 2200};

void nhapHang(GoiHang H[])
{
    for (int i = 0; i < 7; i++)
    {
        H[i].maGH = GH[i];
        H[i].khoiluong = KL[i];
        H[i].giaTien = GT[i];
    }
}

int Xuat(GoiHang *a, int n, int i = 0)
{
    if (i == n)
        return 0;
    cout << "\nThong Tin Goi Hang: " << i + 1;
    cout << "\nMa goi hang: " << i + 1 << "\t" << a[i].maGH;
    cout << "\nKhoi luong :" << a[i].khoiluong;
    cout << "\nGia tien :" << a[i].giaTien;
    return Xuat(a, n, i + 1);
}

int binarySearch(GoiHang H[], int l, int r, string x)
{
    if (r >= l)
    {
        int mid = (l+r) / 2;
        if (H[mid].maGH.compare(x) == 0)
            return mid;
        if (H[mid].maGH.compare(x) > 0)
            return binarySearch(H, l, mid - 1, x);
        return binarySearch(H, mid + 1, r, x);
    }
    return -1;
}

void Search(GoiHang H[], int n)
{
    string x;
    cout<<"Nhap ma hang can tim: ";
    fflush(stdin);
    cin >> x;
    int kq = binarySearch(H, 0, n, x);
    if(kq == -1)
        cout<<"Ko co ...."<<endl;
    else
        cout<<"Goi hang "<<x<<" o vi tri "<<kq+1<<endl;
}

int char_in_string(char x, string a)
{
    for (int i = 0; i < a.length(); i++)
        if (a[i] == x)
            return i;
    return -1;
}

int Boyer_Moore_Horspool(string N, string M)
{
    int dem = 0, i = N.length() - 1, v = N.length();
    while (i < M.length())
    {
        int x = v - 1, j = i;
        while (M[j] == N[x] && x > -1)
        {
            j--;
            x--;
        }
        if (x < 0)
        {
            dem++;
            i = i + v;
        }
        else
        {
            int x = char_in_string(M[j], N);
            if (x < 0)
                i = i + v;
            else
                i = i + v - x - 1;
        }
    }
    return dem;
}



void algo(GoiHang H[], int n,  int m, int F[8][101])
{
    for (int i = 0; i <= m; i++)
    {
        F[0][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            F[i][j] = F[i - 1][j];
            int temp1 = j - H[i].giaTien; 
            int temp = F[i - 1][temp1] + H[i].khoiluong;
            if (H[i].giaTien <= j && F[i][j] < temp)
                F[i][j] = temp;
        }
    }
}

void result(GoiHang H[], int n, int m, int F[8][101])
{
    cout << "Max value = " << F[n][m] << endl;
    int i = n, j = m;
    while (i != 0)
    {
        if (F[i][j] != F[i - 1][j])
        {
            cout << i << " ";
            j = j - H[i].giaTien;
        }
        i--;
    }
}
int Boyer_Moore_Horspool_1(string N, string M)
{
    int dem = 0, i = N.length() - 1, v = N.length();
    while (i < M.length())
    {
        int x = v - 1, j = i;
        while (M[j] == N[x] && x > -1)
        {
            j--;
            x--;
        }
        if (x < 0)
        {
            dem++;
            i = i + v;
        }
        else
        {
            int x = char_in_string(M[j], N);
            if (x < 0)
                i = i + v;
            else
                i = i + v - x - 1;
        }
    }
    return dem;
}

void CheckMaGH(GoiHang gh[], int n)
{
    int dem = 0;
    for (int i = 0; i < n; i++)
        if (Boyer_Moore_Horspool_1("H00", gh[i].maGH) > 0)
        {
            dem++;
        }
    if (dem == n)
        cout << "H00 co trong tat ca cac ma goi hang" << endl;
}

int main()
{
    int n = 7, m=100;
    int F[8][101];
    GoiHang H[7];
    nhapHang(H);
    Xuat(H, n, 0);
    cout << endl;
    //Search(H,n);

    //c3
    //CheckMaGH(H, n);
    //c2
    cout << "Max value = " << F[n][m] << endl;
    int i = n, j = m;
    while (i != 0)
    {
        if (F[i][j] != F[i - 1][j])
        {
            cout << i << " ";
            j = j - H[i].giaTien;
        }
        i--;
    }

    return 0;
}