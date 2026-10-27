#include <iostream>
#include <climits>
using namespace std;

void matrixChainMultiplication(int p[], int n) {
    int dp[n][n];

    // Cost of multiplying a single matrix is 0
    for (int i = 1; i < n; i++) {
        dp[i][i] = 0;
    }

    // len is the chain length
    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    cout << "Minimum number of multiplications: "
         << dp[1][n - 1] << endl;
}

int main() {
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    int p[n + 1];

    cout << "Enter dimensions array ("
         << n + 1 << " values): ";

    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    matrixChainMultiplication(p, n + 1);

    return 0;
}