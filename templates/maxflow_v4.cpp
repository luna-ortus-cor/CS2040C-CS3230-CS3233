#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    int to, rev;
    ll cap, flow;
};

class PushRelabel {
private:
    int V;
    vector<vector<Edge>> adj;
    vector<ll> excess;
    vector<int> height, count;
    vector<vector<int>> buckets;
    vector<ll> balance; // For Node Demands
    int max_height;
    int work;

    // Periodically resets heights to exact distances from sink using BFS
    void global_relabel(int t) {
        height.assign(V, V);
        count.assign(V + 1, 0);
        for (int i = 0; i <= max_height; i++) buckets[i].clear();
        
        queue<int> q;
        q.push(t);
        height[t] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (adj[e.to][e.rev].cap - adj[e.to][e.rev].flow > 0 && height[e.to] == V) {
                    height[e.to] = height[u] + 1;
                    count[height[e.to]]++;
                    if (excess[e.to] > 0) {
                        buckets[height[e.to]].push_back(e.to);
                        max_height = max(max_height, height[e.to]);
                    }
                    q.push(e.to);
                }
            }
        }
        work = 0;
    }

    void push(int u, Edge &e) {
        ll delta = min(excess[u], e.cap - e.flow);
        if (height[u] <= height[e.to] || delta == 0) return;
        e.flow += delta;
        adj[e.to][e.rev].flow -= delta;
        excess[u] -= delta;
        excess[e.to] += delta;
        if (excess[e.to] > 0 && excess[e.to] <= delta) {
            buckets[height[e.to]].push_back(e.to);
            max_height = max(max_height, height[e.to]);
        }
    }

    void relabel(int u) {
        int min_h = 2 * V;
        for (auto &e : adj[u]) {
            if (e.cap - e.flow > 0) min_h = min(min_h, height[e.to]);
        }
        if (count[height[u]] == 1 && height[u] < V) {
            // Gap Heuristic: No path to sink exists for nodes at or above this height
            for (int i = 0; i < V; i++) {
                if (height[i] >= height[u] && height[i] < V) {
                    count[height[i]]--;
                    height[i] = V;
                }
            }
        } else {
            count[height[u]]--;
            height[u] = min_h + 1;
            count[height[u]]++;
            buckets[height[u]].push_back(u);
            max_height = max(max_height, height[u]);
        }
    }

    void discharge(int u) {
        while (excess[u] > 0) {
            for (auto &e : adj[u]) {
                if (excess[u] == 0) break;
                push(u, e);
            }
            if (excess[u] > 0) {
                relabel(u);
                if (work++ > V * 4) global_relabel(V - 1); // Trigger Global Relabel
            }
        }
    }

public:
    const ll INF = 1e18;

    PushRelabel(int n) : V(n), adj(n), excess(n, 0), height(n), 
                        count(n + 1), buckets(n), balance(n, 0) {}

    void add_edge(int u, int v, ll cap, ll low = 0) {
        if (u == v) return;
        balance[u] -= low;
        balance[v] += low;
        adj[u].push_back({v, (int)adj[v].size(), cap - low, 0});
        adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
    }

    ll max_flow(int s, int t) {
        excess[s] = INF;
        global_relabel(t);
        for (auto &e : adj[s]) push(s, e);
        
        for (; max_height >= 0; max_height--) {
            while (!buckets[max_height].empty()) {
                int u = buckets[max_height].back();
                buckets[max_height].pop_back();
                if (u != s && u != t) discharge(u);
            }
        }
        return excess[t];
    }

    // --- Utility Methods ---
    
    inline int in_node(int u) { return u * 2; }
    inline int out_node(int u) { return u * 2 + 1; }

    void add_node_capacity(int u, ll cap) {
        add_edge(in_node(u), out_node(u), cap);
    }

    vector<bool> min_cut(int s) {
        vector<bool> visited(V, false);
        queue<int> q; q.push(s); visited[s] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap - e.flow > 0 && !visited[e.to]) {
                    visited[e.to] = true; q.push(e.to);
                }
            }
        }
        return visited;
    }
};
