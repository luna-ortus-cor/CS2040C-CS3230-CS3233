#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;
    vector<bool> visL, visR; // For MVC/MIS recovery

    HopcroftKarp(int n, int m) : n(n), m(m), adj(n), matchL(n, -1), matchR(m, -1), dist(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);
        for (int i = 0; i < n; i++) {
            if (matchL[i] == -1) {
                dist[i] = 0;
                q.push(i);
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (matchR[v] == -1) found = true;
                else if (dist[matchR[v]] == -1) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (matchR[v] == -1 || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                if (matchL[i] == -1 && dfs(i)) matching++;
        }
        return matching;
    }

    // --- New Methods for MVC and MIS ---

    void _dfs_alternating(int u) {
        visL[u] = true;
        for (int v : adj[u]) {
            // Traverse L -> R via unmatched edges
            // Then R -> L via matched edges
            if (v != matchL[u] && !visR[v]) {
                visR[v] = true;
                if (matchR[v] != -1 && !visL[matchR[v]]) {
                    _dfs_alternating(matchR[v]);
                }
            }
        }
    }

    void build_reachability() {
        visL.assign(n, false);
        visR.assign(m, false);
        for (int i = 0; i < n; i++) {
            if (matchL[i] == -1) {
                _dfs_alternating(i);
            }
        }
    }

    // Returns {Nodes in Left Set, Nodes in Right Set}
    pair<vector<int>, vector<int>> get_mvc() {
        build_reachability();
        vector<int> mvcL, mvcR;
        // MVC = (L \ Visited) union (R \cap Visited)
        for (int i = 0; i < n; i++) if (!visL[i]) mvcL.push_back(i);
        for (int i = 0; i < m; i++) if (visR[i]) mvcR.push_back(i);
        return {mvcL, mvcR};
    }

    // Returns {Nodes in Left Set, Nodes in Right Set}
    pair<vector<int>, vector<int>> get_mis() {
        build_reachability();
        vector<int> misL, misR;
        // MIS = (L \cap Visited) union (R \ Visited)
        for (int i = 0; i < n; i++) if (visL[i]) misL.push_back(i);
        for (int i = 0; i < m; i++) if (!visR[i]) misR.push_back(i);
        return {misL, misR};
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int B,G;
    cin>>B>>G;
    HopcroftKarp hk(B,G);
    unordered_map<string,int> um;
    vector<int> books;
    int idx=0;
    for(int i=0;i<B;i++){
        string s;
        cin>>s;
        int N;
        cin>>N;
        for(int j=0;j<N;j++){
            cin>>s;
            um[s]=idx;
            idx++;
            books.push_back(i);
        }
    }
    for(int i=0;i<G;i++){
        string s;
        cin>>s;
        int N;
        cin>>N;
        for(int j=0;j<N;j++){
            cin>>s;
            hk.add_edge(books[um[s]],i);
        }
    }
    hk.max_matching();
    auto [x,y]=hk.get_mvc();
    cout<<x.size()+y.size();
    return 0;
}
