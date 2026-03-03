#include <bits/stdc++.h>
using namespace std;

//Using sparse table, for static query only
struct StaticLCA {
    vector<int> depth, first, euler, lg;
    vector<vector<int>> st;
    int n;

    StaticLCA(const vector<vector<int>> &adj, int root = 1) {
        n = adj.size();
        depth.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        dfs(adj, root, -1, 0);
        
        int m = euler.size();
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) lg[i] = lg[i / 2] + 1;
        st.assign(m, vector<int>(lg[m] + 1));
        for (int i = 0; i < m; i++) st[i][0] = euler[i];
        for (int j = 1; j <= lg[m]; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                int a = st[i][j - 1], b = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = (depth[a] < depth[b]) ? a : b;
            }
        }
    }

    void dfs(const vector<vector<int>> &adj, int u, int p, int d) {
        depth[u] = d;
        first[u] = euler.size();
        euler.push_back(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(adj, v, u, d + 1);
                euler.push_back(u);
            }
        }
    }

    int get_lca(int u, int v) {
        int L = first[u], R = first[v];
        if (L > R) swap(L, R);
        int j = lg[R - L + 1];
        int a = st[L][j], b = st[R - (1 << j) + 1][j];
        return (depth[a] < depth[b]) ? a : b;
    }

    int get_dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }
};

//Dynamic using segtree, for subtree query
struct EulerLCA {
    vector<int> depth, first, euler, seg;
    int n, m;

    EulerLCA(const vector<vector<int>> &adj, int root = 1) {
        n = adj.size();
        depth.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        dfs(adj, root, -1, 0);
        m = euler.size();
        seg.resize(4 * m);
        build(1, 0, m - 1);
    }

    void dfs(const vector<vector<int>> &adj, int u, int p, int d) {
        depth[u] = d;
        first[u] = euler.size();
        euler.push_back(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(adj, v, u, d + 1);
                euler.push_back(u); // Return to parent
            }
        }
    }

    void build(int node, int b, int e) {
        if (b == e) { seg[node] = euler[b]; return; }
        int mid = (b + e) / 2;
        build(node * 2, b, mid);
        build(node * 2 + 1, mid + 1, e);
        int l = seg[node * 2], r = seg[node * 2 + 1];
        seg[node] = (depth[l] < depth[r]) ? l : r;
    }

    int query(int node, int b, int e, int L, int R) {
        if (b > R || e < L) return -1;
        if (b >= L && e <= R) return seg[node];
        int mid = (b + e) / 2;
        int l = query(node * 2, b, mid, L, R);
        int r = query(node * 2 + 1, mid + 1, e, L, R);
        if (l == -1) return r;
        if (r == -1) return l;
        return (depth[l] < depth[r]) ? l : r;
    }

    int get_lca(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        return query(1, 0, m - 1, l, r);
    }

    int get_dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }
};

//Dynamic, for path update and query
struct HLD {
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;

    HLD(const vector<vector<int>> &adj, int root = 1) {
        int n = adj.size();
        parent.resize(n); depth.resize(n);
        heavy.assign(n, -1); head.resize(n);
        pos.resize(n);
        cur_pos = 0;

        dfs_sz(adj, root, -1, 0);
        dfs_hld(adj, root, root);
    }

    int dfs_sz(const vector<vector<int>> &adj, int u, int p, int d) {
        int size = 1, max_child_size = 0;
        parent[u] = p; depth[u] = d;
        for (int v : adj[u]) {
            if (v != p) {
                int child_size = dfs_sz(adj, v, u, d + 1);
                size += child_size;
                if (child_size > max_child_size) {
                    max_child_size = child_size;
                    heavy[u] = v; // Mark the heavy edge
                }
            }
        }
        return size;
    }

    void dfs_hld(const vector<vector<int>> &adj, int u, int h) {
        head[u] = h;
        pos[u] = cur_pos++;
        if (heavy[u] != -1) dfs_hld(adj, heavy[u], h); // Continue heavy path
        for (int v : adj[u]) {
            if (v != parent[u] && v != heavy[u]) {
                dfs_hld(adj, v, v); // Start new light path
            }
        }
    }

    int get_lca(int u, int v) {
        // Jump until both nodes are on the same heavy path
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) u = parent[head[u]];
            else v = parent[head[v]];
        }
        return (depth[u] < depth[v]) ? u : v;
    }

    int get_dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }
};
