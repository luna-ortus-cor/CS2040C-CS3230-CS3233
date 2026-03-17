#include <bits/stdc++.h>
using namespace std;

// TODO implement get all VC/IS
template<size_t MAXN>
struct GeneralGraphSolver {
    int n;
    bitset<MAXN> adj[MAXN];
    bitset<MAXN> max_is_nodes;
    int max_is_size = 0;

    GeneralGraphSolver(int n) : n(n) {}

    void add_edge(int u, int v) {
        adj[u].set(v);
        adj[v].set(u);
    }

    // Branch and Bound for Maximum Independent Set
    void solve(bitset<MAXN> current_is, bitset<MAXN> candidates) {
        if (candidates.none()) {
            if (current_is.count() > max_is_size) {
                max_is_size = current_is.count();
                max_is_nodes = current_is;
            }
            return;
        }

        // Pruning: if even with all candidates we can't beat current best
        if (current_is.count() + candidates.count() <= max_is_size) return;

        // Heuristic: Pick vertex with highest degree in the subgraph
        int v = -1;
        int max_deg = -1;
        for (int i = candidates._Find_first(); i < n; i = candidates._Find_next(i)) {
            int deg = (adj[i] & candidates).count();
            if (deg > max_deg) {
                max_deg = deg;
                v = i;
            }
        }

        // Branch 1: v is in the Independent Set
        // Remove v and all its neighbors from candidates
        current_is.set(v);
        solve(current_is, candidates & ~adj[v] & ~bitset<MAXN>().set(v));
        current_is.reset(v);

        // Branch 2: v is NOT in the Independent Set
        candidates.reset(v);
        solve(current_is, candidates);
    }

    vector<int> get_mis() {
        max_is_size = 0;
        max_is_nodes.reset();
        bitset<MAXN> candidates;
        for (int i = 0; i < n; i++) candidates.set(i);
        
        solve(bitset<MAXN>(), candidates);

        vector<int> res;
        for (int i = 0; i < n; i++) if (max_is_nodes.test(i)) res.push_back(i);
        return res;
    }

    vector<int> get_mvc() {
        get_mis(); // Ensure max_is_nodes is populated
        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (!max_is_nodes.test(i)) res.push_back(i);
        }
        return res;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    GeneralGraphSolver<40> solver(n); // Adjust MAXN as needed
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        solver.add_edge(u, v);
    }

    vector<int> mis = solver.get_mis();
    cout << mis.size() << "\n";
    for (int v : mis) cout << v << " ";
    return 0;
}
