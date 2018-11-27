const int SIGMA = 26;

// char ⟼ [0, SIGMA)
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
                if (w == 0)
                    w = t[u].go[i];
                else {
                    x = (v ? t[u].go[i] : 0);
                    y = (t[x].id == -1 ? t[x].tlink : x);
                    q.push(w);
                }
            }
        }
    }
};