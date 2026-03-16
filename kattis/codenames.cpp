#include <bits/stdc++.h>
using namespace std;

//this is bipartite matching
//since any two 1-swappable elements we can only pick 1
//i.e. we remove 1 from total elements for each match
//since no duplicate letters, all elements are anagrams
//then each word is a permutation
//swap 2 elements in a permutation results in change of parity
//of number of inversions (which we can precalculate)
//let left be even parity, right be odd parity
//1-swappable elements = exactly 2 idx with different char
//then just add edge according to the above logic
//can also solve using max flow
//but here we use hopcroft-karp

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

int get_parity(const string& s) {
    int inv=0;
    for(int i=0;i<s.size();i++){
        for(int j=i+1;j<s.size();j++){
            if(s[i]>s[j])inv++;
        }
    }
    return inv%2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    vector<string> s(N);
    for(int i=0;i<N;i++)cin>>s[i];
    vector<int> p(N);
    for(int i=0;i<N;i++)p[i]=get_parity(s[i]);
    HopcroftKarp hk(N,N);
    int len=s[0].size();
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            int count=0;
            for(int k=0;k<len;k++){
                if(s[i][k]!=s[j][k])count++;
            }
            if(count==2){
                if(p[i]%2==0)hk.add_edge(i,j);
                else hk.add_edge(j,i);
            }
        }
    }
    cout<<N-hk.max_matching();
    return 0;
}
