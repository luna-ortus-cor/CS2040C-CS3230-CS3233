#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct TSPSolver {
    int n;
    const ll INF = 1e18;
    vector<vector<ll>> dist;
    vector<vector<ll>> dp;
    vector<ll> stay_time;
    vector<vector<int>> parent; // To store which node v led to u

    TSPSolver(int nodes) : n(nodes) {
        dist.assign(n, vector<ll>(n, INF));
        stay_time.assign(n, 0);
        for (int i = 0; i < n; i++) dist[i][i] = 0;
    }

    void set_stay_time(int u, ll t) { stay_time[u] = t; }

    void add_edge(int u, int v, ll w, bool directed = false) {
        dist[u][v] = min(dist[u][v], w);
        if (!directed) dist[v][u] = min(dist[v][u], w);
    }
    
    void compute_shortest_paths() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }

    // --- Cycle TSP (Start and End at 0) ---
    ll solve_cycle() {
        if (n <= 1) return 0;
        dp.assign(1 << n, vector<ll>(n, INF));
        parent.assign(1 << n, vector<int>(n, -1));
        
        dp[1][0] = stay_time[0];

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (dp[mask][u] == INF) continue;
                for (int v = 0; v < n; v++) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        ll new_dist = dp[mask][u] + dist[u][v] + stay_time[v];
                        if (new_dist < dp[next_mask][v]) {
                            dp[next_mask][v] = new_dist;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }

        ll min_total = INF;
        int last_node = -1;
        for (int i = 1; i < n; i++) {
            if (dp[(1 << n) - 1][i] + dist[i][0] < min_total) {
                min_total = dp[(1 << n) - 1][i] + dist[i][0];
                last_node = i;
            }
        }
        return min_total;
    }

    vector<int> get_cycle_path() {
        // Find the best last node first (must match logic in solve_cycle)
        ll min_total = INF;
        int curr = -1;
        for (int i = 1; i < n; i++) {
            if (dp[(1 << n) - 1][i] + dist[i][0] < min_total) {
                min_total = dp[(1 << n) - 1][i] + dist[i][0];
                curr = i;
            }
        }

        if (curr == -1) return {};

        vector<int> path;
        int mask = (1 << n) - 1;
        while (curr != -1) {
            path.push_back(curr);
            int prev = parent[mask][curr];
            mask ^= (1 << curr);
            curr = prev;
        }
        reverse(path.begin(), path.end());
        path.push_back(0); // Explicitly close the cycle
        return path;
    }

    // --- Open TSP (Hamiltonian Path) ---
    ll solve_open() {
        if (n <= 1) return 0;
        dp.assign(1 << n, vector<ll>(n, INF));
        parent.assign(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n; i++) dp[1 << i][i] = stay_time[i];

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int u = 0; u < n; u++) {
                if (dp[mask][u] == INF) continue;
                for (int v = 0; v < n; v++) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        ll new_dist = dp[mask][u] + dist[u][v] + stay_time[v];
                        if (new_dist < dp[next_mask][v]) {
                            dp[next_mask][v] = new_dist;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }

        ll min_total = INF;
        for (int i = 0; i < n; i++) min_total = min(min_total, dp[(1 << n) - 1][i]);
        return min_total;
    }

    // Modified solve_open to accept a starting node
    ll solve_open(int start_node) {
        if (n <= 1) return (n == 1 ? stay_time[0] : 0);
        
        dp.assign(1 << n, vector<ll>(n, INF));
        parent.assign(1 << n, vector<int>(n, -1));
    
        // Base case: Only the start_node is visited
        // We pay the stay_time of the first node
        dp[1 << start_node][start_node] = stay_time[start_node];
    
        for (int mask = 1; mask < (1 << n); mask++) {
            // Optimization: Only process masks that actually contain the start_node
            if (!(mask & (1 << start_node))) continue;
    
            for (int u = 0; u < n; u++) {
                if (dp[mask][u] == INF) continue;
                
                for (int v = 0; v < n; v++) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        ll new_dist = dp[mask][u] + dist[u][v] + stay_time[v];
                        if (new_dist < dp[next_mask][v]) {
                            dp[next_mask][v] = new_dist;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }
    
        ll min_total = INF;
        for (int i = 0; i < n; i++) {
            min_total = min(min_total, dp[(1 << n) - 1][i]);
        }
        return min_total;
    }

    vector<int> get_open_path() {
        ll min_total = INF;
        int curr = -1;
        for (int i = 0; i < n; i++) {
            if (dp[(1 << n) - 1][i] < min_total) {
                min_total = dp[(1 << n) - 1][i];
                curr = i;
            }
        }

        if (curr == -1) return {}; // No path found

        vector<int> path;
        int mask = (1 << n) - 1;
        while (curr != -1) {
            path.push_back(curr);
            int prev = parent[mask][curr];
            mask ^= (1 << curr);
            curr = prev;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> get_open_path(int start_node) {
        ll min_total = INF;
        int curr = -1;
    
        for (int i = 0; i < n; i++) {
            if (dp[(1 << n) - 1][i] < min_total) {
                min_total = dp[(1 << n) - 1][i];
                curr = i;
            }
        }
    
        if (curr == -1) return {}; // No path found
    
        vector<int> path;
        int mask = (1 << n) - 1;
    
        while (curr != -1) {
            path.push_back(curr);
            int prev = parent[mask][curr];
            mask ^= (1 << curr); // Remove current node from the mask
            curr = prev;
        }

        reverse(path.begin(), path.end());
        return path;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m,s;
    cin>>n>>m>>s;
    TSPSolver tsp(n);
    vector<int> times(n);
    for(int i=0;i<n;i++){
        cin>>times[i];
        tsp.set_stay_time(i,times[i]);
    }
    for(int i=0;i<m;i++){
        int u,v,t;
        cin>>u>>v>>t;
        tsp.add_edge(u-1,v-1,t);
    }
    tsp.compute_shortest_paths();
    ll ans=tsp.solve_open(0);
    sort(times.begin(),times.end());
    ans-=accumulate(times.end()-s,times.end(),0LL);
    cout<<ans;
    return 0;
}
