#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define eprint(x) cerr << #x << " = " << x << endl
#else
#define eprint(x) 42
#endif

#define endl '\n'
using ll = long long;

vector<int> piFunc(const string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        pi[i] = j + (s[i] == s[j]);
    }
    return pi;
}

vector<vector<int>> kmpAut(const string &s) {
    int n = s.size();
    auto pi = piFunc(s);
    vector<vector<int>> aut(n + 1, vector<int>(26));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 26; j++) {
            if ('a' + j == s[i])
                aut[i][j] = i + 1;
            else if (i > 0)
                aut[i][j] = aut[pi[i - 1]][j];
        }
    return aut;
}

vector<int> kmp(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    auto aut = kmpAut(p);
    vector<int> res;
    for (int i = 0, j = 0; i < n; i++) {
        j = aut[j][s[i] - 'a'];
        if (j == m)
            res.push_back(i - m + 1);
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
        if (c == '?') {
            cout << (kmp(text, s).empty() ? "NO" : "YES") << endl;
        }
        else
            text += s;
    }
}