#include<bits/stdc++.h>
using namespace std;

void placeQueen(int row);

int n;
vector<vector<int>> board;

void printvv(vector<vector<int>> &board)
{
    for (auto v:board)
    {
        for (auto i:v)
            cout<<i<<" ";
        cout<<endl;
    }
    cout<<endl;
}

bool isValid(int row,int column)
{
    return (0<=row && row<n && 0<=column && column<n); 
}

bool isAttacking(int row,int column)
{
    vector<pair<int,int>> jump={{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};
    for (auto p:jump)
    {
        int x=row+p.first,y=column+p.second;
        while (isValid(x,y))
        {
            if (board[x][y]==1) return true;
            x=x+p.first;
            y=y+p.second;
        }
    }
    return false;
}

int findNextPlaceForQueen(int row)
{
    for (int c=0;c<n;c++)// search for queens place in this row
    {
        if (board[row][c]==0 && !isAttacking(row,c))
        {
            return c;
        }   
        if (board[row][c]==1) board[row][c]=0; 
    }

    return -1;
}

void undo(int row)
{
    for (int i=0;i<n;i++)
        board[row][i]=0;
    placeQueen(row-1);
}

void placeQueen(int row=0)
{
    if (row==-1) return; //end search
    int column=findNextPlaceForQueen(row);
    if (column==-1)//no positions left for this row
    {
        undo(row);
        return;
    }
    board[row][column]=1;// place queen here

    if (row==n-1)  //success
    {
        // undo(row);
        printvv(board);
        return;
    }
    placeQueen(row+1);
}

int main()
{
    cin>>n;
    vector<int> sample(n,0);
    for (int i=1;i<=n;i++)
        board.push_back(sample);
    placeQueen();
}