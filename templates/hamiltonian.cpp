#include <bits/stdc++.h>
using namespace std;

struct Hamiltonian {
    int n;
    bool directed;
    vector<vector<int>> adj;

    Hamiltonian(int _n, bool _directed) : n(_n), directed(_directed), adj(_n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    vector<int> solve() {
        // dp[mask][i] = true if there exists a path covering 'mask' ending at 'i'
        vector<vector<bool>> dp(1 << n, vector<bool>(n, false));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) dp[1 << i][i] = true;

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (!dp[mask][u]) continue;
                for (int v : adj[u]) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        if (!dp[next_mask][v]) {
                            dp[next_mask][v] = true;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }

        int last_node = -1;
        int full_mask = (1 << n) - 1;
        for (int i = 0; i < n; i++) {
            if (dp[full_mask][i]) {
                last_node = i;
                break;
            }
        }

        if (last_node == -1) return {};

        // Reconstruct Path
        vector<int> path;
        int curr_mask = full_mask;
        while (last_node != -1) {
            path.push_back(last_node);
            int prev = parent[curr_mask][last_node];
            curr_mask ^= (1 << last_node);
            last_node = prev;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
