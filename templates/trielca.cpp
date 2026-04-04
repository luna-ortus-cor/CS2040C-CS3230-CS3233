#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 1000005; // Total sum of string lengths
const int LOG = 20;

struct Trie {
    int next[MAX_NODES][26];
    int depth[MAX_NODES];
    int tin[MAX_NODES], tout[MAX_NODES];
    int up[MAX_NODES][LOG];
    int timer = 0, nodes = 1;

    Trie() {
        memset(next, 0, sizeof(next));
        memset(up, 0, sizeof(up));
        depth[0] = 0;
    }

    // Returns the node ID of the end of the string
    int insert(const string& s) {
        int curr = 0;
        for (char c : s) {
            int v = c - 'a';
            if (!next[curr][v]) {
                next[curr][v] = nodes++;
                depth[next[curr][v]] = depth[curr] + 1;
            }
            curr = next[curr][v];
        }
        return curr;
    }

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[u][0] = p;
        for (int i = 1; i < LOG; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int i = 0; i < 26; i++) {
            if (next[u][i]) dfs(next[u][i], u);
        }
        tout[u] = timer;
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    int get_lcp_len(int u, int v) {
        return depth[get_lca(u, v)];
    }
};
