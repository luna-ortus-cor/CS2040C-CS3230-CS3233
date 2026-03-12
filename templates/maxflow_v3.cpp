#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    int from, to;
    ll cap, flow;
};

class max_flow {
private:
    int V;
    vector<Edge> EL;
    vector<vector<int>> AL;
    vector<ll> excess;
    vector<int> height, count;
    vector<vector<int>> buckets;
    int max_height;

    void update_height(int u, int new_h) {
        if (height[u] != V + 1) count[height[u]]--;
        height[u] = new_h;
        if (new_h <= V) {
            count[new_h]++;
            buckets[new_h].push_back(u);
            max_height = max(max_height, new_h);
        }
    }

    void global_relabel(int t) {
        height.assign(V, V + 1);
        count.assign(V + 1, 0);
        for (int i = 0; i <= max_height; i++) buckets[i].clear();
        max_height = 0;

        queue<int> q;
        q.push(t);
        height[t] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int idx : AL[u]) {
                if (EL[idx ^ 1].cap - EL[idx ^ 1].flow > 0 && height[EL[idx].to] == V + 1) {
                    update_height(EL[idx].to, height[u] + 1);
                    q.push(EL[idx].to);
                }
            }
        }
    }

    void push(int u, int idx) {
        Edge &e = EL[idx];
        if (excess[u] == 0 || height[u] != height[e.to] + 1) return;
        ll delta = min(excess[u], e.cap - e.flow);
        e.flow += delta;
        EL[idx ^ 1].flow -= delta;
        excess[u] -= delta;
        excess[e.to] += delta;
        if (excess[e.to] > 0 && excess[e.to] <= delta) {
            buckets[height[e.to]].push_back(e.to);
        }
    }

    void discharge(int u) {
        int next_h = V;
        for (int idx : AL[u]) {
            if (EL[idx].cap - EL[idx].flow > 0) {
                if (height[u] == height[EL[idx].to] + 1) {
                    push(u, idx);
                    if (excess[u] <= 0) return;
                } else {
                    next_h = min(next_h, height[EL[idx].to] + 1);
                }
            }
        }
        
        // Gap Heuristic
        if (count[height[u]] == 1) {
            for (int i = 0; i < V; i++) {
                if (height[i] > height[u] && height[i] < V) {
                    update_height(i, V + 1);
                }
            }
        }
        update_height(u, next_h);
    }

public:
    const ll INF = 1e18;

    max_flow(int initialV) : V(initialV) {
        AL.assign(V, vector<int>());
        excess.assign(V, 0);
        height.assign(V, 0);
        buckets.assign(V + 1, vector<int>());
    }

    int add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return -1;
        int id = (int)EL.size();
        AL[u].push_back(id);
        EL.push_back({u, v, w, 0});
        AL[v].push_back(id + 1);
        EL.push_back({v, u, directed ? 0 : w, 0});
        return id;
    }

    ll solve(int s, int t) {
        excess.assign(V, 0);
        excess[s] = INF;
        global_relabel(t);
        
        for (int idx : AL[s]) push(s, idx);

        for (; max_height >= 0; max_height--) {
            while (!buckets[max_height].empty()) {
                int u = buckets[max_height].back();
                buckets[max_height].pop_back();
                if (u != s && u != t && excess[u] > 0) {
                    discharge(u);
                }
            }
        }
        return excess[t];
    }

    // --- Utilities ---

    void reset_flow() { for (auto& e : EL) e.flow = 0; }

    ll get_flow(int edge_id) { return (edge_id >= 0) ? EL[edge_id].flow : 0; }

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
