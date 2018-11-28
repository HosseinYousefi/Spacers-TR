#include <bits/stdc++.h>
using namespace std;

#define eprint(x) cerr << "[" << __LINE__ << "]\t" << #x " = " << (x) << endl
#ifndef LOCAL
#define cerr if (false) cerr
#endif

#define endl '\n'
using ll = long long;

const int N = 100;
const int M = 2e5;
const ll INF = 1e18;

ll dp[2][M + 1], c[M + 1];

ll cost(int k, int j) {
    return (c[j] - c[k]) + (j - k) * 1ll * k;
}

void compute(int l, int r, int lb, int ub) {
    if (l > r) return;
    int m = (l + r) / 2;
    
    pair<ll, int> best = {0, lb};
    for (int k = lb; k <= min(ub, m - 1); k++)
        best = max(best, {dp[0][k] + cost(k, m), k});
    
    dp[1][m] = best.first;
    int k = best.second;
    compute(l, m - 1, lb, k);
    compute(m + 1, r, k, ub);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    int holes = 0;
    ll ans = 0;
    vector<int> cnt(k + 1);
    for (int j = 0; j < n; j++) {
        cin >> a[j];
        if (a[j] == 0) {
            holes++;
        } else {
            for (int i = a[j] + 1; i <= k; i++)
                ans += cnt[i];
        }
        cnt[a[j]]++;
    }
    
    for (int jj = 1; jj <= holes; jj++)
        dp[0][jj] = -INF;
    for (int i = k; i >= 1; i--) {
        for (int j = 0, jj = 1, cur = 0; j < n; j++) {
            if (a[j] == 0) {
                c[jj++] = cur;
            } else {
                cur += (a[j] > i);
            }
        }
        for (int j = n - 1, jj = holes, cur = 0; j >= 0; j--) {
            if (a[j] == 0) {
                c[jj--] += cur;
            } else {
                cur += (a[j] < i);
            }
        }
        for (int jj = 1; jj <= holes; jj++)
            c[jj] += c[jj - 1];
        compute(0, holes, 0, holes);
        for (int j = 0; j <= holes; j++)
            dp[0][j] = max(dp[0][j], dp[1][j]);
    }
    ans += dp[0][holes];
    cout << ans << endl;
}