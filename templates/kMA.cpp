#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e15;

struct KArborescence {
    int n, k;
    vector<vector<pair<int, int>>> adj;
    // dp[mask][root] = min weight of arborescence on 'mask' rooted at 'root'
    vector<vector<ll>> dp;

    KArborescence(int _n, int _k) : n(_n), k(_k) {
        adj.resize(n);
        dp.assign(1 << n, vector<ll>(n, INF));
    }

    void add_directed_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    ll solve() {
        // Base case: 1-node arborescence costs 0
        for (int i = 0; i < n; i++) dp[1 << i][i] = 0;

        // Iterate masks by size to ensure sub-arborescences are solved
        for (int sz = 1; sz < k; sz++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                if (__builtin_popcount(mask) != sz) continue;
                
                for (int r = 0; r < n; r++) {
                    if (!(mask & (1 << r)) || dp[mask][r] == INF) continue;

                    // Transition: Add a new node 'v' by connecting it to any 'u' already in the mask
                    for (int u = 0; u < n; u++) {
                        if (mask & (1 << u)) {
                            for (auto& edge : adj[u]) {
                                int v = edge.first;
                                int w = edge.second;
                                if (!(mask & (1 << v))) {
                                    int next_mask = mask | (1 << v);
                                    dp[next_mask][r] = min(dp[next_mask][r], dp[mask][r] + w);
                                }
                            }
                        }
                    }
                }
            }
        }

        ll ans = INF;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == k) {
                for (int r = 0; r < n; r++) ans = min(ans, dp[mask][r]);
            }
        }
        return (ans >= INF) ? -1 : ans;
    }
};
