#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;

    HopcroftKarp(int n, int m) : n(n), m(m), adj(n), matchL(n, -1), matchR(m, -1), dist(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);
        for (int i = 0; i < n; i++) {
            if (matchL[i] == -1) {
                dist[i] = 0;
                q.push(i);
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (matchR[v] == -1) found = true;
                else if (dist[matchR[v]] == -1) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (matchR[v] == -1 || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                if (matchL[i] == -1 && dfs(i)) matching++;
        }
        return matching;
    }

    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; i++) {
            if (matchL[i] != -1) {
                pairs.push_back({i, matchL[i]});
            }
        }
        return pairs;
    }
};

struct Blossom {
    int n;
    vector<vector<int>> adj;
    vector<int> match, p, base, q;
    vector<bool> used, blossom;

    Blossom(int n) : n(n), adj(n), match(n, -1), p(n), base(n), used(n), blossom(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    int lca(int a, int b) {
        vector<bool> seen(n, false);
        while (true) {
            a = base[a]; seen[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            b = p[match[b]];
        }
    }

    void mark_path(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    int find_path(int root) {
        fill(used.begin(), used.end(), false);
        fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;
        used[root] = true;
        q = {root};
        int head = 0;
        while(head < q.size()){
            int v = q[head++];
            for (int to : adj[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                    int cur_base = lca(v, to);
                    fill(blossom.begin(), blossom.end(), false);
                    mark_path(v, cur_base, to);
                    mark_path(to, cur_base, v);
                    for (int i = 0; i < n; i++) {
                        if (blossom[base[i]]) {
                            base[i] = cur_base;
                            if (!used[i]) { used[i] = true; q.push_back(i); }
                        }
                    }
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) return to;
                    to = match[to];
                    used[to] = true; q.push_back(to);
                }
            }
        }
        return -1;
    }

    int max_matching() {
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                int v = find_path(i);
                while (v != -1) {
                    int pv = p[v], ppv = match[pv];
                    match[v] = pv; match[pv] = v;
                    v = ppv;
                }
            }
        }
        for (int i = 0; i < n; i++) if (match[i] != -1) result++;
        return result / 2;
    }

    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; i++) {
            // match[i] > i ensures we only count each edge once
            if (match[i] != -1 && match[i] > i) {
                pairs.push_back({i, match[i]});
            }
        }
        return pairs;
    }
};

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

// Finds Maximum Weight Perfect Matching
// For Minimum Weight, negate the costs and negate the result
struct Hungarian {
    int n;
    vector<vector<ll>> a;
    vector<ll> u, v;
    vector<int> p, way;

    Hungarian(int n) : n(n), a(n + 1, vector<ll>(n + 1, INF)), u(n + 1), v(n + 1), p(n + 1), way(n + 1) {}

    // We use 1-based indexing for this specific implementation
    void set_weight(int i, int j, ll w) {
        a[i][j] = w; 
    }

    ll solve() {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<ll> minv(n + 1, INF);
            vector<bool> used(n + 1, false);
            do {
                used[j0] = true;
                int i0 = p[j0], j1;
                ll delta = INF;
                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        ll cur = a[i0][j] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }
                for (int j = 0; j <= n; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        return -v[0]; // The max weight (if you negated for min-cost)
    }

    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> pairs;
        for (int j = 1; j <= n; j++) {
            if (p[j] != 0) {
                // Returns {row_index, column_index}
                // Note: Use p[j] - 1 and j - 1 if you want 0-based output
                pairs.push_back({p[j], j});
            }
        }
        return pairs;
    }
};

vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
for (int i=1; i<=n; ++i) {
    p[0] = i;
    int j0 = 0;
    vector<int> minv (m+1, INF);
    vector<bool> used (m+1, false);
    do {
        used[j0] = true;
        int i0 = p[j0],  delta = INF,  j1;
        for (int j=1; j<=m; ++j)
            if (!used[j]) {
                int cur = A[i0][j]-u[i0]-v[j];
                if (cur < minv[j])
                    minv[j] = cur,  way[j] = j0;
                if (minv[j] < delta)
                    delta = minv[j],  j1 = j;
            }
        for (int j=0; j<=m; ++j)
            if (used[j])
                u[p[j]] += delta,  v[j] -= delta;
            else
                minv[j] -= delta;
        j0 = j1;
    } while (p[j0] != 0);
    do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
    } while (j0);
}

vector<int> ans (n+1);
for (int j=1; j<=m; ++j)
    ans[p[j]] = j;

int cost = -v[0];
