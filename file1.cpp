#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(vector<vector<char>> &board)
{
    for (int i = 0; i < SIDE; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < SIDE; j++)
        {
            if (j == SIDE - 1)
            {
                cout << board[i][j];
                continue;
            }
            cout << board[i][j] << " | ";
        }
        cout << "\n";
        if (i != SIDE - 1)
            cout << "\t\t\t--| --| -- \n";
    }
    cout << "\n";
}

void showInstructions()
{
    cout << "\nChoose a number from 1 to 9 as below and play\n\n";
    int count = 1;
    for (int i = 0; i < SIDE; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < SIDE; j++)
        {
            if (j == SIDE - 1)
            {
                cout << count;
                count++;
                continue;
            }
            cout << count << " | ";
            count++;
        }
        cout << "\n";
        if (i != SIDE - 1)
            cout << "\t\t\t--| --| -- \n";
    }
    cout << "\n";
}

void declareWinner(int whoseTurn,string playerName)
{
    if (whoseTurn == COMPUTER)
    {
        cout << "Computer has won the game. \n";
    }
    else
    {
        cout <<playerName<< "has won\n";
    }
}

bool rowFulfilled(vector<vector<char>> &board)
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
        {
            return true;
        }
    }
    return false;
}

bool columnFullfilled(vector<vector<char>> &board)
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
        {
            return true;
        }
    }
    return false;
}

bool diagonalFullfilled(vector<vector<char>> &board)
{
    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != '*'))
    {
        return true;
    }
    if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && (board[0][2] != '*'))
    {
        return true;
    }
    return false;
}

bool gameOver(vector<vector<char>> &board)
{
    return (rowFulfilled(board) || columnFullfilled(board) || diagonalFullfilled(board));
}

int minimax(vector<vector<char>> &board, int depth, bool isHuman)
{
    int score = 0;
    int bestscore = 0;
    if (gameOver(board) == true)
    {
        if (isHuman == true)
        {
            return -10;
        }
        if (isHuman == false)
        {
            return +10;
        }
    }
    if (depth < 9)
    {
        if (isHuman == true)
        {
            bestscore = INT_MIN;
            for (int i = 0; i < SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == '*')
                    {
                        board[i][j] = COMPUTERMOVE;
                        score = minimax(board, depth + 1, false);
                        board[i][j] = '*';
                        if (score > bestscore)
                        {
                            bestscore = score;
                        }
                    }
                }
            }
            return bestscore;
        }
        else
        {
            bestscore = INT_MAX;
            for (int i = 0; i < SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == '*')
                    {
                        board[i][j] = HUMANMOVE;
                        score = minimax(board, depth + 1, true);
                        board[i][j] = '*';
                        if (score < bestscore)
                        {
                            bestscore = score;
                        }
                    }
                }
            }
            return bestscore;
        }
    }

    else
        return 0;
}

int bestMove(vector<vector<char>> &board, int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestscore = INT_MIN;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestscore)
                {
                    bestscore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}

void playTicTacToe(int whoseTurn, string personName)
{
    vector<vector<char>> board(SIDE, vector<char>(SIDE, '*'));
    int moveIndex = 0, x = 0, y = 0;

    showInstructions();

    while (gameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "COMPUTER has put " << COMPUTERMOVE << " in cell " << n + 1 << endl
                 << endl;
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        }

        else if (whoseTurn == HUMAN)
        {
            cout << "You can insert in the following positions : ";
            for (int i = 0; i < SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == '*')
                    {
                        cout << (i * 3 + j) + 1 << " ";
                    }
                }
            }

            cout << "\n\nEnter the position: ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;

            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = HUMANMOVE;
                cout << personName << " has Put a " << HUMANMOVE << " in cell " << n + 1 << endl
                     << endl;
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            }
            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
                cout << "\nPosition is Pre-occupied,  select any other position. \n";
            }
            else if (n < 0 || n > 8)
            {
                cout << "Invalid position\n";
            }
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
    {
        cout << "It is a draw\n";
    }
    else
    {
        if (whoseTurn == COMPUTER)
        {
            whoseTurn = HUMAN;
        }
        else if (whoseTurn = HUMAN)
        {
            whoseTurn = COMPUTER;
        }
        declareWinner(whoseTurn,personName);
    }
}

int main()
{
    cout << "\n----------------------------------------------------\n\n";
    cout << "\t\t\tTic-Tac-Toe\n";
    cout << "\n----------------------------------------------------\n\n";

    char cont = 'y';
    do
    {
        string playerName;
        cout << "Enter name of the player: ";
        cin >> playerName;
        char choice;
        cout << "Do you want to start first?(y/n) :";
        cin >> choice;
        if (choice == 'n')
            playTicTacToe(COMPUTER, playerName);
        else if (choice == 'y')
            playTicTacToe(HUMAN, playerName);
        else
            cout << "Invalid Choice\n";

        cout << "Do you want to quit ?(y/n) :";
        cin >> cont;
    } while (cont == 'n');

    return 0;
}