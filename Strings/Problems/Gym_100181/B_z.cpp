#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define eprint(x) cerr << #x << " = " << x << endl
#else
#define eprint(x) 42
#endif

#define endl '\n'
using ll = long long;

vector<int> zFunc(const string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

vector<int> zMatch(const string &s, const string &p) {
    int n = s.size(), m = p.size();
    auto z = zFunc(p + "#" + s);
    vector<int> res;
    for (int i = 0; i < n; i++)
        if (z[m + 1 + i] == m)
            res.push_back(i);
    return res;
}

int main() {
    freopen("search.in", "r", stdin);
    freopen("search.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, p;
    cin >> s >> p;
    auto res = zMatch(s, p);
    cout << res.size() << endl;
    for (auto pos : res)
        cout << pos + 1 << ' ';
    cout << endl;
}