#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define eprint(x) cerr << #x << " = " << x << endl
#else
#define eprint(x) 42
#endif

#define endl '\n'
using ll = long long;

const int MOD = 1e9 + 7;
const int P = 257;

vector<int> rabinKarp(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    vector<int> hs(n + 1);
    for (int i = n - 1; i >= 0; i--)
        hs[i] = (s[i] + hs[i + 1] * 1LL * P) % MOD;
    int hp = 0;
    for (int i = m - 1; i >= 0; i--)
        hp = (p[i] + hp * 1LL * P) % MOD;
    int pw = 1;
    for (int i = 0; i < m; i++)
        pw = (pw * 1LL * P) % MOD;
    vector<int> res;
    for (int i = 0; i + m <= n; i++) {
        int hash = (hs[i] - pw * 1LL * hs[i + m]) % MOD;
        if (hash < 0)
            hash += MOD;
        if (hash == hp)
            res.push_back(i);
    }
    return res;
}

int main() {
    freopen("nenokku_easy.in", "r", stdin);
    freopen("nenokku_easy.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text;
    char c; string s;
    while (cin >> c >> s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if (c == '?')
            cout << (rabinKarp(text, s).empty() ? "NO" : "YES") << endl;
        else
            text += s;
    }
}