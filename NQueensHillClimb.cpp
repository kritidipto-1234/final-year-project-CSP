#include<bits/stdc++.h>

using namespace std;

struct node //a position on the chess board
{
    int row;
    int column;
};

vector<int> state;//current state of board in array[row]=column format
vector<vector<int>> board;//actual board
vector<vector<int>> heuristicBoard;//heuristic value mapping for row wise queen movements
int n;//queen board size

int randomLessThanN(int n)//returns random number less than n
{
    srand(time(0));
    return rand()%n;
} 
//O(1)

void printCurrentBoard()//prints the current chess board
{
    for (int row=0;row<n;row++)
    {
        for(int column=0;column<n;column++)
            cout<<board[row][column]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
//O(n2)

void initializeBoardRandomly()//initializes the board with a random config
{
    for (int row=0;row<n;row++)
    {
        board[row][state[row]]=0;//clear queen from previous config state
        int column=randomLessThanN(n);//generates random number in the range 0 and n-1
        board[row][column]=1;
        state[row]=column;
    }
}
//O(n)

bool isValid(int row,int column)//checks if a particular position is inside the board
{
    return (0<=row && row<n && 0<=column && column<n); 
}
//O(1)

int conflictCountAtPos(int row,int column)//returns no of conflicts at current position
{
    int conflicts=0;
    vector<pair<int,int>> jump;
    for (int a:{-1,0,1})//initialize the different kinds of jumps
    {
        for (int b:{-1,0,1})
        {
            if (a==0 && b==0) continue;
            jump.push_back(make_pair(a,b));
        }
    }

    for (auto j:jump)
    {
        int x=row+j.first,y=column+j.second;
        while (isValid(x,y))
        {
            if (board[x][y]==1) conflicts++;
            x=x+j.first;
            y=y+j.second;
        }
    }

    return conflicts;
}
//O(n)

int calculateCurrentBoardHeuristic()//calculates heuristic of current board
{
    int conflicts=0;
    for (int row=0;row<n;row++)
    {
        conflicts+=conflictCountAtPos(row,state[row]);
    }

    return conflicts/2;//because we counted every pair twice
}
//O(n2)

void generateHeuristicBoard()
{
    for (int row=0;row<n;row++)
    {
        int prevColumn=state[row];
        for (int column=0;column<n;column++)//put this row queen in every column and generate heuristic
        {
            board[row][prevColumn]=0;
            board[row][column]=1;
            heuristicBoard[row][column]=calculateCurrentBoardHeuristic();
            prevColumn=column;
        }
        board[row][prevColumn]=0;
        board[row][state[row]]=1;//original board restored
    }
}
//O(n4)

node findSuccessor()//finds a relative with lesser conflicts/better heruistic
{
    int minRow=-1,minColumn=-1;    int current_heuristic=heuristicBoard[0][state[0]];
    for (int r=0;r<n;r++)
    {
        for (int c=0;c<n;c++)
        {
            if (board[r][c]==1) continue;//Only check neighbours
            if (minRow==-1 && minColumn==-1 && heuristicBoard[r][c]<current_heuristic)//initialize
            {
                minRow=r;
                minColumn=c;
                continue;
            }
            if (minRow!=-1 && minColumn!=-1 && heuristicBoard[r][c]<heuristicBoard[minRow][minColumn])
            {
                minRow=r;
                minColumn=c;
            }
        }
    }
    return {minRow,minColumn};
}
//O(n2)

void moveBoardTo(int row,int column)
{
    board[row][state[row]]=0;//remove previous queen from board
    state[row]=column;//change row state to new column
    board[row][column]=1;//put queen in new column
}
//O(1)

void hillClimb()
{
    initializeBoardRandomly();
    while (true)
    {
        generateHeuristicBoard();
        node successor=findSuccessor();
        if (successor.row==-1 && successor.column==-1)//we found a local minima
        {
            printCurrentBoard();
            return;
            // initializeBoardRandomly();
            // continue;
            // successor.row=randomLessThanN(n);
            // successor.column=randomLessThanN(n);
        }
        moveBoardTo(successor.row,successor.column);
    }
    printCurrentBoard();
}

int main()
{
    cin>>n;
    clock_t tStart = clock();
    vector<vector<int>> b(n,vector<int> (n,0));
    state=b[0];
    board=b;
    heuristicBoard=b;
    hillClimb();
    cout<<calculateCurrentBoardHeuristic()<<endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}
