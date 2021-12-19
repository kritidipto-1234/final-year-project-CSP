#include<bits/stdc++.h>

using namespace std;
 
#define N 40

void configureRandomly(int board[][N],int* state)//configures the 2D array "board" and array "state" randomly to provide a starting point for the algorithm.
{
    srand(time(0));
    for (int i = 0; i < N; i++) 
    { 
        state[i] = rand() % N;
        board[state[i]][i] = 1;
    }
}
 
void printBoard(int board[][N])//prints the 2D array "board".
{
    for (int i = 0; i < N; i++) 
    {
        cout << " ";
        for (int j = 0; j < N; j++) 
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

bool compareStates(int* state1,int* state2)//compares two arrays, state1 and state2 and returns true if equal and false otherwise.
{ 
    for (int i = 0; i < N; i++) 
    {
        if (state1[i] != state2[i]) 
        {
            return false;
        }
    }
    return true;
}
 
void fill(int board[][N], int value)//fills the 2D array "board" with values "value"
{
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            board[i][j] = value;
        }
    }
}

int calculateObjective(int board[][N],int* state)// This function calculates the objective value of the state(queens attacking each other) using the board
{
    // For each queen in a column, we check for other queens falling in the line of our current queen and if found,any, then we increment the variable attacking count.

    int attacking = 0;// Number of queens attacking each other,initially zero.
    int row, col;// Variables to index a particular row and column on board.
 
    for (int i = 0; i < N; i++) 
    {
        // At each column 'i', the queen is placed at row 'state[i]', by the definition of our state.
        // To the left of same row (row remains constant and col decreases)
        row = state[i], col = i - 1;
        while (col >= 0 && board[row][col] != 1) 
        {
            col--;
        }
        if (col >= 0 && board[row][col] == 1) 
        {
            attacking++;
        }
 
        row = state[i], col = i + 1;// To the right of same row (row remains constant and col increases)
        while (col < N && board[row][col] != 1) 
        {
            col++;
        }
        if (col < N && board[row][col] == 1) 
        {
            attacking++;
        }
 
        // Diagonally to the left up (row and col simultaneously decrease)
        row = state[i] - 1, col = i - 1;
        while (col >= 0 && row >= 0 && board[row][col] != 1) 
        {
            col--;
            row--;
        }
        if (col >= 0 && row >= 0 && board[row][col] == 1) {
            attacking++;
        }
 
        // Diagonally to the right down (row and col simultaneously increase)
        row = state[i] + 1, col = i + 1;
        while (col < N && row < N && board[row][col] != 1) 
        {
            col++;
            row++;
        }
        if (col < N && row < N && board[row][col] == 1) 
        {
            attacking++;
        }
 
        // Diagonally to the left down (col decreases and row increases)
        row = state[i] + 1, col = i - 1;
        while (col >= 0 && row < N && board[row][col] != 1) 
        {
            col--;
            row++;
        }
        if (col >= 0 && row < N && board[row][col] == 1) 
        {
            attacking++;
        }
 
        // Diagonally to the right up (col increases and row decreases)
        row = state[i] - 1, col = i + 1;
        while (col < N && row >= 0 && board[row][col] != 1) 
        {
            col++;
            row--;
        }
        if (col < N && row >= 0 && board[row][col] == 1) 
        {
            attacking++;
        }
    }
 
    return (int)(attacking / 2);// Return pairs.
}

void generateBoard(int board[][N],int* state)//generates a board configuration given the state.
{
    fill(board, 0);
    for (int i = 0; i < N; i++) 
    {
        board[state[i]][i] = 1;
    }
}

void copyState(int* state1, int* state2)//copies contents of state2 to state1.
{
    for (int i = 0; i < N; i++) 
    {
        state1[i] = state2[i];
    }
}

void getNeighbour(int board[][N],int* state)//gets the neighbour of the current state having the least objective value amongst all neighbours as well as the current state.
{
    // Declaring and initializing the optimal board and state with the current board and the state as the starting point. 
    int opBoard[N][N];
    int opState[N];
 
    copyState(opState,state);
    generateBoard(opBoard,opState);
 
    // Initializing the optimal objective value
 
    int opObjective= calculateObjective(opBoard,opState);
 
    // Declaring and initializing the temporary board and state for the purpose of computation.
 
    int NeighbourBoard[N][N];
    int NeighbourState[N];
 
    copyState(NeighbourState,state);
    generateBoard(NeighbourBoard,NeighbourState);
 
    // Iterating through all possible neighbours of the board.
 
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            // Condition for skipping the current state
            if (j != state[i]) 
            {
                // Initializing temporary neighbour with the current neighbour.
                NeighbourState[i] = j;
                NeighbourBoard[NeighbourState[i]][i] = 1;
                NeighbourBoard[state[i]][i] = 0;
 
                // Calculating the objective value of the neighbour.
 
                int temp = calculateObjective(NeighbourBoard,NeighbourState);
 
                // Comparing temporary and optimal neighbour objectives and if temporary is less than optimal then updating accordingly.
 
                if (temp <= opObjective) 
                {
                    opObjective = temp;
                    copyState(opState,NeighbourState);
                    generateBoard(opBoard,opState);
                }
 
                // Going back to the original configuration for the next iteration.
 
                NeighbourBoard[NeighbourState[i]][i] = 0;
                NeighbourState[i] = state[i];
                NeighbourBoard[state[i]][i] = 1;
            }
        }
    }
 
    // Copying the optimal board and state thus found to the current board and, state since c++ doesn't allow returning multiple values.
    copyState(state, opState);
    fill(board, 0);
    generateBoard(board, state);
}

void hillClimbing(int board[][N],int* state)
{
    int neighbourBoard[N][N] = {};int neighbourState[N];// Declaring  and initializing the neighbour board and state with the current board and the state as the starting point.
    copyState(neighbourState, state);
    generateBoard(neighbourBoard,neighbourState);

    do 
    {
        copyState(state, neighbourState);// Copying the neighbour board and state to the current board and state, since a neighbour becomes current after the jump.
        generateBoard(board, state);
        getNeighbour(neighbourBoard,neighbourState);// Getting the optimal neighbour

        if (compareStates(state,neighbourState)) 
        {
            // If neighbour and current are equal then no optimal neighbour exists and therefore output the result and break the loop.
            printBoard(board);
            break;
        }
        else if (calculateObjective(board,state) == calculateObjective(neighbourBoard,neighbourState)) 
        {
            // If neighbour and current are not equal but their objectives are equal then we are either approaching a shoulder or a local optimum, in any case, jump to a random neighbour to escape it.
            // Random neighbour
            neighbourState[rand() % N]= rand() % N;
            generateBoard(neighbourBoard,neighbourState);
        }
    } 
    while (true);
}

int main()
{
    clock_t tStart = clock();
    int state[N] = {};
    int board[N][N] = {};
    configureRandomly(board, state);
    hillClimbing(board, state);
    cout<<calculateObjective(board,state)<<endl;
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}