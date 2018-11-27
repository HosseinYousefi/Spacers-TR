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

const int SIGMA = 26;

// char ⟼ [0, SIGMA)
int ctoi(char c) {
    int res = (c - 'a');
    assert(0 <= res && res < SIGMA);
    return res;
}

vector<vector<int>> kmpAut(const string &s) {
    int n = s.size();
    auto pi = piFunc(s);
    vector<vector<int>> aut(n + 1, vector<int>(SIGMA));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j < SIGMA; j++) {
            if (i < n && ctoi(s[i]) == j)
                aut[i][j] = i + 1;
            else if (i > 0)
                aut[i][j] = aut[pi[i - 1]][j];
        }
    return aut;
}