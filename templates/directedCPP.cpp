#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e15;

// Min-Cost Max-Flow using SPFA
struct MCMF {
    struct Edge {
        int to;
        ll cap, flow, cost;
        int rev;
    };
    vector<vector<Edge>> adj;
    vector<ll> dist;
    vector<int> p_node, p_edge;
    int n, s, t;

    MCMF(int n, int s, int t) : n(n), s(s), t(t), adj(n), dist(n), p_node(n), p_edge(n) {}

    void add_edge(int u, int v, ll cap, ll cost) {
        adj[u].push_back({v, cap, 0, cost, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, -cost, (int)adj[u].size() - 1});
    }

    bool spfa(ll &flow, ll &cost) {
        dist.assign(n, INF);
        vector<bool> in_q(n, false);
        queue<int> q;
        dist[s] = 0; q.push(s); in_q[s] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop(); in_q[u] = false;
            for (int i = 0; i < (int)adj[u].size(); i++) {
                Edge &e = adj[u][i];
                if (e.cap > e.flow && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    p_node[e.to] = u; p_edge[e.to] = i;
                    if (!in_q[e.to]) { q.push(e.to); in_q[e.to] = true; }
                }
            }
        }
        if (dist[t] == INF) return false;

        ll push = INF;
        for (int v = t; v != s; v = p_node[v]) {
            push = min(push, adj[p_node[v]][p_edge[v]].cap - adj[p_node[v]][p_edge[v]].flow);
        }
        flow += push;
        cost += push * dist[t];
        for (int v = t; v != s; v = p_node[v]) {
            adj[p_node[v]][p_edge[v]].flow += push;
            adj[v][adj[p_node[v]][p_edge[v]].rev].flow -= push;
        }
        return true;
    }
};

struct DirectedCPP {
    int n;
    ll total_weight = 0;
    vector<vector<ll>> dist;
    vector<vector<int>> parent;
    vector<vector<int>> multi_adj; // Multigraph for Hierholzer
    vector<int> in_deg, out_deg;

    DirectedCPP(int n) : n(n), dist(n, vector<ll>(n, INF)), 
                         parent(n, vector<int>(n, -1)), 
                         multi_adj(n), in_deg(n, 0), out_deg(n, 0) {
        for (int i = 0; i < n; i++) dist[i][i] = 0;
    }

    void add_edge(int u, int v, ll w) {
        // For shortest paths, we only care about the cheapest direct edge
        if (w < dist[u][v]) {
            dist[u][v] = w;
            parent[u][v] = u; 
        }
        out_deg[u]++;
        in_deg[v]++;
        total_weight += w;
        multi_adj[u].push_back(v);
    }

    void add_path(int u, int v) {
        int curr = v;
        while (curr != u) {
            int p = parent[u][curr];
            if (p == -1) break; 
            multi_adj[p].push_back(curr);
            curr = p;
        }
    }

    ll solve() {
        // 1. Floyd-Warshall to find shortest paths between all imbalanced nodes
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            parent[i][j] = parent[k][j]; // Path reconstruction
                        }
                    }
                }
            }
        }

        int s = n, t = n + 1;
        MCMF mcmf(n + 2, s, t);
        vector<int> sources, sinks;

        for (int i = 0; i < n; i++) {
            int balance = out_deg[i] - in_deg[i];
            if (balance > 0) {
                mcmf.add_edge(s, i, balance, 0);
                sources.push_back(i);
            } else if (balance < 0) {
                mcmf.add_edge(i, t, -balance, 0);
                sinks.push_back(i);
            }
        }

        // Only connect supply nodes to demand nodes via shortest paths
        for (int u : sources) {
            for (int v : sinks) {
                if (dist[u][v] < INF) {
                    mcmf.add_edge(u, v, INF, dist[u][v]);
                }
            }
        }

        ll flow = 0, extra_cost = 0;
        while (mcmf.spfa(flow, extra_cost));

        // 2. Augment the multigraph by tracing the flow paths
        for (int u : sources) {
            for (auto &e : mcmf.adj[u]) {
                if (e.to < n && e.flow > 0) {
                    for (int f = 0; f < e.flow; f++) {
                        add_path(u, e.to);
                    }
                }
            }
        }

        return total_weight + extra_cost;
    }

    // Hierholzer's Algorithm for Directed Eulerian Circuit
    vector<int> get_path(int start_node = 0) {
        vector<int> path;
        stack<int> st;
        st.push(start_node);
        
        // Use a local copy of adj to avoid destroying the state if needed
        auto temp_adj = multi_adj;

        while (!st.empty()) {
            int u = st.top();
            if (!temp_adj[u].empty()) {
                int v = temp_adj[u].back();
                temp_adj[u].pop_back();
                st.push(v);
            } else {
                path.push_back(u);
                st.pop();
            }
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
//need to check/test this 
