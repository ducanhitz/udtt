#include <iostream>

using namespace std;

struct sv
{
    char maSV[10];
    char tenSV[32];
    float diem;
};


void nhapsv(sv L[], int n)
{
    cout<<"Nhap thong tin cac sinh vien"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"\nNhap thong tin sinh vien "<<i+1<<endl;
        cout<<"Nhap ma SV: ";
        fflush(stdin);
        cin.getline(L[i].maSV, 10);
        cout << "Nhap ten SV: ";
        fflush(stdin);
        cin.getline(L[i].tenSV, 32);
        cout << "Nhap diem SV: ";
        cin>>L[i].diem;
    }
}

void hienthisv(sv L[], int n)
{
    cout << "Thong tin cac sinh vien" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << L[i].maSV << "  " << L[i].tenSV <<"  "<< L[i].diem<<endl;
    }
}

void view_config(int x[], int k, sv L[])
{
    for (int i = 1; i <= k; i++)
        cout << L[x[i] - 1].maSV << "  " << L[x[i] - 1].tenSV << "  " << L[x[i] - 1].diem << endl;
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

void listing_configs(int k, int n, sv L[])
{
    int i, x[k + 1];
    // Cau hinh dau tien {1 2 … k}
    for (i = 1; i <= k; i++)
    {
        x[i] = i;
    }
    do
    {

        view_config(x, k, L); // In mot cau hình
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
    sv L[100];
    int k, n;
    cout<<"Nhap so luong SV: ";
    cin>>n;
    nhapsv(L, n);
    hienthisv(L, n);

    cout << "Nhap so luong SV muon lay: ";
    cin >> k;
    listing_configs(k, n, L);
    return 0;
}