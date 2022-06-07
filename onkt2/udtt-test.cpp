
#include <iostream>
#include <string>

using namespace std;



struct HocSinh
{
    string maHS;
    string tenHS;
    float diem;
};

int n = 7;
HocSinh H[7];

string Ma[7] = {"HS001", "HS002", "HS003", "HS004", "HS005", "HS006", "HS007"};
string Ten[7] = {
    "Nguyen Van A",
    "Nguyen Van B",
    "Nguyen Van C",
    "Nguyen Van D",
    "Nguyen Van E",
    "Nguyen Van F",
    "Nguyen Van G"};

float Diem[7] = {7, 9.5, 9, 9.5, 4, 7, 9};

void nhapHS(HocSinh H[])
{
    for (int i = 0; i < 7; i++)
    {
        H[i].maHS = Ma[i];
        H[i].tenHS = Ten[i];
        H[i].diem = Diem[i];
    }
}

int Xuat(HocSinh  H[], int n, int i = 0)
{
    if (i == n)
        return 0;
    cout << "\nThong Tin Hoc Sinh: " << i + 1;
    cout << "\nMa hoc sinh: " << i + 1 << "\t" << H[i].maHS;
    cout << "\nTen hoc sinh :" << H[i].tenHS;
    cout << "\nDiem tong ket :" << H[i].diem;
    return Xuat(H, n, i + 1);
}

void SearchMax(HocSinh H[], int l, int r, float &max)
{
    float max1, max2;
    if (l == r)
    {
        max = H[l].diem;
    }
    else
    {
        int mid = (l + r) / 2;
        max1 = l;
        max = mid + 1;
        SearchMax(H, l, mid, max1);
        SearchMax(H, mid + 1, r, max2);
        if (max1 > max2)
        {
            max = max1;
        }
        else
        {
            max = max2;
        }
    }
}
//Xau con chung
char xc[12];
int L[12][12];
int algo(string A, string B)
{
    int m = A.length(), n = B.length();
    for (int i = 0; i <= m; i++)
        L[i][0] = 0;
    for (int j = 0; j <= n; j++)
        L[0][j] = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
    return L[m][n];
}

void Xau_con(string A, string B)
{
    int i = A.length(), j = B.length(), k = 0;
    while (L[i][j] != 0)
    {
        if (A[i - 1] == B[j - 1])
        {
            xc[k] = A[i - 1];
            k++;
            i--;
            j--;
        }
        else
        {
            if (L[i - 1][j] > L[i][j - 1])
                i--;
            else
                j--;
        }
    }
    xc[k] = '\0';
    strrev(xc);
}

int main()
{
    
    nhapHS(H);
    Xuat(H, n, 0);
    cout << "------------------------" << endl;
    //
    float Max=H[0].diem;
    SearchMax(H, 0, n, Max);
    cout << "\nDanh sach hoc sinh diem cao nhat = "<<Max<<endl;
    for (int i = 0; i < n; i++)
        if(H[i].diem == Max)
        {
            cout << "\nMa hoc sinh: " << H[i].maHS;
            cout << "\nTen hoc sinh: " << H[i].tenHS;
            cout << "\nDiem tong ket: " << H[i].diem;
        }
    //
    cout <<"------------------------"<<endl;
    cout << "Do dai xau con lon nhat: " << algo(H[0].tenHS, H[n].tenHS) << endl;
    Xau_con(H[0].tenHS, H[n].tenHS);
    cout << "Xau con chung lon nhat: " << xc << endl;



    return 0;
}