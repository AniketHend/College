#include <bits/stdc++.h>
using namespace std;

#define N 15

char board[N][N];
int n;
int c = 0;

bool isSafe(int row, int col)
{
    for (int k = row - 1; k >= 0; k--)
    {
        if (board[k][col] == 'Q')
        {
            return false;
        }
    }

    for (int k = row - 1, l = col - 1; k >= 0 && l >= 0; k--, l--)
    {
        if (board[k][l] == 'Q')
        {
            return false;
        }
    }

    for (int k = row - 1, l = col + 1; k >= 0 && l < n; k--, l++)
    {
        if (board[k][l] == 'Q')
        {
            return false;
        }
    }
    return true;
}

void solve(int row)
{
    if (row >= n)
    {
        cout << "Solution :" << c + 1 << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        c++;
        if (c == 2)
            exit(0);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (isSafe(row, i))
        {
            board[row][i] = 'Q';
            solve(row + 1);
            board[row][i] = '.';
        }
    }
}

int main()
{
    cin >> n;
    if (n < 4)
    {
        cout << "NO SOLUTION EXISTS OF THE GIVEN DIMENSION OF BOARD\n";
        return 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            board[i][j] = '.';
        }
    solve(0);
    // cout<<c<<endl;
    return 0;
}

n = 13

Solution :1
Q . . . . . . . . . . . . 
. . Q . . . . . . . . . . 
. . . . Q . . . . . . . . 
. Q . . . . . . . . . . . 
. . . . . . . . Q . . . . 
. . . . . . . . . . . Q . 
. . . . . . . . . Q . . . 
. . . . . . . . . . . . Q 
. . . Q . . . . . . . . . 
. . . . . Q . . . . . . . 
. . . . . . . Q . . . . . 
. . . . . . . . . . Q . . 
. . . . . . Q . . . . . . 
Solution :2
Q . . . . . . . . . . . . 
. . Q . . . . . . . . . . 
. . . . Q . . . . . . . . 
. . . . . . Q . . . . . . 
. . . . . . . . Q . . . . 
. . . . . . . . . . Q . . 
. . . . . . . . . . . . Q 
. Q . . . . . . . . . . . 
. . . Q . . . . . . . . . 
. . . . . Q . . . . . . . 
. . . . . . . Q . . . . . 
. . . . . . . . . Q . . . 
. . . . . . . . . . . Q .

