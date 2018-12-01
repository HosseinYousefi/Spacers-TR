using ll = long long;

struct edge {
    int from, to, cap, flow;
};

vector<edge> e;
vector<int> adj[N];
int d[N], ptr[N], src, snk, n, m, cap[N][N];

void add_edge(int from, int to, int cap) {
    adj[from].push_back((int)e.size());
    e.push_back({from, to, cap, 0});
    adj[to].push_back((int)e.size());
    e.push_back({to, from, cap, cap});
}

bool bfs(int lim) {
    queue<int> q;
    memset(d, -1, sizeof d);
    d[src] = 0;
    q.push(src);
    while (q.size() and d[snk] == -1) {
        int v = q.front();
        q.pop();
        for (int id: adj[v])
            if (d[e[id].to] == -1 and e[id].cap - e[id].flow >= lim) {
                d[e[id].to] = d[v] + 1;
                q.push(e[id].to);
            }
    }
    memset(ptr, 0, sizeof ptr);
    return d[snk] != -1;
}

bool dfs(int v, int lim) {
    if (v == snk)
        return true;
    for (; ptr[v] < adj[v].size(); ++ptr[v]) {
        int id = adj[v][ptr[v]];
        if (d[e[id].to] == d[v] + 1 and e[id].cap - e[id].flow >= lim)
            if (dfs(e[id].to, lim)) {
                e[id ^ 0].flow += lim;
                e[id ^ 1].flow -= lim;
                return true;
            }
    }
    return false;
}

ll dinic() {
    ll flow = 0;
    for (int lim = 1 << 30; lim; lim >>= 1)
        while (bfs(lim))
            while (dfs(src, lim))
                flow += lim;
    return flow;
}
