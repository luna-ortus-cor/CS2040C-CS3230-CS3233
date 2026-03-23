#include <bits/stdc++.h>
using namespace std;

struct Eulerian {
    int n;
    bool directed;
    vector<vector<pair<int, int>>> adj; // {to, edge_id}
    vector<int> in_deg, out_deg, deg;
    int m = 0;

    Eulerian(int _n, bool _directed) : n(_n), directed(_directed), adj(_n), 
                                       in_deg(_n, 0), out_deg(_n, 0), deg(_n, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back({v, m});
        if (directed) {
            out_deg[u]++; in_deg[v]++;
        } else {
            adj[v].push_back({u, m});
            deg[u]++; deg[v]++;
        }
        m++;
    }

    vector<int> solve() {
        int start_node = -1, odd_count = 0, out_greater = 0, in_greater = 0;
        vector<int> path;

        if (directed) {
            int s = -1, t = -1;
            for (int i = 0; i < n; i++) {
                if (out_deg[i] - in_deg[i] == 1) { out_greater++; s = i; }
                else if (in_deg[i] - out_deg[i] == 1) { in_greater++; t = i; }
                else if (out_deg[i] != in_deg[i]) return {}; // Impossible
            }
            if (!((out_greater == 0 && in_greater == 0) || (out_greater == 1 && in_greater == 1))) return {};
            start_node = (s != -1) ? s : 0;
            // Find first node with outgoing edges if 0 is isolated
            if (out_deg[start_node] == 0) {
                for(int i=0; i<n; i++) if(out_deg[i] > 0) { start_node = i; break; }
            }
        } else {
            vector<int> odds;
            for (int i = 0; i < n; i++) if (deg[i] % 2 != 0) odds.push_back(i);
            if (odds.size() != 0 && odds.size() != 2) return {};
            start_node = odds.empty() ? 0 : odds[0];
            if (deg[start_node] == 0) {
                for(int i=0; i<n; i++) if(deg[i] > 0) { start_node = i; break; }
            }
        }

        // Hierholzer's Algorithm
        vector<bool> used_edge(m, false);
        vector<int> current_edge_idx(n, 0);
        stack<int> st;
        st.push(start_node);

        while (!st.empty()) {
            int u = st.top();
            bool found = false;
            while (current_edge_idx[u] < adj[u].size()) {
                auto [v, id] = adj[u][current_edge_idx[u]++];
                if (!used_edge[id]) {
                    used_edge[id] = true;
                    st.push(v);
                    found = true;
                    break;
                }
            }
            if (!found) {
                path.push_back(u);
                st.pop();
            }
        }

        reverse(path.begin(), path.end());
        if (path.size() != m + 1) return {}; // Disconnected graph with edges
        return path;
    }
};
