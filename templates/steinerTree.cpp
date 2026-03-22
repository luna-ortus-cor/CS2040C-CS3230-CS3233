struct SteinerTree {
    int n, k;
    struct State { int mask, u; int type; int val; }; // type 0: edge, type 1: submask
    vector<vector<pair<int, int>>> adj;
    vector<vector<ll>> dp;
    vector<vector<State>> pre;
    vector<int> terminals;

    SteinerTree(int _n, const vector<int>& _terminals) : n(_n), terminals(_terminals) {
        k = terminals.size();
        adj.resize(n + 1);
        dp.assign(1 << k, vector<ll>(n + 1, INF));
        pre.assign(1 << k, vector<State>(n + 1, {0, 0, -1, 0}));
    }

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void solve() {
        for (int i = 0; i < k; i++) dp[1 << i][terminals[i]] = 0;

        for (int mask = 1; mask < (1 << k); mask++) {
            for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
                for (int i = 1; i <= n; i++) {
                    if (dp[mask][i] > dp[sub][i] + dp[mask ^ sub][i]) {
                        dp[mask][i] = dp[sub][i] + dp[mask ^ sub][i];
                        pre[mask][i] = {mask, i, 1, sub};
                    }
                }
            }
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            for (int i = 1; i <= n; i++) if (dp[mask][i] != INF) pq.push({dp[mask][i], i});
            while (!pq.empty()) {
                ll d = pq.top().first; int u = pq.top().second; pq.pop();
                if (d > dp[mask][u]) continue;
                for (auto& e : adj[u]) {
                    if (dp[mask][e.first] > dp[mask][u] + e.second) {
                        dp[mask][e.first] = dp[mask][u] + e.second;
                        pre[mask][e.first] = {mask, e.first, 0, u};
                        pq.push({dp[mask][e.first], e.first});
                    }
                }
            }
        }
    }

    // Returns a set of edges {u, v} included in the tree
    void get_edges(int mask, int u, set<pair<int, int>>& res) {
        State& p = pre[mask][u];
        if (p.type == -1) return;
        if (p.type == 0) {
            res.insert({min(u, p.val), max(u, p.val)});
            get_edges(mask, p.val, res);
        } else {
            get_edges(p.val, u, res);
            get_edges(mask ^ p.val, u, res);
        }
    }
};

//case where graph is tree
struct SteinerTreee {
    int n;
    vector<vector<int>> adj;
    vector<int> parent;
    vector<bool> is_terminal, in_steiner;

    SteinerTree(int _n) : n(_n), adj(_n + 1), parent(_n + 1), is_terminal(_n + 1, false), in_steiner(_n + 1, false) {}

    void dfs(int u, int p) {
        parent[u] = p;
        for (int v : adj[u]) if (v != p) dfs(v, u);
    }

    void solve(const vector<int>& terminals) {
        if (terminals.empty()) return;
        dfs(terminals[0], 0); // Root at the first terminal
        for (int t : terminals) {
            int curr = t;
            while (curr != 0 && !in_steiner[curr]) {
                in_steiner[curr] = true;
                curr = parent[curr];
            }
        }
    }
};

//case where graph is grid
struct HananGridSteiner {
    struct Point { int x, y, id; };
    
    ll solve(vector<Point>& terminals) {
        vector<int> xs, ys;
        for (auto p : terminals) { xs.push_back(p.x); ys.push_back(p.y); }
        sort(xs.begin(), xs.end()); xs.erase(unique(xs.begin(), xs.end()), xs.end());
        sort(ys.begin(), ys.end()); ys.erase(unique(ys.begin(), ys.end()), ys.end());

        int R = xs.size(), C = ys.size();
        auto get_id = [&](int r, int c) { return r * C + c + 1; };

        SteinerTree st(R * C, {});
        // Add horizontal and vertical edges between adjacent grid points
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (r + 1 < R) st.add_edge(get_id(r, c), get_id(r + 1, c), xs[r + 1] - xs[r]);
                if (c + 1 < C) st.add_edge(get_id(r, c), get_id(r, c + 1), ys[c + 1] - ys[c]);
            }
        }

        vector<int> term_ids;
        for (auto p : terminals) {
            int r = lower_bound(xs.begin(), xs.end(), p.x) - xs.begin();
            int c = lower_bound(ys.begin(), ys.end(), p.y) - ys.begin();
            term_ids.push_back(get_id(r, c));
        }
        
        st.terminals = term_ids;
        st.k = term_ids.size();
        st.dp.assign(1 << st.k, vector<ll>(st.n + 1, INF)); // Re-init DP for new terminals
        return st.solve();
    }
};

//todo check + implement DP dryefus wagner
