#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

string a, b, globalAlignment_a, globalAlignment_b, localAlignment_a, localAlignment_b;
int match_score, mismatch_penalty, gap_penalty, n, m;

int globalAlignment(vector<vector<int>> &dp) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            if(i == 0 && j == 0) {
                dp[i][j] = 0;
            } else if(i == 0) {
                dp[i][j] = dp[i][j - 1] + gap_penalty;
            } else if(j == 0) {
                dp[i][j] = dp[i - 1][j] + gap_penalty;
            } else {
                int matchScore = (a[i - 1] == b[j - 1]) ? match_score : mismatch_penalty;
                int diagonal = dp[i - 1][j - 1] + matchScore;
                int up = dp[i - 1][j] + gap_penalty;
                int left = dp[i][j - 1] + gap_penalty;
                dp[i][j] = max({diagonal, up, left});
            }
        }

    }

    for(int i = n, j = m; i > 0 || j > 0; ) {
        if(i > 0 && j > 0  && dp[i][j] == dp[i - 1][j - 1] + ((a[i - 1] == b[j - 1]) ? match_score : mismatch_penalty)) {
            globalAlignment_a += a[i - 1];
            globalAlignment_b += b[j - 1];
            i--;
            j--;
        } else if(i > 0 && dp[i][j] == dp[i - 1][j] + gap_penalty) {
            globalAlignment_a += a[i - 1];
            globalAlignment_b += '-';
            i--;
        } else if(j > 0 && dp[i][j] == dp[i][j - 1] + gap_penalty) {
            globalAlignment_a += '-';
            globalAlignment_b += b[j - 1];
            j--;
        } else {
            if (i > 0) {
                globalAlignment_a += a[i - 1];
                globalAlignment_b += '-';
                i--;
            } else if (j > 0) {
                globalAlignment_a += '-';
                globalAlignment_b += b[j - 1];
                j--;
            }
        }
    }
    return dp[n][m];
}

int localAlignment(vector<vector<int>> &dp) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            if(i == 0 || j == 0) {
                dp[i][j] = 0;
            } else {
                int matchScore = (a[i - 1] == b[j - 1]) ? match_score : mismatch_penalty;
                dp[i][j] = max({dp[i - 1][j - 1] + matchScore, dp[i - 1][j] + gap_penalty, dp[i][j - 1] + gap_penalty, 0});

            }
        }
    }
    int maxScore = 0;
    int max_i = 0, max_j = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            maxScore = max(maxScore, dp[i][j]);
            if(dp[i][j] == maxScore) {
                max_i = i;
                max_j = j;
            }
        }
    }
    for(int i = max_i , j = max_j; i > 0 && j > 0; ) {
        if(dp[i][j] == dp[i - 1][j - 1] + ((a[i - 1] == b[j - 1]) ? match_score : mismatch_penalty)) {
            localAlignment_a += a[i - 1];
            localAlignment_b += b[j - 1];
            i--;
            j--;
        } else if(dp[i][j] == dp[i - 1][j] + gap_penalty) {
            localAlignment_a += a[i - 1];
            localAlignment_b += '-';
            i--;
        } else if(dp[i][j] == dp[i][j - 1] + gap_penalty) {
            localAlignment_a += '-';
            localAlignment_b += b[j - 1];
            j--;
        } else {
            break;
        }
    }
    return maxScore;
}

int main() {
    cout << "Enter first sequence: ";
    cin >> a;
    cout << "Enter second sequence: ";
    cin >> b;
    cout << "Enter match score: ";
    cin >> match_score;
    cout << "Enter mismatch penalty: ";
    cin >> mismatch_penalty;
    cout << "Enter gap penalty: ";
    cin >> gap_penalty;

    n = a.length();
    m = b.length();

    vector<vector<int>> dp1(n + 1, vector<int>(m + 1, 0));
    vector<vector<int>> dp2(n + 1, vector<int>(m + 1, 0));
    
    int globalScore = globalAlignment(dp1);
    int localScore = localAlignment(dp2);
    reverse(globalAlignment_a.begin(), globalAlignment_a.end());
    reverse(globalAlignment_b.begin(), globalAlignment_b.end());
    reverse(localAlignment_a.begin(), localAlignment_a.end());
    reverse(localAlignment_b.begin(), localAlignment_b.end());


    cout << "Global Alignment: " << endl;
    cout << globalAlignment_a << endl << globalAlignment_b << endl << endl;
    cout << "Maximum Score: " << globalScore << endl << endl;
    cout << "Local Alignment: " << endl;
    cout << localAlignment_a << endl << localAlignment_b << endl << endl;
    cout << "Maximum Score: " << localScore << endl;

    return 0;
}