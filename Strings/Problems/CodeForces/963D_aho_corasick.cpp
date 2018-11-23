#include <bits/stdc++.h>
using namespace std;

#define eprint(x) cerr << "[" << __LINE__ << "]\t" << #x " = " << (x) << endl
#ifndef LOCAL
#define cerr if (false) cerr
#endif

#define endl '\n'
using ll = long long;

constexpr int SIGMA = 26;

// char -> [0, SIGMA)
int ctoi(char c) {
    int res = (c - 'a');
    assert(0 <= res && res < SIGMA);
    return res;
}

struct AhoCorasick {
    struct Node {
        int go[SIGMA], link, tlink, id;
        Node() {
            memset(go, 0, sizeof(go));
            link = tlink = 0;
            id = -1;
        }
    };
    
    vector<Node> t;
    
    AhoCorasick() {
        t.emplace_back();
    }
    
    int addString(const string &s, int id) {
        int v = 0;
        for (auto c : s) {
            int i = ctoi(c);
            if (t[v].go[i] == 0) {
                t[v].go[i] = t.size();
                t.emplace_back();
            }
            v = t[v].go[i];
        }
        t[v].id = id;
        return v;
    }
    
    void pushLinks() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            int u = t[v].link;
            for (int i = 0; i < SIGMA; i++) {
                int &w = t[v].go[i];
                int &x = t[w].link;
                int &y = t[w].tlink;
                if (w == 0) {
                    w = t[u].go[i];
                } else {
                    x = (v ? t[u].go[i] : 0);
                    y = (t[x].id == -1 ? t[x].tlink : x);
                    q.push(w);
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string s;
    cin >> s >> n;
    vector<int> ks(n);
    vector<string> p(n);
    AhoCorasick ac;
    for (int i = 0; i < n; i++) {
        cin >> ks[i] >> p[i];
        ac.addString(p[i], i);
    }
    ac.pushLinks();
    auto &t = ac.t;
    
    vector<vector<int>> pos(n);
    int v = 0;
    for (int i = 0; i < s.size(); i++) {
        v = t[v].go[ctoi(s[i])];
        int u = v;
        while (u != 0) {
            if (t[u].id != -1) {
                pos[t[u].id].push_back(i);
            }
            u = t[u].tlink;
        }
    }
    
    const int INF = 1e9;
    for (int i = 0; i < n; i++) {
        int ans = INF;
        int k = ks[i];
        for (int j = 0; j + k - 1 < pos[i].size(); j++)
            ans = min(ans, pos[i][j + k - 1] - pos[i][j] + (int) p[i].size());
        cout << (ans == INF ? -1 : ans) << endl;
    }
}