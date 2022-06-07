#include <iostream>
using namespace std;

//Number of queens
int a, b, N;

//chessboard
int board[100][100];

void Show()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 1)
                cout << board[i][j] << "    ";
            else
                cout << "*"
                     << "    ";
        }
        cout << endl;
    }
}

//function to check if the cell is attacked or not
int is_attack(int x, int y)
{
    for (int i = 0; i < N; i++)
    {
        if ((board[x][i] == 1) || (board[i][y] == 1))
            return 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (((i + j) == (x + y)) || ((i - j) == (x - y)))
            {
                if (board[i][j] == 1)
                    return 1;
            }
        }
    }
    return 0;
}

int Try(int k)
{
    
    if (k == N+1){
        Show();
        return 1;
    }
    

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((!is_attack(i, j)) && (board[i][j] != 1))
            {
                board[i][j] = 1;
                if (Try(k + 1) == 1)
                    return 1;
                board[i][j] = 0;
            }
        }
    }
    return 0;
}

int main()
{
    cout << "Nhap N cho ban co NxN o: ";
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }

    Try(1);
}