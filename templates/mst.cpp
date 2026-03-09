#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const { return w < other.w; }
};

class DSU {
public:
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

class KruskalMST {
    int n;
    vector<Edge> edges;
public:
    KruskalMST(int n) : n(n) {}
    void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

    long long solve() {
        sort(edges.begin(), edges.end());
        DSU dsu(n);
        long long mst_weight = 0;
        int edges_count = 0;

        for (auto& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                mst_weight += edge.w;
                edges_count++;
            }
        }
        return (edges_count == n - 1) ? mst_weight : -1; // -1 if graph is disconnected
    }
};

class PrimMST {
    int n;
    vector<vector<pair<int, int>>> adj;
public:
    PrimMST(int n) : n(n), adj(n) {}
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    long long solve(int start_node = 0) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> min_w(n, INT_MAX);
        vector<bool> visited(n, false);
        long long mst_weight = 0;

        min_w[start_node] = 0;
        pq.push({0, start_node});

        while (!pq.empty()) {
            int u = pq.top().second;
            int w = pq.top().first;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;
            mst_weight += w;

            for (auto& edge : adj[u]) {
                int v = edge.first, weight = edge.second;
                if (!visited[v] && weight < min_w[v]) {
                    min_w[v] = weight;
                    pq.push({min_w[v], v});
                }
            }
        }
        return mst_weight;
    }
};

struct DirectedEdge { int u, v, w; };

class EdmondsMSA {
public:
    int n;
    vector<DirectedEdge> edges;
    EdmondsMSA(int n) : n(n) {}

    void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

    long long solve(int root) {
        long long res = 0;
        vector<int> min_in_edge(n), parent(n), id(n), visited(n);

        while (true) {
            fill(min_in_edge.begin(), min_in_edge.end(), INT_MAX);
            for (auto& e : edges) {
                if (e.u != e.v && e.w < min_in_edge[e.v]) {
                    min_in_edge[e.v] = e.w;
                    parent[e.v] = e.u;
                }
            }

            for (int i = 0; i < n; i++) {
                if (i != root && min_in_edge[i] == INT_MAX) return -1; // No MSA possible
            }

            int cycle_cnt = 0;
            fill(id.begin(), id.end(), -1);
            fill(visited.begin(), visited.end(), -1);
            min_in_edge[root] = 0;

            for (int i = 0; i < n; i++) {
                res += min_in_edge[i];
                int v = i;
                // Traverse back to find cycles
                while (visited[v] != i && id[v] == -1 && v != root) {
                    visited[v] = i;
                    v = parent[v];
                }
                if (v != root && id[v] == -1) {
                    for (int u = parent[v]; u != v; u = parent[u]) id[u] = cycle_cnt;
                    id[v] = cycle_cnt++;
                }
            }

            if (cycle_cnt == 0) break; // No cycles, we are done

            for (int i = 0; i < n; i++) {
                if (id[i] == -1) id[i] = cycle_cnt++;
            }

            // Contract nodes into cycles
            for (auto& e : edges) {
                int v = e.v;
                e.u = id[e.u];
                e.v = id[e.v];
                if (e.u != e.v) e.w -= min_in_edge[v];
            }
            n = cycle_cnt;
            root = id[root];
        }
        return res;
    }
};

class BoruvkaMST {
    struct Edge { int u, v, w; };
    int n;
    vector<Edge> edges;

public:
    BoruvkaMST(int n) : n(n) {}
    void addEdge(int u, int v, int w) { edges.push_back({u, v, w}); }

    long long solve() {
        DSU dsu(n); // Re-using the DSU class from the previous block
        int components = n;
        long long mst_weight = 0;

        while (components > 1) {
            vector<int> cheapest(n, -1);

            // Find cheapest edge for each component
            for (int i = 0; i < (int)edges.size(); i++) {
                int root_u = dsu.find(edges[i].u);
                int root_v = dsu.find(edges[i].v);
                if (root_u == root_v) continue;

                if (cheapest[root_u] == -1 || edges[i].w < edges[cheapest[root_u]].w)
                    cheapest[root_u] = i;
                if (cheapest[root_v] == -1 || edges[i].w < edges[cheapest[root_v]].w)
                    cheapest[root_v] = i;
            }

            bool added = false;
            for (int i = 0; i < n; i++) {
                if (cheapest[i] != -1) {
                    int root_u = dsu.find(edges[cheapest[i]].u);
                    int root_v = dsu.find(edges[cheapest[i]].v);
                    if (dsu.unite(root_u, root_v)) {
                        mst_weight += edges[cheapest[i]].w;
                        components--;
                        added = true;
                    }
                }
            }
            if (!added) break; // Graph is disconnected
        }
        return (components == 1) ? mst_weight : -1;
    }
};
