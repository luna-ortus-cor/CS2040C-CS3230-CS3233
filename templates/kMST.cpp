#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e15;

struct KMST {
    int n, k;
    vector<vector<pair<int, int>>> adj;
    // dp[mask][u] = min weight of a tree covering 'mask', ending at 'u'
    vector<vector<ll>> dp;

    KMST(int _n, int _k) : n(_n), k(_k) {
        adj.resize(n);
        dp.assign(1 << n, vector<ll>(n, INF));
    }

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll solve() {
        // Base case: Single nodes
        for (int i = 0; i < n; i++) dp[1 << i][i] = 0;

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (dp[mask][u] == INF) continue;

                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int w = edge.second;
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        dp[next_mask][v] = min(dp[next_mask][v], dp[mask][u] + w);
                    }
                }
            }
        }

        ll ans = INF;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == k) {
                for (int i = 0; i < n; i++) ans = min(ans, dp[mask][i]);
            }
        }
        return (ans == INF) ? -1 : ans;
    }
};
