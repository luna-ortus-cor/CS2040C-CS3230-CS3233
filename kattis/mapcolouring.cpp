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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int C,B;
        cin>>C>>B;
        MapColour mc(C);
        for(int k=0;k<B;k++){
            int i,j;
            cin>>i>>j;
            mc.add_edge(i,j);
        }
        int K=mc.get_chromatic_number();
        cout<<(K<5?to_string(K):"many")<<"\n";
    }
    return 0;
}
