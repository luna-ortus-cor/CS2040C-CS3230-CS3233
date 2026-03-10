#include <bits/stdc++.h>
using namespace std;

class EulerianSolver {
public:
    enum GraphType { DIRECTED, UNDIRECTED };

private:
    struct Edge {
        int to;
        bool used;
        int rev_idx; 
    };

    int n;
    GraphType type;
    vector<vector<Edge>> adj;
    vector<int> in_degree, out_degree;
    vector<int> parent; // For DSU connectivity check

    // DSU helper functions
    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) parent[b] = a;
    }

    bool is_connected() {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);

        int nodes_with_edges = 0;
        int start_node = -1;

        // Group all nodes that share an edge
        for (int u = 0; u < n; u++) {
            if (out_degree[u] > 0 || (type == DIRECTED && in_degree[u] > 0)) {
                if (start_node == -1) start_node = u;
                nodes_with_edges++;
                for (auto &e : adj[u]) union_sets(u, e.to);
            }
        }

        if (start_node == -1) return true; // Empty graph is technically Eulerian

        // Verify all nodes with edges belong to the same DSU component
        int root = find_set(start_node);
        for (int i = 0; i < n; i++) {
            if (out_degree[i] > 0 || (type == DIRECTED && in_degree[i] > 0)) {
                if (find_set(i) != root) return false;
            }
        }
        return true;
    }

public:
    EulerianSolver(int n, GraphType type) : n(n), type(type) {
        adj.resize(n);
        in_degree.assign(n, 0);
        out_degree.assign(n, 0);
    }

    void addEdge(int u, int v) {
        if (type == DIRECTED) {
            adj[u].push_back({v, false, -1});
            out_degree[u]++;
            in_degree[v]++;
        } else {
            int u_idx = adj[u].size();
            int v_idx = adj[v].size();
            adj[u].push_back({v, false, v_idx});
            adj[v].push_back({u, false, u_idx});
            out_degree[u]++; 
            out_degree[v]++;
        }
    }

    // Returns start node if Eulerian, else -1
    int get_start_node() {
        if (!is_connected()) return -1;

        if (type == DIRECTED) {
            int start_node = -1, end_node = -1;
            int potential_circuit_start = -1;

            for (int i = 0; i < n; i++) {
                if (out_degree[i] > 0 && potential_circuit_start == -1) potential_circuit_start = i;
                
                if (out_degree[i] - in_degree[i] == 1) {
                    if (start_node != -1) return -1; // Multiple potential starts
                    start_node = i;
                } else if (in_degree[i] - out_degree[i] == 1) {
                    if (end_node != -1) return -1; // Multiple potential ends
                    end_node = i;
                } else if (in_degree[i] != out_degree[i]) {
                    return -1;
                }
            }
            if (start_node != -1 && end_node != -1) return start_node; // Path
            if (start_node == -1 && end_node == -1) return potential_circuit_start; // Circuit
            return -1;
        } else {
            int odd = 0, first_odd = -1, first_even = -1;
            for (int i = 0; i < n; i++) {
                if (out_degree[i] > 0 && first_even == -1) first_even = i;
                if (out_degree[i] % 2 != 0) {
                    odd++;
                    if (first_odd == -1) first_odd = i;
                }
            }
            if (odd == 0) return first_even; // Circuit
            if (odd == 2) return first_odd; // Path
            return -1;
        }
    }

    vector<int> getTour() {
        int s = get_start_node();
        if (s == -1) return {}; // No tour exists

        vector<int> tour;
        stack<int> st;
        vector<int> current_ptr(n, 0);
        st.push(s);

        while (!st.empty()) {
            int u = st.top();
            bool found = false;
            while (current_ptr[u] < (int)adj[u].size()) {
                Edge &e = adj[u][current_ptr[u]++];
                if (e.used) continue;
                e.used = true;
                if (type == UNDIRECTED) adj[e.to][e.rev_idx].used = true;
                st.push(e.to);
                found = true;
                break;
            }
            if (!found) {
                tour.push_back(u);
                st.pop();
            }
        }
        reverse(tour.begin(), tour.end());
        return tour;
    }
};

int main() {
    EulerianSolver es(8, EulerianSolver::DIRECTED);
    es.addEdge(0, 1); es.addEdge(0, 6);
    es.addEdge(1, 2);
    es.addEdge(2, 3); es.addEdge(2, 4);
    es.addEdge(3, 0);
    es.addEdge(4, 5);
    es.addEdge(5, 0); es.addEdge(5, 2);
    es.addEdge(6, 5);
    es.addEdge(7, 6);

    vector<int> ans = es.getTour();
    
    cout << "Directed Tour: ";
    if (ans.empty()) {
        cout << -1 << endl;
    } else {
        for (int u : ans) cout << u << " ";
        cout << endl;
    }

    // Undirected Example
    EulerianSolver us(4, EulerianSolver::UNDIRECTED);
    us.addEdge(0, 1); us.addEdge(1, 2); 
    us.addEdge(2, 3); us.addEdge(3, 0);
    us.addEdge(0, 2); // Makes it an Eulerian Path, not Circuit
    
    ans = us.getTour();
    cout << "Undirected Tour: ";
    if (ans.empty()) {
        cout << -1 << endl;
    } else {
        for (int v : ans) cout << v << " ";
        cout << endl;
    }
    
    return 0;
}
