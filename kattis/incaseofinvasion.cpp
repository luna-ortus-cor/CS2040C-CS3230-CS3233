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
    vector<int> d, last;

    bool BFS(int s, int t) {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int idx : AL[u]) {
                auto& edge = EL[idx];
                if (edge.cap - edge.flow > 0 && d[edge.to] == -1) {
                    d[edge.to] = d[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return d[t] != -1;
    }

    ll DFS(int u, int t, ll pushed) {
        if (pushed == 0 || u == t) return pushed;
        for (int& cid = last[u]; cid < (int)AL[u].size(); ++cid) {
            int idx = AL[u][cid];
            auto& edge = EL[idx];
            if (d[u] + 1 != d[edge.to] || edge.cap - edge.flow == 0) continue;
            ll tr = DFS(edge.to, t, min(pushed, edge.cap - edge.flow));
            if (tr == 0) continue;
            EL[idx].flow += tr;
            EL[idx ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

public:
    const ll INF = 1e18;

    max_flow(int initialV) : V(initialV) {
        AL.assign(V, vector<int>());
        d.assign(V, 0);
        last.assign(V, 0);
    }

    // Returns the ID of the forward edge
    ll add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return -1;
        ll id = (ll)EL.size();
        AL[u].push_back(id);
        EL.push_back({u, v, w, 0});
        AL[v].push_back(id + 1);
        EL.push_back({v, u, directed ? 0 : w, 0});
        return id;
    }

    ll dinic(int s, int t) {
        ll mf = 0;
        while (BFS(s, t)) {
            last.assign(V, 0);
            while (ll f = DFS(s, t, INF)) {
                mf += f;
            }
        }
        return mf;
    }

    // --- CP Utilities & Network Modification ---

    void reset_flow() {
        for (auto& e : EL) e.flow = 0;
    }

    // Find the S-partition of the minimum cut (reachable from s in residual graph)
    vector<bool> min_cut(int s) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int idx : AL[u]) {
                if (EL[idx].cap - EL[idx].flow > 0 && !visited[EL[idx].to]) {
                    visited[EL[idx].to] = true;
                    q.push(EL[idx].to);
                }
            }
        }
        return visited;
    }

    // Returns all forward edges
    vector<Edge> get_edges() {
        vector<Edge> res;
        for (int i = 0; i < (int)EL.size(); i += 2) {
            res.push_back(EL[i]);
        }
        return res;
    }

    // Get flow along a specific edge by its ID
    ll get_flow(int edge_id) {
        if (edge_id < 0 || edge_id >= (int)EL.size()) return 0;
        return EL[edge_id].flow;
    }

    // Get total flow between u and v (handles parallel edges)
    ll get_total_flow(int u, int v) {
        ll total_flow = 0;
        for (int idx : AL[u]) {
            if (EL[idx].to == v && idx % 2 == 0) {
                total_flow += EL[idx].flow;
            }
        }
        return total_flow;
    }

    // Increase capacity of a specific edge
    void increase_capacity(int edge_id, ll delta) {
        if (edge_id < 0 || edge_id >= (int)EL.size()) return;
        EL[edge_id].cap += delta;
        // Call dinic(s, t) again after this to push new flow
    }

    // Safely remove an edge (asserts no flow is actively using it)
    void remove_edge_safe(int edge_id) {
        if (edge_id < 0 || edge_id >= (int)EL.size()) return;
        assert(EL[edge_id].flow == 0); 
        EL[edge_id].cap = 0;
        EL[edge_id ^ 1].cap = 0;
    }

    // Safely decrease capacity (asserts new capacity >= current flow)
    void decrease_capacity_safe(int edge_id, ll new_cap) {
        if (edge_id < 0 || edge_id >= (int)EL.size()) return;
        assert(new_cap >= EL[edge_id].flow); 
        EL[edge_id].cap = new_cap;
    }

    // Remove an edge (no assert, must reset flow and rerun dinic)
    void remove_edge(int edge_id) {
        if (edge_id < 0 || edge_id >= (int)EL.size()) return;
        EL[edge_id].cap = 0;
        EL[edge_id ^ 1].cap = 0;
    }

    // Similarly, decrease capacity (no assert, must reset flow and rerun dinic)
    void decrease_capacity(int edge_id, ll new_cap) {
        if (edge_id < 0 || edge_id >= (int)EL.size()) return;
        EL[edge_id].cap = new_cap;
    }
};

ll dist[11][100005];
bool check(ll T,ll n,ll s,ll total,const vector<ll> &loc, const vector<pair<ll,ll>> &shelters){
    map<ll, ll> mask_pop;
    for(ll i=0;i<n;i++){
        if (loc[i]==0)continue;
        ll mask=0;
        for(ll j=0;j<s;j++){
            if (dist[j][i]<=T)mask|=(1<<j);
        }
        if (mask>0)mask_pop[mask]+=loc[i];
    }

    int source=0;
    int sink=mask_pop.size()+s+1;
    max_flow mf(sink+1);

    int node_idx=1;
    for(auto const& [mask,pop]:mask_pop){
        mf.add_edge(source,node_idx,pop);
        for (int j=0;j<s;j++){
            if((mask>>j)&1){
                mf.add_edge(node_idx,mask_pop.size()+j+1,1e18);
            }
        }
        node_idx++;
    }
    for(int j=0;j<s;j++){
        mf.add_edge(mask_pop.size()+j+1,sink,shelters[j].second);
    }
    return mf.dinic(source,sink)==total;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n,m,s;
    cin>>n>>m>>s;
    vector<ll> loc(n);
    ll total=0;
    for(ll i=0;i<n;i++){
        cin>>loc[i];
        total+=loc[i];
    }
    vector<vector<pair<ll,ll>>> adj(n);
    for(ll i=0;i<m;i++) {
        ll u,v,w;
        cin>>u>>v>>w;
        adj[u-1].push_back({v-1,w});
        adj[v-1].push_back({u-1,w});
    }
    vector<pair<ll,ll>> shelters(s);
    for(int i=0;i<s;i++){
        ll si,ci;
        cin>>si>>ci;
        shelters[i]={si-1,ci};
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
        for(ll j=0;j<n;j++)dist[i][j]=1e18;
        dist[i][shelters[i].first]=0;
        pq.push({0,shelters[i].first});
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if (d>dist[i][u])continue;
            for(auto& v:adj[u]){
                if (dist[i][u]+v.second<dist[i][v.first]){
                    dist[i][v.first]=dist[i][u]+v.second;
                    pq.push({dist[i][v.first],v.first});
                }
            }
        }
    }
    ll lo=0,hi=1e18,ans=hi;
    while(lo<=hi){
        ll mid=lo+(hi-lo)/2;
        if (check(mid,n,s,total,loc,shelters)){
            ans=mid;
            hi=mid-1;
        }else{
            lo=mid+1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
