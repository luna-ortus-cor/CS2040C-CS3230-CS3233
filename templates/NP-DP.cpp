#include <bits/stdc++.h>
using namespace std;

template<int MAXN>
struct SubsetPartitionSolver {
    int n;
    int dp[1 << MAXN];
    int parent[1 << MAXN];
    // Optimization: masks_containing[i] stores valid masks 
    // whose LOWEST set bit is i.
    vector<int> masks_containing[MAXN];

    SubsetPartitionSolver(int n) : n(n) {
        fill(dp, dp + (1 << n), 1e9);
        fill(parent, parent + (1 << n), 0);
        for(int i = 0; i < n; i++) masks_containing[i].clear();
    }

    // Step 1: Generate valid masks and sort them into buckets for the DP
    void find_valid_subsets(const function<bool(int)>& is_valid) {
        for (int mask = 1; mask < (1 << n); mask++) {
            if (is_valid(mask)) {
                // We bucket by the lowest bit to satisfy the 
                // "first_free" requirement in the DP loop.
                masks_containing[__builtin_ctz(mask)].push_back(mask);
            }
        }
    }

    // Step 2: Solve with O(2^N * Avg_Subsets_Per_Bit)
    int solve() {
        dp[0] = 0;
        int full_mask = (1 << n) - 1;
        for (int mask = 0; mask < full_mask; mask++) {
            if (dp[mask] == 1e9) continue;

            // Find the index of the first '0' bit (the next person to pick up)
            int first_free = __builtin_ctz(~mask);

            // We ONLY check masks that can fill this specific hole
            for (int sub : masks_containing[first_free]) {
                if (mask & sub) continue; // Must be disjoint

                int next_mask = mask | sub;
                if (dp[next_mask] > dp[mask] + 1) {
                    dp[next_mask] = dp[mask] + 1;
                    parent[next_mask] = sub;
                }
            }
        }
        return dp[full_mask];
    }

    vector<vector<int>> get_groups() {
        vector<vector<int>> groups;
        int curr = (1 << n) - 1;
        if (dp[curr] == 1e9) return {}; // No solution

        while (curr > 0) {
            int sub = parent[curr];
            vector<int> group;
            for (int i = 0; i < n; i++)
                if ((sub >> i) & 1) group.push_back(i);
            groups.push_back(group);
            curr ^= sub;
        }
        return groups;
    }
};

//min independent set cover (+ capacity)
solver.find_valid_subsets([&](int mask) {
    if (__builtin_popcount(mask) > C) return false;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            if (adj[i] & mask) return false; // Conflict edge
        }
    }
    return true;
});

//clique cover
solver.find_valid_subsets([&](int mask) {
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) {
            // Every node in mask must be connected to every other node in mask
            if ((adj[i] & mask) != (mask ^ (1 << i))) return false;
        }
    }
    return true;
});

//bin packing (+ capacity/weight constraint)
solver.find_valid_subsets([&](int mask) {
    long long current_weight = 0;
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1) current_weight += weights[i];
    }
    return current_weight <= MAX_CAPACITY;
});

//min bipartite partition
solver.find_valid_subsets([&](int mask) {
    // Check if the subgraph induced by 'mask' is bipartite
    // Standard BFS/DFS 2-coloring within the mask
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++) {
        if (!((mask >> i) & 1) || color[i] != -1) continue;
        
        queue<int> q; q.push(i); color[i] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : adj_list[u]){
                if(!((mask >> v) & 1)) continue;
                if(color[v] == -1){
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if(color[v] == color[u]) return false;
            }
        }
    }
    return true;
});

//min star partition
solver.find_valid_subsets([&](int mask) {
    if (__builtin_popcount(mask) == 1) return true;
    for (int center = 0; center < n; center++) {
        if (!((mask >> center) & 1)) continue;
        // Everyone in mask (except center) must be adjacent to center
        int others = mask ^ (1 << center);
        if ((adj[center] & others) == others) return true;
    }
    return false;
});

//min distance partition
solver.find_valid_subsets([&](int mask) {
    vector<int> idx;
    for(int i=0; i<n; i++) if((mask >> i) & 1) idx.push_back(i);
    
    for(int i=0; i<idx.size(); i++) {
        for(int j=i+1; j<idx.size(); j++) {
            if (dist(points[idx[i]], points[idx[j]]) < D) return false;
        }
    }
    return true;
});

//min disjoint path cover
solver.find_valid_subsets([&](int mask) {
    int nodes = __builtin_popcount(mask);
    if (nodes == 1) return true; // A single node is a path of length 0

    int edges = 0;
    for (int i = 0; i < n; i++) {
        if (!((mask >> i) & 1)) continue;
        
        int degree = __builtin_popcount(adj[i] & mask);
        if (degree > 2) return false; // Not a path if any node has 3+ neighbors
        edges += degree;
    }
    edges /= 2; // Each edge was counted twice

    // Path condition: Connected, max degree 2, and |E| = |V| - 1
    if (edges != nodes - 1) return false;

    // Connectivity Check (BFS/DFS within the mask)
    int start_node = __builtin_ctz(mask);
    int visited_mask = 0;
    queue<int> q;
    q.push(start_node);
    visited_mask |= (1 << start_node);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        int neighbors = adj[u] & mask;
        while (neighbors > 0) {
            int v = __builtin_ctz(neighbors);
            if (!((visited_mask >> v) & 1)) {
                visited_mask |= (1 << v);
                q.push(v);
            }
            neighbors &= ~(1 << v);
        }
    }

    return visited_mask == mask;
});

//set cover
// Example: N items, M input subsets
int N, M;
cin >> N >> M;
SubsetPartitionSolver<20> solver(N);

for (int i = 0; i < M; i++) {
    int input_mask = 0;
    int set_size; cin >> set_size;
    while(set_size--) {
        int item; cin >> item; // 0-indexed
        input_mask |= (1 << item);
    }
    // Directly add the provided subsets to the solver's buckets
    if (input_mask > 0) {
        solver.masks_containing[__builtin_ctz(input_mask)].push_back(input_mask);
    }
}
