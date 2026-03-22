#include <bits/stdc++.h>
using namespace std;

struct FeedbackSolver {
    int n;
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;

    FeedbackSolver(int _n) : n(_n), adj(_n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        edges.push_back({u, v});
    }

    bool is_dag(int mask) {
        // Check if graph is DAG after removing vertices in 'mask'
        vector<int> in_degree(n, 0);
        vector<int> active;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) {
                active.push_back(i);
                for (int v : adj[i]) {
                    if (!(mask & (1 << v))) in_degree[v]++;
                }
            }
        }

        queue<int> q;
        for (int i : active) if (in_degree[i] == 0) q.push(i);

        int count = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            count++;
            for (int v : adj[u]) {
                if (!(mask & (1 << v))) {
                    if (--in_degree[v] == 0) q.push(v);
                }
            }
        }
        return count == active.size();
    }

    // Solve Minimum Feedback Vertex Set - O(2^N * (N+M))
    int solve_fvs() {
        int min_v = n;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (is_dag(mask)) {
                min_v = min(min_v, __builtin_popcount(mask));
            }
        }
        return min_v;
    }

    // Solve Minimum Feedback Arc Set - O(2^N * N)
    // We find the Maximum Acyclic Subgraph (MAS). FAS = Total Edges - MAS.
    int solve_fas() {
        // dp[mask] = max number of forward edges possible using vertices in mask
        vector<int> dp(1 << n, 0);
        
        // precompute: gain[v][mask] = edges from mask to v
        vector<vector<int>> gain(n, vector<int>(1 << n, 0));
        for (int v = 0; v < n; v++) {
            for (int mask = 0; mask < (1 << n); mask++) {
                for (int u = 0; u < n; u++) {
                    if (mask & (1 << u)) {
                        // If there's an edge u -> v, it becomes a forward edge
                        // if v is added to the ordering AFTER u.
                        for(int neighbor : adj[u]) if(neighbor == v) gain[v][mask]++;
                    }
                }
            }
        }

        for (int mask = 0; mask < (1 << n); mask++) {
            for (int v = 0; v < n; v++) {
                if (!(mask & (1 << v))) {
                    int next_mask = mask | (1 << v);
                    dp[next_mask] = max(dp[next_mask], dp[mask] + gain[v][mask]);
                }
            }
        }

        return edges.size() - dp[(1 << n) - 1];
    }
};

#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false; // They are already in the same component (Cycle!)
    }
};

struct UndirectedFVS {
    int n;
    vector<pair<int, int>> edges;

    UndirectedFVS(int _n) : n(_n) {}

    void add_edge(int u, int v) {
        edges.push_back({u, v});
    }

    // A subgraph is a forest if adding edges never connects two nodes 
    // already in the same connected component.
    bool is_forest(int mask) {
        DSU dsu(n);
        for (auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            // If neither vertex is in the "removed" set (mask)
            if (!(mask & (1 << u)) && !(mask & (1 << v))) {
                if (!dsu.unite(u, v)) {
                    return false; // Found an undirected cycle
                }
            }
        }
        return true;
    }

    vector<int> solve() {
        int best_mask = (1 << n) - 1;
        int min_size = n;

        // Iterate through all possible subsets of vertices to remove
        for (int mask = 0; mask < (1 << n); mask++) {
            int current_size = __builtin_popcount(mask);
            if (current_size < min_size) {
                if (is_forest(mask)) {
                    min_size = current_size;
                    best_mask = mask;
                }
            }
        }

        vector<int> fvs;
        for (int i = 0; i < n; i++) {
            if (best_mask & (1 << i)) fvs.push_back(i);
        }
        return fvs;
    }
};

//todo check
