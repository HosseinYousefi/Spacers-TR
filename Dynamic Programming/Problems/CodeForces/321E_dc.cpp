#include <bits/stdc++.h>
using namespace std;

#define eprint(x) cerr << "[" << __LINE__ << "]\t" << #x " = " << (x) << endl
#ifndef LOCAL
#define cerr if (false) cerr
#endif

#define endl '\n'
using ll = long long;

const int N = 800;
const int M = 4000;
const int INF = 1e9;

int dp[N + 1][M + 1], c[M + 1][M + 1];

int cost(int k, int j) {
    return c[j][j] - c[j][k] - c[k][j] + c[k][k];
}

void compute(int i, int l, int r, int lb, int ub) {
    if (l > r) return;
    int m = (l + r) / 2;
    
    pair<int, int> best = {INF, lb};
    for (int k = lb; k <= min(ub, m - 1); k++)
        best = min(best, {dp[i - 1][k] + cost(k, m), k});
    
    dp[i][m] = best.first;
    int k = best.second;
    compute(i, l, m - 1, lb, k);
    compute(i, m + 1, r, k, ub);
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            while (ch = getchar(), !isdigit(ch));
            c[i][j] = (ch - '0') + c[i - 1][j] + c[i][j - 1] - c[i - 1][j - 1]; 
        }
    }
    for (int i = 1; i <= m; i++)
        dp[0][i] = INF;
    for (int i = 1; i <= n; i++)
        compute(i, 0, m, 0, m);
    cout << dp[n][m] / 2 << endl;
}