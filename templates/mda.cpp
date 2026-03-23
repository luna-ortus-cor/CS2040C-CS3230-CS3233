#include <bits/stdc++.h>
using namespace std;

struct MinDegreeArborescence {
    int n;
    vector<vector<int>> adj;

    MinDegreeArborescence(int _n) : n(_n), adj(_n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    // Check if there exists a spanning arborescence with max out-degree <= max_d
    // dp[mask][u] = bitmask of current out-degrees (simplified for small N)
    // For CP, we usually use backtracking with pruning for this specific constraint.
    
    bool check(int root, int mask, vector<int>& out_deg, int max_d) {
        if (mask == (1 << n) - 1) return true;

        for (int u = 0; u < n; u++) {
            if (mask & (1 << u)) { // u is in the current arborescence
                if (out_deg[u] < max_d) {
                    for (int v : adj[u]) {
                        if (!(mask & (1 << v))) { // v is not yet included
                            out_deg[u]++;
                            if (check(root, mask | (1 << v), out_deg, max_d)) return true;
                            out_deg[u]--;
                        }
                    }
                }
            }
        }
        return false;
    }

    int solve() {
        for (int d = 1; d < n; d++) {
            for (int r = 0; r < n; r++) {
                vector<int> out_deg(n, 0);
                if (check(r, 1 << r, out_deg, d)) return d;
            }
        }
        return n - 1;
    }
};
