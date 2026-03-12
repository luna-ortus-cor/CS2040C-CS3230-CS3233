#include <bits/stdc++.h>
using namespace std;

struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;

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

    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; i++) {
            if (matchL[i] != -1) {
                pairs.push_back({i, matchL[i]});
            }
        }
        return pairs;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int p,v;
    cin>>p>>v;
    HopcroftKarp hk(v,p);
    unordered_map<int,vector<int>> ps;
    for(int i=0;i<p;i++){
        int a,b;
        cin>>a>>b;
        ps[a].push_back(i);
        ps[b].push_back(i);
    }
    for(int i=0;i<v;i++){
        int c;
        cin>>c;
        for(auto v:ps[c]){
            hk.add_edge(i,v);
        }
    }
    hk.max_matching();
    vector<int> ans;
    for(int i=0;i<v;i++){
        if(hk.matchL[i]!=-1){
            ans.push_back(hk.matchL[i]);
        }else{
            cout<<"impossible";
            return 0;
        }
    }
    for(auto i:ans)cout<<i+1<<"\n";
    return 0;
}
