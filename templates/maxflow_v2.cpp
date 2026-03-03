#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    int from, to;
    ll cap, flow, demand;
    bool is_real; // To distinguish between problem edges and auxiliary demand edges
};

class max_flow {
private:
    int V;
    vector<Edge> EL;
    vector<vector<int>> AL;
    vector<int> d, last;
    vector<ll> balance; // For Node Demands (Supplies/Sinks)

    bool BFS(int s, int t) {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int idx : AL[u]) {
                auto& edge = EL[idx];
                if (edge.cap - edge.flow > 0 && d[edge.to] == -1) {
                    d[edge.to] = d[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return d[t] != -1;
    }

    ll DFS(int u, int t, ll pushed) {
        if (pushed == 0 || u == t) return pushed;
        for (int& cid = last[u]; cid < (int)AL[u].size(); ++cid) {
            int idx = AL[u][cid];
            auto& edge = EL[idx];
            if (d[u] + 1 != d[edge.to] || edge.cap - edge.flow == 0) continue;
            ll tr = DFS(edge.to, t, min(pushed, edge.cap - edge.flow));
            if (tr == 0) continue;
            EL[idx].flow += tr;
            EL[idx ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

public:
    const ll INF = 1e18;

    // For N logical nodes, initialV should be 2*N + 2
    max_flow(int initialV) : V(initialV) {
        AL.assign(V, vector<int>());
        balance.assign(V, 0);
    }

    // --- Core Methods ---

    int add_edge(int u, int v, ll cap, ll low = 0, bool directed = true, bool real = true) {
        if (u == v) return -1;
        // Handle Edge Demand
        balance[u] -= low;
        balance[v] += low;
        
        int id = (int)EL.size();
        AL[u].push_back(id);
        EL.push_back({u, v, cap - low, 0, low, real});
        AL[v].push_back(id + 1);
        EL.push_back({v, u, directed ? 0 : cap - low, 0, directed ? 0 : low, real});
        return id;
    }

    ll dinic(int s, int t) {
        ll mf = 0;
        while (BFS(s, t)) {
            last.assign(V, 0);
            while (ll f = DFS(s, t, INF)) mf += f;
        }
        return mf;
    }

    // --- Demand & Balance Utilities ---

    void add_node_balance(int u, ll b) { balance[u] += b; }

    // Solves for feasibility and returns {is_feasible, max_flow_value}
    pair<bool, ll> solve_demands(int s = -1, int t = -1) {
        int S_prime = V - 2, T_prime = V - 1;
        int ts_idx = -1;
        if (s != -1 && t != -1) ts_idx = add_edge(t, s, INF, 0, true, false);

        ll needed = 0;
        for (int i = 0; i < V - 2; ++i) {
            if (balance[i] > 0) { add_edge(S_prime, i, balance[i], 0, true, false); needed += balance[i]; }
            else if (balance[i] < 0) { add_edge(i, T_prime, -balance[i], 0, true, false); }
        }

        if (dinic(S_prime, T_prime) != needed) return {false, 0};
        if (s == -1 || t == -1) return {true, 0};

        ll flow_val = EL[ts_idx].flow;
        remove_edge(ts_idx); // Remove auxiliary cycle edge
        return {true, flow_val + dinic(s, t)};
    }

    // --- Node Capacity Helpers ---

    inline int in_node(int u) { return u * 2; }
    inline int out_node(int u) { return u * 2 + 1; }

    int add_node_capacity(int u, ll cap) {
        return add_edge(in_node(u), out_node(u), cap);
    }

    // --- Manipulation & Retrieval ---

    void reset_flow() { for (auto& e : EL) e.flow = 0; }

    void change_capacity(int edge_id, ll new_cap) {
        EL[edge_id].cap = new_cap - EL[edge_id].demand;
    }

    void remove_edge(int edge_id) {
        if (edge_id < 0) return;
        EL[edge_id].cap = EL[edge_id ^ 1].cap = 0;
        EL[edge_id].flow = EL[edge_id ^ 1].flow = 0;
    }

    // To "delete" a node, we kill the edge connecting its split halves
    void remove_node(int u) {
        // This assumes you used add_node_capacity(u, ...)
        for (int idx : AL[in_node(u)]) {
            if (EL[idx].to == out_node(u)) remove_edge(idx);
        }
    }

    ll get_edge_flow(int edge_id) { 
        return EL[edge_id].flow + EL[edge_id].demand; 
    }

    ll get_node_flow(int u) {
        // Total flow through node u is the flow across its internal split edge
        for (int idx : AL[in_node(u)]) {
            if (EL[idx].to == out_node(u)) return get_edge_flow(idx);
        }
        return 0;
    }

    vector<bool> min_cut(int s) {
        vector<bool> visited(V, false);
        queue<int> q; q.push(s); visited[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int idx : AL[u]) {
                if (EL[idx].cap - EL[idx].flow > 0 && !visited[EL[idx].to]) {
                    visited[EL[idx].to] = true; q.push(EL[idx].to);
                }
            }
        }
        return visited;
    }
};
