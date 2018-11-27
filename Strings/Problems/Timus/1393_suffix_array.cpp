#include <bits/stdc++.h>
using namespace std;

#define eprint(x) cerr << "[" << __LINE__ << "]\t" << #x " = " << (x) << endl
#ifndef LOCAL
#define cerr if (false) cerr
#endif

#define endl '\n'
using ll = long long;

struct SuffixArray {
    static const int SIGMA = 256;
    vector<int> p, c;
    
    SuffixArray() {}
    
    SuffixArray(const string &s) {
        buildArray(s);
        buildHeight(s);
    }
    
    void buildArray(const string &s) {
        int n = s.size();
        p.resize(n); c.resize(n);
        vector<int> cnt(max(SIGMA, n));
        
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < SIGMA; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        for (int i = 1; i < n; i++)
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
        vector<int> p2(n), c2(n);
        for (int w = 1; w < n; w <<= 1) {
            for (int i = 0; i < n; i++) {
                p2[i] = p[i] - w;
                if (p2[i] < 0)
                    p2[i] += n;
            }
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++)
                cnt[c[p2[i]]]++;
            for (int i = 1; i < n; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                p[--cnt[c[p2[i]]]] = p2[i];
            c2[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                bool notEq = (c[p[i]] != c[p[i - 1]]) ||
                             (c[(p[i] + w) % n] != c[(p[i - 1] + w) % n]);
                c2[p[i]] = c2[p[i - 1]] + notEq;
            }
            c.swap(c2);
        }
    }
    
    vector<int> r, h;
    
    void buildHeight(const string &s) {
        int n = s.size();
        r.resize(n); h.resize(n - 1);
        for (int i = 0; i < n; i++)
            r[p[i]] = i;
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (r[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = p[r[i] + 1];
            if (c[i] == c[j]) {
                h[r[i]] = n;
                continue;
            }
            k = max(k - 1, 0);
            while (k < n && s[(i + k) % n] == s[(j + k) % n])
                k++;
            h[r[i]] = k;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string s;
    cin >> n >> s;
    SuffixArray sa(s);
    ll ans = 0;
    for (auto val : sa.h)
        ans += val;
    cout << setprecision(10) << fixed;
    cout << ((double) ans) / (n - 1) << endl;
}