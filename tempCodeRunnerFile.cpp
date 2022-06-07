#include <iostream>

using namespace std;

struct SinhVien
{
    char maSV[10];
    char tenSV[32];
    float diem;
};

void nhapsv(SinhVien sv[], int n)
{
    cout << "Nhap thong tin cac sinh vien";
    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap thong tin sinh vien " << i + 1 << endl;
        cout << "Nhap ma SV: ";
        cin.ignore();
        cin.getline(sv[i].maSV, 10);
        cout << "Nhap ten SV: ";
        cin.ignore();
        cin.getline(sv[i].tenSV, 32);
        cout << "Nhap diem SV: ";
        cin >> sv[i].diem;
    }
}

void hienthisv(SinhVien sv[], int n)
{
    cout << "Thong tin cac sinh vien" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << sv[i].maSV << "  " << sv[i].tenSV << "  " << sv[i].diem << endl;
    }
}

void view_config(int x[], int k, SinhVien sv[])
{
    for (int i = 1; i <= k; i++)
        cout << sv[x[i] - 1].maSV << "  " << sv[x[i] - 1].tenSV << "  " << sv[x[i] - 1].diem << endl;
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

void listing_configs(int k, int n, SinhVien sv[])
{
    int i, x[k + 1];
    // Cau hinh dau tien {1 2 … k}
    for (i = 1; i <= k; i++)
    {
        x[i] = i;
    }
    do
    {

        view_config(x, k, sv); // In mot cau hình
        // Tim phan tu dau tien chua dat ghe tren
        i = k;
        while (i > 0 && x[i] == n - k + i)
            i--;
        if (i > 0)
        { // Chua phai cau hinh cuoi
            next_config(x, k, i);
        }
    } while (i > 0);
}

int main()
{
    SinhVien sv[100];
    int k, n;
    cout << "Nhap so luong SV: ";
    cin >> n;

    nhapsv(sv, n);
    hienthisv(sv, n);

    cout << "Nhap so luong SV muon lay: ";
    cin >> k;
    cout << "Cac cach chon sinh vien la: " << endl;
    listing_configs(k, n, sv);
    return 0;
}