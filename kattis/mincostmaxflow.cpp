#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    int to;
    ll cap, flow, cost, demand;
    int rev; // Index of the reverse edge in AL[to]
};

class min_cost_max_flow {
private:
    int V;
    vector<vector<Edge>> AL;
    vector<ll> d, pot, balance;
    vector<int> parent_v, parent_e;

    // SPFA to handle initial negative costs and build potentials
    bool spfa(int s, int t) {
        d.assign(V, INF);
        parent_v.assign(V, -1);
        parent_e.assign(V, -1);
        vector<bool> in_queue(V, false);
        queue<int> q;

        d[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            in_queue[u] = false;
            for (int i = 0; i < (int)AL[u].size(); ++i) {
                Edge &e = AL[u][i];
                if (e.cap - e.flow > 0 && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    parent_v[e.to] = u;
                    parent_e[e.to] = i;
                    if (!in_queue[e.to]) {
                        q.push(e.to);
                        in_queue[e.to] = true;
                    }
                }
            }
        }
        return d[t] != INF;
    }

public:
    const ll INF = 1e18;

    min_cost_max_flow(int initialV) : V(initialV) {
        AL.assign(V, vector<Edge>());
        balance.assign(V, 0);
    }

    // --- Core Methods ---

    void add_edge(int u, int v, ll cap, ll cost, ll low = 0) {
        if (u == v) return;
        // Edge Demand Transformation
        balance[u] -= low;
        balance[v] += low;
        
        AL[u].push_back({v, cap - low, 0, cost, low, (int)AL[v].size()});
        AL[v].push_back({u, 0, 0, -cost, 0, (int)AL[u].size() - 1});
    }

    void add_node_balance(int u, ll b) {
        balance[u] += b;
    }

    inline int in_node(int u) { return u * 2; }
    inline int out_node(int u) { return u * 2 + 1; }

    void add_node_capacity(int u, ll cap, ll cost = 0) {
        add_edge(in_node(u), out_node(u), cap, cost);
    }

    // Returns {total_flow, total_cost}
    pair<ll, ll> solve_mcmf(int s, int t) {
        int S_prime = V - 2, T_prime = V - 1;
        ll total_flow = 0;
        ll total_cost = 0;

        // 1. Handle Demands/Balances first
        // Connect t -> s with INF capacity and 0 cost to allow circulation
        add_edge(t, s, INF, 0); 
        
        ll needed_flow = 0;
        for (int i = 0; i < V - 2; ++i) {
            if (balance[i] > 0) {
                add_edge(S_prime, i, balance[i], 0);
                needed_flow += balance[i];
            } else if (balance[i] < 0) {
                add_edge(i, T_prime, -balance[i], 0);
            }
        }

        // 2. Solve for Feasibility (satisfying all demands at min cost)
        while (spfa(S_prime, T_prime)) {
            ll push = INF;
            for (int v = T_prime; v != S_prime; v = parent_v[v]) {
                int u = parent_v[v];
                int idx = parent_e[v];
                push = min(push, AL[u][idx].cap - AL[u][idx].flow);
            }
            for (int v = T_prime; v != S_prime; v = parent_v[v]) {
                int u = parent_v[v];
                int idx = parent_e[v];
                AL[u][idx].flow += push;
                int rev_idx = AL[u][idx].rev;
                AL[v][rev_idx].flow -= push;
                total_cost += push * AL[u][idx].cost;
            }
        }

        // Note: Check if needed_flow was met if feasibility is required.
        
        // 3. Maximize flow from s to t (already found min cost for demand)
        while (spfa(s, t)) {
            ll push = INF;
            for (int v = t; v != s; v = parent_v[v]) {
                int u = parent_v[v];
                int idx = parent_e[v];
                push = min(push, AL[u][idx].cap - AL[u][idx].flow);
            }
            total_flow += push;
            for (int v = t; v != s; v = parent_v[v]) {
                int u = parent_v[v];
                int idx = parent_e[v];
                AL[u][idx].flow += push;
                int rev_idx = AL[u][idx].rev;
                AL[v][rev_idx].flow -= push;
                total_cost += push * AL[u][idx].cost;
            }
        }

        // Add the cost of pre-filled demands
        for (auto &row : AL) {
            for (auto &e : row) {
                if (e.demand > 0) total_cost += e.demand * e.cost;
            }
        }

        return {total_flow, total_cost};
    }

    ll get_actual_flow(int u, int edge_idx) {
        return AL[u][edge_idx].flow + AL[u][edge_idx].demand;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N,M,S,T;
    cin>>N>>M>>S>>T;
    min_cost_max_flow mf(N+2);
    for(int i=0;i<M;i++){
        int u,v;
        ll cap,cost;
        cin>>u>>v>>cap>>cost;
        mf.add_edge(u,v,cap,cost);
    }
    pair<ll,ll> result=mf.solve_mcmf(S,T);
    cout<<result.first<<" "<<result.second;
    return 0;
}
