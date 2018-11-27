#include <bits/stdc++.h>
using namespace std;

#define eprint(x) cerr << "[" << __LINE__ << "]\t" << #x " = " << (x) << endl
#ifndef LOCAL
#define cerr if (false) cerr
#endif

#define endl '\n'
using ll = long long;

template <typename T>
struct SparseTable {
    vector<int> lg;
    vector<vector<T>> table;
    
    SparseTable() {}
    
    SparseTable(const vector<T> &a) {
        int n = a.size();

        lg.resize(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        
        int k = lg[n];
        table.assign(n, vector<T>(k + 1));
        for (int i = 0; i < n; i++)
            table[i][0] = a[i];
        for (int j = 1; j <= k; j++) {
            int w = (1 << j);
            for (int i = 0; i + w <= n; i++)
                table[i][j] = min(table[i][j - 1],
                                  table[i + w / 2][j - 1]);
        }
    }
    
    T query(int l, int r) {
        int k = lg[r - l];
        return min(table[l][k], table[r - (1 << k)][k]);
    }
};

struct SuffixArray {
    static const int SIGMA = 256;
    vector<int> p, c;
    
    SuffixArray() {}
    
    SuffixArray(const string &s) {
        buildArray(s);
        buildHeight(s);
    }
    
    void buildArray(const string &s) {
        int n = s.size() + 1;
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
        p.erase(p.begin());
    }
    
    vector<int> r, h;
    SparseTable<int> st;
    
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
            k = max(k - 1, 0);
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            h[r[i]] = k;
        }
        st = SparseTable<int>(h);
    }
    
    int lcp(int i, int j) {
        assert(i != j);
        i = r[i]; j = r[j];
        if (i > j)
            swap(i, j);
        return st.query(i, j);
    }
};
int main() {
    freopen("sufflcp.in", "r", stdin);
    freopen("sufflcp.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string s;
    cin >> n >> s;
    SuffixArray sa(s);
    for (auto val : sa.h)
        cout << val << ' ';
    cout << endl;
}