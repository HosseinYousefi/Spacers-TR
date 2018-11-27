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