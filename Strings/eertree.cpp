const int SIGMA = 26;

// char ⟼ [0, SIGMA)
int ctoi(char c) {
    int res = (c - 'a');
    assert(0 <= res && res < SIGMA);
    return res;
}

struct Eertree {
    struct Node {
        int nxt[SIGMA], link, len, cnt;
        Node(int _link, int _len) : link(_link), len(_len), cnt(0) {
            memset(nxt, 0, sizeof(nxt));
        }
    };
    
    vector<int> s;
    vector<Node> t;
    int p;
    
    Eertree() {
        s.push_back(-1);
        t.emplace_back(1, 0);
        t.emplace_back(0, -1);
        p = 0;
    }
    
    int update(int v) { 
        while (s[s.size() - t[v].len - 2] != s.back())
            v = t[v].link;
        return v;
    }
    
    int addLetter(char c) {
        int i = ctoi(c);
        s.push_back(i);
        p = update(p);
        if (t[p].nxt[i] == 0) {
            t.emplace_back(t[update(t[p].link)].nxt[i], t[p].len + 2);
            t[p].nxt[i] = t.size() - 1;
        }
        p = t[p].nxt[i];
        return (t[p].cnt = t[t[p].link].cnt + 1);
    }
};