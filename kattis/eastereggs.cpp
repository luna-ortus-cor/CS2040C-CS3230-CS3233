#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

bool check(ll D,ll N,ll B,ll R,const vector<vector<ll>> &dist){
    HopcroftKarp hk(B,R);
    for(ll i=0;i<B;i++){
        for(ll j=0;j<R;j++){
            if(dist[i][j]<D+1e-9)hk.add_edge(i,j);
        }
    }
    return R+B-hk.max_matching()>=N;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N,B,R;
    cin>>N>>B>>R;
    vector<pair<ll,ll>> Bs(B),Rs(R);
    for(ll i=0;i<B;i++)cin>>Bs[i].first>>Bs[i].second;
    for(ll i=0;i<R;i++)cin>>Rs[i].first>>Rs[i].second;
    vector<vector<ll>> dist(B,vector<ll>(R,1e18));
    for(ll i=0;i<B;i++){
        for(ll j=0;j<R;j++){
            ll dx=Bs[i].first-Rs[j].first;
            ll dy=Bs[i].second-Rs[j].second;
            ll d=llround(sqrt(dx*dx+dy*dy)*1e7);
            dist[i][j]=d;
        }
    }
    ll lo=0,hi=1e12,ans=lo;
    while(lo<=hi){
        ll mid=(lo+hi)/2;
        if(check(mid,N,B,R,dist)){
            ans=mid;
            lo=mid+1;
        }else hi=mid-1;
    }
    cout<<fixed<<setprecision(10)<<(double)ans/1e7;
    return 0;
}
