struct Eertree {
    struct Node {
        int nxt[26], link, len, cnt;
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
    
    int addLetter(int c) {
        s.push_back(c);
        p = update(p);
        if (t[p].nxt[c] == 0) {
            t.emplace_back(t[update(t[p].link)].nxt[c], t[p].len + 2);
            t[p].nxt[c] = t.size() - 1;
        }
        p = t[p].nxt[c];
        return (t[p].cnt = t[t[p].link].cnt + 1);
    }
};