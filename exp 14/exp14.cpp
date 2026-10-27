#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[n], value[n];

    cout << "Enter weights of items: ";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter values of items: ";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> W;

    int dp[n + 1][W + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
        }
    }

    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    value[i - 1] +
                    dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum value: " << dp[n][W] << endl;

    // Find selected items
    cout << "Selected items: ";
    int w = W;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << i << " ";
            w -= weight[i - 1];
        }
    }

    cout << endl;
    return 0;
}