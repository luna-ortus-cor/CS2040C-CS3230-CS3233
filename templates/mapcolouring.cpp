#include <bits/stdc++.h>
using namespace std;

struct MapColour {
    int n;
    vector<vector<int>> adj;
    vector<int> colors; // Stores the assigned color for each node (1 to k)

    MapColour(int countries) : n(countries) {
        adj.assign(n, vector<int>());
        colors.assign(n, 0);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Check if it's safe to color node u with color 'c'
    bool is_safe(int u, int c) {
        for (int neighbor : adj[u]) {
            if (colors[neighbor] == c) return false;
        }
        return true;
    }

    // Backtracking function to try coloring with 'k' colors
    bool solve_backtrack(int u, int k) {
        if (u == n) return true; // All nodes colored

        for (int c = 1; c <= k; c++) {
            if (is_safe(u, c)) {
                colors[u] = c;
                if (solve_backtrack(u + 1, k)) return true;
                colors[u] = 0; // Backtrack
            }
        }
        return false;
    }

    // Finds the minimum number of colors required
    int get_chromatic_number() {
        if (n == 0) return 0;
        // Optimization: Start from 1, but we know max is 4 for planar maps
        // or n for general graphs.
        for (int k = 1; k <= n; k++) {
            fill(colors.begin(), colors.end(), 0);
            if (solve_backtrack(0, k)) return k;
        }
        return n;
    }

    // Returns the color assignment
    vector<int> get_coloring() {
        return colors;
    }
};

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    MapColour mc(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        mc.add_edge(u, v);
    }

    int min_colors = mc.get_chromatic_number();
    cout << "Minimum colors required: " << min_colors << endl;

    vector<int> result = mc.get_coloring();
    cout << "Coloring assignment: ";
    for (int i = 0; i < N; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

struct MapColour {
    int n;
    vector<long long> adj_mask; // Adjacency matrix as bitmasks
    vector<int> colors;
    vector<vector<int>> adj_list;

    MapColour(int countries) : n(countries) {
        adj_mask.assign(n, 0);
        adj_list.assign(n, vector<int>());
        colors.assign(n, 0);
    }

    void add_edge(int u, int v) {
        adj_mask[u] |= (1LL << v);
        adj_mask[v] |= (1LL << u);
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    // Inclusion-Exclusion to find Chromatic Number in O(2^n * n)
    int get_chromatic_number() {
        if (n == 0) return 0;
        
        // ind[mask] = number of independent sets contained in mask
        vector<int> ind(1 << n, 0);
        ind[0] = 1;
        for (int mask = 1; mask < (1 << n); mask++) {
            int v = __builtin_ctz(mask);
            int prev_mask = mask ^ (1 << v);
            ind[mask] = ind[prev_mask] + ind[prev_mask & ~adj_mask[v]];
        }

        // Smallest k such that we can cover the graph with k independent sets
        for (int k = 1; k <= n; k++) {
            long long sum = 0;
            for (int mask = 0; mask < (1 << n); mask++) {
                // Parity of the number of elements in the complement
                if ((n - __builtin_popcount(mask)) & 1) 
                    sum -= pow_mod(ind[mask], k);
                else 
                    sum += pow_mod(ind[mask], k);
            }
            if (sum > 0) return k;
        }
        return n;
    }

    // Efficient power function
    long long pow_mod(long long base, int exp) {
        long long res = 1;
        for (int i = 0; i < exp; i++) res *= base;
        return res;
    }

    // Guided Backtracking to find the specific coloring
    bool find_coloring(int u, int k) {
        if (u == n) return true;
        for (int c = 1; c <= k; c++) {
            bool ok = true;
            for (int v : adj_list[u]) {
                if (colors[v] == c) { ok = false; break; }
            }
            if (ok) {
                colors[u] = c;
                if (find_coloring(u + 1, k)) return true;
                colors[u] = 0;
            }
        }
        return false;
    }

    void solve() {
        int k = get_chromatic_number();
        cout << "Minimum colors: " << k << endl;
        find_coloring(0, k);
        cout << "Coloring: ";
        for (int i = 0; i < n; i++) cout << colors[i] << " ";
        cout << endl;
    }
};

int main() {
    int N, M; cin >> N >> M;
    MapColour mc(N);
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        mc.add_edge(u, v);
    }
    mc.solve();
    return 0;
}
