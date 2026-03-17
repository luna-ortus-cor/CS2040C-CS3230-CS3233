#include <bits/stdc++.h>
using namespace std;

// Utility to generate the complement graph G' = (V, E')
template<size_t MAXN>
vector<bitset<MAXN>> get_complement(int n, const vector<bitset<MAXN>>& adj) {
    vector<bitset<MAXN>> comp(n);
    bitset<MAXN> all_bits;
    for (int i = 0; i < n; i++) all_bits.set(i);

    for (int i = 0; i < n; i++) {
        // G' has an edge if G does NOT have an edge (and it's not the same node)
        comp[i] = all_bits ^ adj[i];
        comp[i].reset(i); 
    }
    return comp;
}

template<size_t MAXN>
struct MaxCliqueSolver {
    int n;
    vector<bitset<MAXN>> adj;
    vector<bitset<MAXN>> all_max_cliques;
    int max_size;

    MaxCliqueSolver(int n) : n(n), adj(n), max_size(0) {}

    MaxCliqueSolver(int n, const vector<bitset<MAXN>>& external_adj) 
        : n(n), adj(external_adj), max_size(0) {}

    void add_edge(int u, int v) {
        adj[u].set(v);
        adj[v].set(u);
    }

    void bron_kerbosch(bitset<MAXN> R, bitset<MAXN> P, bitset<MAXN> X, bool find_all) {
        if (P.none() && X.none()) {
            int cur = R.count();
            if (cur > max_size) {
                max_size = cur;
                all_max_cliques.clear();
                all_max_cliques.push_back(R);
            } else if (find_all && cur == max_size && cur > 0) {
                all_max_cliques.push_back(R);
            }
            return;
        }

        if (R.count() + P.count() < (find_all ? max_size : max_size + 1)) return;

        bitset<MAXN> P_or_X = P | X;
        int pivot = P_or_X._Find_first();
        bitset<MAXN> candidates = P & ~adj[pivot];

        for (int v = candidates._Find_first(); v < n; v = candidates._Find_next(v)) {
            bitset<MAXN> singleton_v;
            singleton_v.set(v);
            bron_kerbosch(R | singleton_v, P & adj[v], X & adj[v], find_all);
            P.reset(v);
            X.set(v);
        }
    }

    vector<vector<int>> solve(bool find_all = false) {
        all_max_cliques.clear();
        max_size = 0;
        bitset<MAXN> P, R, X;
        for (int i = 0; i < n; i++) P.set(i);
        
        bron_kerbosch(R, P, X, find_all);

        vector<vector<int>> results;
        for (auto& bs : all_max_cliques) {
            vector<int> clique;
            for (int i = 0; i < n; i++) if (bs.test(i)) clique.push_back(i);
            results.push_back(clique);
        }
        return results;
    }

    // Method to return MIS by solving for Clique on the complement
    vector<vector<int>> solve_mis(bool find_all = false) {
        vector<bitset<MAXN>> comp_adj = get_complement<MAXN>(n, adj);
        MaxCliqueSolver<MAXN> mis_solver(n, comp_adj);
        return mis_solver.solve(find_all);
    }

    vector<int> solve_mvc() { // TODO: return mvc for each mis
        // Get one Maximum Independent Set
        auto mis_results = solve_mis(false);
        if (mis_results.empty()) return {};
    
        // Create a bitset of the MIS for easy lookup
        bitset<MAXN> mis_bits;
        for (int node : mis_results[0]) mis_bits.set(node);
    
        // The MVC is every node NOT in the MIS
        vector<int> mvc;
        for (int i = 0; i < n; i++) {
            if (!mis_bits.test(i)) {
                mvc.push_back(i);
            }
        }
        return mvc;
    }
};

// --- Example Usage ---
int main() {
    // 5 nodes: A "House" graph (square 0-1-2-3 plus a triangle roof 2-3-4)
    int n = 5;
    MaxCliqueSolver<100> solver(n);

    // Square base
    solver.add_edge(0, 1);
    solver.add_edge(1, 2);
    solver.add_edge(2, 3);
    solver.add_edge(3, 0);
    // Triangle roof
    solver.add_edge(2, 4);
    solver.add_edge(3, 4);

    // 1. Get All Maximum Cliques
    auto cliques = solver.solve(true);
    cout << "--- Maximum Cliques ---" << endl;
    for (auto& c : cliques) {
        cout << "{ ";
        for (int node : c) cout << node << " ";
        cout << "}" << endl;
    }

    // 2. Get All Maximum Independent Sets
    auto miss = solver.solve_mis(true);
    cout << "\n--- Maximum Independent Sets ---" << endl;
    for (auto& is : miss) {
        cout << "{ ";
        for (int node : is) cout << node << " ";
        cout << "}" << endl;
    }

    return 0;
}
