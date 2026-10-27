#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> board;

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column
        if (board[i] == col)
            return false;

        // Check diagonals
        if (abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

bool solveNQueens(int row) {
    if (row == n)
        return true;

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;

            if (solveNQueens(row + 1))
                return true;

            // Backtrack
            board[row] = -1;
        }
    }

    return false;
}

int main() {
    cout << "Enter the value of N: ";
    cin >> n;

    if (n <= 0) {
        cout << "N must be positive." << endl;
        return 0;
    }

    board.assign(n, -1);

    if (solveNQueens(0)) {
        cout << "Solution for " << n << "-Queens problem:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i] == j)
                    cout << "Q ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists for N = " << n << endl;
    }

    return 0;
}
