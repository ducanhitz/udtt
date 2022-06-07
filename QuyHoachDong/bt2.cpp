#include <iostream>

using namespace std;

int *Cur;
int *Next;


int analys02(int n)
{
    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= n; j++)
            if (j < i)
                Next[j] = Cur[j];
            else
                Next[j] = Cur[j] + Next[j-i];
        //memcpy(Next, Cur, n*sizeof(int));
        for(int i=0; i<n; i++)
        {
            Cur[i] = Next[i];
        }
    }
    return Cur[n];
}

int main()
{
    int n;
    
    cout << "Nhap n: ";
    cin >> n;
    Next = new int[n + 1];
    Cur = new int[n + 1];
    Cur[n+1] = {0};
    Cur[0] = 1;
    

    cout << analys02(n) << endl;

    return 0;
}
