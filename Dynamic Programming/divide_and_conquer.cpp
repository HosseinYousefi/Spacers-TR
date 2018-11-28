const int N = 1000;
const int M = 1000;
const int INF = 1e9;

int dp[N + 1][M + 1];

int cost(int k, int j) {
    return 0;
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