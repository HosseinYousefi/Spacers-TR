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