#include <iostream>
#include <vector>
#include <limits>
using namespace std;

char checkWinner(const vector<char>& board) 
{
    int winLines[8][3] = 
    {
        {0,1,2},{3,4,5},{6,7,8}, 
        {0,3,6},{1,4,7},{2,5,8}, 
        {0,4,8},{2,4,6}         
    };
    for (auto &line : winLines) 
    {
        char a = board[line[0]], b = board[line[1]], c = board[line[2]];
        if (a != ' ' && a == b && b == c) return a;
    }
    return ' ';
}

bool isFull(const vector<char>& board) 
{
    for (char c : board) if (c == ' ') return false;
    return true;
}

int minimax(vector<char>& board, bool maximizingPlayer, char ai, char human, int alpha, int beta) 
{
    char winner = checkWinner(board);
    if (winner == ai) return 10;
    if (winner == human) return -10;
    if (isFull(board)) return 0;

    if (maximizingPlayer) 
    {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) 
        {
            if (board[i] == ' ') 
            {
                board[i] = ai;
                int score = minimax(board, false, ai, human, alpha, beta);
                board[i] = ' ';
                bestScore = max(bestScore, score);
                alpha = max(alpha, score);
                if (beta <= alpha) break; // pruning
            }
        }
        return bestScore;
    } 
    else 
    {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) 
        {
            if (board[i] == ' ') 
            {
                board[i] = human;
                int score = minimax(board, true, ai, human, alpha, beta);
                board[i] = ' ';
                bestScore = min(bestScore, score);
                beta = min(beta, score);
                if (beta <= alpha) break; // pruning
            }
        }
        return bestScore;
    }
}

int bestMove(vector<char>& board, char ai, char human) 
{
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) 
    {
        if (board[i] == ' ') 
        {
            board[i] = ai;
            int score = minimax(board, false, ai, human,
                                numeric_limits<int>::min(), numeric_limits<int>::max());
            board[i] = ' ';
            if (score > bestScore) 
            {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

void printBoard(const vector<char>& board) 
{
    cout << "\n";
    for (int i = 0; i < 9; i++) 
    {
        cout << " " << board[i] << " ";
        if (i % 3 != 2) cout << "|";
        else if (i != 8) cout << "\n-----------\n";
    }
    cout << "\n\n";
}

int main() 
{
    cout << "Welcome to Tic-Tac-Toe (Minimax with Alpha-Beta)\n";
    char choice;
    cout << "Would you like to start first? (y/n): ";
    cin >> choice;

    char human = (choice == 'y' || choice == 'Y') ? 'X' : 'O';
    char ai = (human == 'X') ? 'O' : 'X';

    vector<char> board(9, ' ');
    bool humanTurn = (human == 'X');

    printBoard(board);

    while (true) 
    {
        if (humanTurn) 
        {
            int move;
            cout << "Your move (1-9): ";
            cin >> move;
            move--; // 0-based
            if (move >= 0 && move < 9 && board[move] == ' ') 
            {
                board[move] = human;
                humanTurn = false;
            } 
            else 
            {
                cout << "Invalid move. Try again.\n";
                continue;
            }
        } 
        
        else 
        {
            int move = bestMove(board, ai, human);
            cout << "AI chooses square " << (move+1) << "\n";
            board[move] = ai;
            humanTurn = true;
        }

        printBoard(board);

        char winner = checkWinner(board);
        if (winner == human) 
        {
            cout << "You (" << human << ") win!\n";
            break;
        } 
        
        else if (winner == ai) 
        {
            cout << "AI (" << ai << ") wins!\n";
            break;
        } 
        
        else if (isFull(board)) 
        {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}
