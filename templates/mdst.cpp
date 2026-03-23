#include <bits/stdc++.h>
using namespace std;

struct MDST {
    int n;
    vector<pair<int, int>> edges;
    vector<int> degree;
    int min_max_degree;

    MDST(int _n) : n(_n), degree(_n, 0), min_max_degree(_n) {}

    void add_edge(int u, int v) {
        edges.push_back({u, v});
    }

    struct DSU {
        vector<int> p;
        DSU(int n) { p.resize(n); iota(p.begin(), p.end(), 0); }
        int find(int i) { return p[i] == i ? i : p[i] = find(p[i]); }
        bool unite(int i, int j) {
            int root_i = find(i), root_j = find(j);
            if (root_i != root_j) { p[root_i] = root_j; return true; }
            return false;
        }
    };

    void backtrack(int edge_idx, int edges_count, int current_max_deg) {
        if (current_max_deg >= min_max_degree) return;

        if (edges_count == n - 1) {
            min_max_degree = current_max_deg;
            return;
        }

        if (edge_idx == edges.size()) return;

        // Try including edges[edge_idx]
        int u = edges[edge_idx].first;
        int v = edges[edge_idx].second;
        
        // This is a simplified backtracking; for efficiency, 
        // a bitmask DP checking connectivity is preferred for N < 20.
        // Here we just show the logical constraint:
    }

    // Exact approach for small N using bitmask
    int solve_bitmask() {
        int best_deg = n;
        // mask represents the set of edges chosen
        for (int mask = 0; mask < (1 << edges.size()); mask++) {
            if (__builtin_popcount(mask) != n - 1) continue;
            
            DSU dsu(n);
            vector<int> d(n, 0);
            int components = n;
            int local_max = 0;
            
            for (int i = 0; i < edges.size(); i++) {
                if (mask & (1 << i)) {
                    if (dsu.unite(edges[i].first, edges[i].second)) {
                        components--;
                        d[edges[i].first]++;
                        d[edges[i].second]++;
                    }
                }
            }

            if (components == 1) {
                for (int i = 0; i < n; i++) local_max = max(local_max, d[i]);
                best_deg = min(best_deg, local_max);
            }
        }
        return best_deg;
    }
};
