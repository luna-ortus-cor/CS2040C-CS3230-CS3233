#include <bits/stdc++.h>
using namespace std;

class EulerianSolver {
public:
    enum GraphType { DIRECTED, UNDIRECTED };

private:
    struct Edge {
        int to;
        bool used;
        int rev_idx; // Only needed for Undirected
    };

    int n;
    GraphType type;
    vector<vector<Edge>> adj;
    vector<int> in_degree, out_degree;
    vector<int> ptr; // For O(E) traversal

public:
    EulerianSolver(int n, GraphType type) : n(n), type(type) {
        adj.resize(n);
        in_degree.assign(n, 0);
        out_degree.assign(n, 0);
        ptr.assign(n, 0);
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
            out_degree[u]++; // In undirected, we treat "degree" as out_degree
            out_degree[v]++;
        }
    }

    // Checks if Eulerian Circuit/Path is possible based on degrees
    int checkEulerian() {
        if (type == DIRECTED) {
            int start_nodes = 0, end_nodes = 0;
            for (int i = 0; i < n; i++) {
                if (out_degree[i] - in_degree[i] == 1) start_nodes++;
                else if (in_degree[i] - out_degree[i] == 1) end_nodes++;
                else if (in_degree[i] != out_degree[i]) return -1; // Impossible
            }
            if (start_nodes == 0 && end_nodes == 0) return 1; // Circuit
            if (start_nodes == 1 && end_nodes == 1) return 2; // Path
            return -1;
        } else {
            int odd = 0;
            for (int i = 0; i < n; i++) if (out_degree[i] % 2 != 0) odd++;
            if (odd == 0) return 1; // Circuit
            if (odd == 2) return 2; // Path
            return -1;
        }
    }

    vector<int> getTour(int start_node) {
        if (checkEulerian() == -1) return {};

        vector<int> tour;
        stack<int> st;
        st.push(start_node);

        while (!st.empty()) {
            int u = st.top();
            bool found_edge = false;

            while (ptr[u] < (int)adj[u].size()) {
                Edge &e = adj[u][ptr[u]++];
                if (e.used) continue;

                e.used = true;
                if (type == UNDIRECTED) {
                    adj[e.to][e.rev_idx].used = true;
                }

                st.push(e.to);
                found_edge = true;
                break;
            }

            if (!found_edge) {
                tour.push_back(u);
                st.pop();
            }
        }

        reverse(tour.begin(), tour.end());
        return tour;
    }
};

int main() {
    // Directed Example from your query
    EulerianSolver ds(7, EulerianSolver::DIRECTED);
    ds.addEdge(0, 1); ds.addEdge(0, 6);
    ds.addEdge(1, 2);
    ds.addEdge(2, 3); ds.addEdge(2, 4);
    ds.addEdge(3, 0);
    ds.addEdge(4, 5);
    ds.addEdge(5, 0); ds.addEdge(5, 2);
    ds.addEdge(6, 5);

    vector<int> tour = ds.getTour(0);
    cout << "Directed Tour: ";
    for (int v : tour) cout << v << " ";
    cout << endl;

    // Undirected Example
    EulerianSolver us(4, EulerianSolver::UNDIRECTED);
    us.addEdge(0, 1); us.addEdge(1, 2); 
    us.addEdge(2, 3); us.addEdge(3, 0);
    us.addEdge(0, 2); // Makes it an Eulerian Path, not Circuit
    
    vector<int> u_tour = us.getTour(0);
    cout << "Undirected Tour: ";
    for (int v : u_tour) cout << v << " ";
    cout << endl;

    return 0;
}
