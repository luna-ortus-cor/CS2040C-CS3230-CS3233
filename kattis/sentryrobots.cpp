#include <bits/stdc++.h>
using namespace std;

//by konig thm, max matching=min vertex cover in bipartite graph
//let the nodes be segments and the edges the points to be covered
//each point is covered by exactly 1 vertical and 1 horizontal segment
//thus we this is bipartite (one side horizontal node, one side vertical node)
//for each point's (unique) horizontal,vertical pair
//we need a matching in each to cover the point

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
    int C;
    cin>>C;
    while(C--){
        int Y,X;
        cin>>Y>>X;
        vector<vector<int>> grid(Y+1,vector<int>(X+1,0));
        int P; 
        cin>>P;
        vector<pair<int,int>> points(P);
        for(int i=0;i<P;i++){
            int py,px;
            cin>>py>>px;
            points[i]={py,px};
            grid[py][px]=1;
        }
        int W;
        cin>>W;
        for(int i=0;i<W;i++){
            int wy,wx;
            cin>>wy>>wx;
            grid[wy][wx]=2;
        }
        vector<vector<int>> hor_map(Y+1,vector<int>(X+1,-1));
        int h_id=0;
        for(int i=1;i<=Y;i++){
            bool new_seg=true;
            for(int j=1;j<=X;j++){
                if(grid[i][j]==2)new_seg=true;
                else{
                    if(new_seg)h_id++;
                    hor_map[i][j]=h_id-1;
                    new_seg=false;
                }
            }
        }
        vector<vector<int>> ver_map(Y+1,vector<int>(X+1,-1));
        int v_id=0;
        for(int j=1;j<=X;j++){
            bool new_seg=true;
            for(int i=1;i<=Y;i++){
                if(grid[i][j]==2)new_seg=true;
                else{
                    if(new_seg)v_id++;
                    ver_map[i][j]=v_id-1;
                    new_seg=false;
                }
            }
        }
        HopcroftKarp hk(h_id,v_id);
        for(auto p:points)hk.add_edge(hor_map[p.first][p.second],ver_map[p.first][p.second]);
        cout<<hk.max_matching()<<"\n";
    }
    return 0;
}
