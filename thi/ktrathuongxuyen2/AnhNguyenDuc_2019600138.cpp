#include <iostream>

using namespace std;

string hotenGV[7] = {"Nguyen Van A", "Nguyen Thi", "Nguyen Van C", "Nguyen Thi D", "Nguyen E", "Nguyen Van F", "Nguyen Van G"};
int soHS[7] = {15, 17, 38, 3, 20, 25, 26};
int soHSNu[7] = {10, 17, 18, 1, 16, 20, 19};
int phuCap[7] = {100, 200, 400, 300, 50, 600, 350};

struct LopHoc
{
    string hotenGV;
    int soHS;
    int soHSNu;
    int phuCap;
};

void NhapLH(LopHoc lh[])
{
    for (int i = 0; i < 7; i++)
    {
        lh[i].hotenGV = hotenGV[i];
        lh[i].soHS = soHS[i];
        lh[i].soHSNu = soHSNu[i];
        lh[i].phuCap = phuCap[i];
    }
}

void TimGiaoVien(LopHoc lh[], int l, int r, LopHoc &minlh)
{
    LopHoc minl, minr;
    if (l == r)
    {
        minlh.hotenGV = lh[l].hotenGV;
        minlh.soHS = lh[l].soHS;
        minlh.soHSNu = lh[l].soHSNu;
    }
    else
    {
        int mid = (l + r) / 2;
        TimGiaoVien(lh, l, mid, minl);
        TimGiaoVien(lh, mid + 1, r, minr);
        if (minl.soHS - minl.soHSNu == 0)
        {
            minlh.hotenGV = minl.hotenGV;
            minlh.soHS = minl.soHS;
            minlh.soHSNu = minl.soHSNu;
        }
        else
        {
            minlh.hotenGV = minr.hotenGV;
            minlh.soHS = minr.soHS;
            minlh.soHSNu = minr.soHSNu;
        }
    }
}

int F[7][21];

void Algorithm(LopHoc lh[], int m)
{
    for (int i = 0; i <= m; i++)
        F[0][i] = 0;
    for (int i = 1; i <= 7; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            F[i][j] = F[i - 1][j];
            int temp = F[i - 1][j - lh[i].soHS] + lh[i].soHSNu;
            if (lh[i].soHS <= j && F[i][j] < temp)
                F[i][j] = temp;
        }
    }
}

void KetQua(LopHoc lh[], int m)
{
    int i = 7, j = m;
    cout << "Cac lop cua cac giao vien sau de tong so hoc sinh khong vuot qua " << m << " va so HS nu nhieu nhat la: " << endl;
    while (i != 0)
    {
        if (F[i][j] != F[i - 1][j])
        {
            cout << lh[i].hotenGV << " " << lh[i].soHS << " " << lh[i].soHSNu << " " << lh[i].phuCap << endl;
            j = j - lh[i].soHS;
        }
        i--;
    }
    cout << endl;
}

void z_algorithm(string s, int z[])
{
    int n = s.length(), l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i > r)
        {
            l = r = i;
            while (r < n && s[r - l] == s[r])
                r++;
            z[i] = r - l;
            r--;
        }
        else if (z[i - l] < r - i + 1)
            z[i] = z[i - l];
        else
        {
            l = i;
            while (r < n && s[r - l] == s[r])
                r++;
            z[i] = r - l;
            r--;
        }
    }
}

int DemKhoangTrang(string s)
{
    int count = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
            count++;
    }
    return count;
}

void DemTenThi(LopHoc lh[])
{
    cout << "Cac giao vien co ho dem la \"Thi\": " << endl;
    for (int i = 0; i < 7; i++)
    {
        string s;
        s = "Thi$" + lh[i].hotenGV;
        int z[s.length()];
        z_algorithm(s, z);
        if (DemKhoangTrang(lh[i].hotenGV) >= 2)
        {
            for (int j = 1; j < s.length(); j++)
                if (z[j] != 0)
                {
                    cout << lh[i].hotenGV << " " << lh[i].soHS << " " << lh[i].soHSNu << " " << lh[i].phuCap << endl;
                }
        }
    }
}

int main()
{
    LopHoc lh[7];

    NhapLH(lh);
    cout << "Danh sach lop hoc la: " << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << lh[i].hotenGV << " " << lh[i].soHS << " " << lh[i].soHSNu << " " << lh[i].phuCap << endl;
    }

    LopHoc lh_temp;
    TimGiaoVien(lh, 0, 6, lh_temp);
    cout << "Giao vien phu trach lop hoc khong co hoc sinh nam la: " << lh_temp.hotenGV << endl;

    int m = 20;
    Algorithm(lh, m);
    KetQua(lh, m);

    DemTenThi(lh);

    return 0;
}