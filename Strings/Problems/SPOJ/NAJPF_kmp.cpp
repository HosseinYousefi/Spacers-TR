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

vector<int> kmp(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    auto pi = piFunc(p);
    vector<int> res;
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];
        j += (s[i] == p[j]);
        if (j == m) {
            res.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        string s, p;
        cin >> s >> p;
        auto ans = kmp(s, p);
        if (ans.empty()) {
            cout << "Not Found" << endl << endl;
            continue;
        }
        cout << ans.size() << endl;
        for (auto pos : ans)
            cout << pos + 1 << ' ';
        cout << endl << endl;
    }
}