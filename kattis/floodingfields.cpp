#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;                             // large enough

class max_flow {
private:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;

  bool BFS(int s, int t) {                       // find augmenting path
    d.assign(V, -1); d[s] = 0;
    queue<int> q({s});
    p.assign(V, {-1, -1});                       // record BFS sp tree
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == t) break;                         // stop as sink t reached
      for (auto &idx : AL[u]) {                  // explore neighbors of u
        auto &[v, cap, flow] = EL[idx];          // stored in EL[idx]
        if ((cap-flow > 0) && (d[v] == -1))      // positive residual edge
          d[v] = d[u]+1, q.push(v), p[v] = {u, idx}; // 3 lines in one!
      }
    }
    return d[t] != -1;                           // has an augmenting path
  }

  ll send_one_flow(int s, int t, ll f = INF) {   // send one flow from s->t
    if (s == t) return f;                        // bottleneck edge f found
    auto &[u, idx] = p[t];
    auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
    ll pushed = send_one_flow(s, u, min(f, cap-flow));
    flow += pushed;
    auto &rflow = get<2>(EL[idx^1]);             // back edge
    rflow -= pushed;                             // back flow
    return pushed;
  }

  ll DFS(int u, int t, ll f = INF) {             // traverse from s->t
    if ((u == t) || (f == 0)) return f;
    for (int &i = last[u]; i < (int)AL[u].size(); ++i) { // from last edge
      auto &[v, cap, flow] = EL[AL[u][i]];
      if (d[v] != d[u]+1) continue;              // not part of layer graph
      if (ll pushed = DFS(v, t, min(f, cap-flow))) {
        flow += pushed;
        auto &rflow = get<2>(EL[AL[u][i]^1]);     // back edge
        rflow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

public:
  max_flow(int initialV) : V(initialV) {
    EL.clear();
    AL.assign(V, vi());
  }

  // if you are adding a bidirectional edge u<->v with weight w into your
  // flow graph, set directed = false (default value is directed = true)
  void add_edge(int u, int v, ll w, bool directed = true) {
    if (u == v) return;                          // safeguard: no self loop
    EL.emplace_back(v, w, 0);                    // u->v, cap w, flow 0
    AL[u].push_back(EL.size()-1);                // remember this index
    EL.emplace_back(u, directed ? 0 : w, 0);     // back edge
    AL[v].push_back(EL.size()-1);                // remember this index
  }

  ll edmonds_karp(int s, int t) {
    ll mf = 0;                                   // mf stands for max_flow
    while (BFS(s, t)) {                          // an O(V*E^2) algorithm
      ll f = send_one_flow(s, t);                // find and send 1 flow f
      if (f == 0) break;                         // if f == 0, stop
      mf += f;                                   // if f > 0, add to mf
    }
    return mf;
  }

  ll dinic(int s, int t) {
    ll mf = 0;                                   // mf stands for max_flow
    while (BFS(s, t)) {                          // an O(V^2*E) algorithm
      last.assign(V, 0);                         // important speedup
      while (ll f = DFS(s, t))                   // exhaust blocking flow
        mf += f;
    }
    return mf;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n,k,h;
  cin>>n>>k>>h;
  max_flow mf(2*(n*n*(h+1))+2);
  int source=0,sink=2*(n*n*(h+1))+1;
  vector<vector<int>> grid(n,vector<int>(n,0));
  for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
          cin>>grid[i][j];
      }
  }
  for(int i=0;i<k;i++){
      int r,c;
      cin>>r>>c;
      int in=2*(r*n+c)+1,out=2*(r*n+c)+2;
      mf.add_edge(0,in,1);
      mf.add_edge(in,out,1);
  }
  vector<int> flood(h+1,-1);
  int dr[]={0,0,-1,1,0},dc[]={-1,1,0,0,0};
  for(int i=1;i<=h;i++)cin>>flood[i];
  for(int r=0;r<n;r++){
      for(int c=0;c<n;c++){
          for(int i=0;i<=h;i++){
              int in=2*(i*n*n+r*n+c)+1,out=2*(i*n*n+r*n+c)+2;
              if(i>0&&grid[r][c]>flood[i])mf.add_edge(in,out,1);
              if(i==h){
                  if(grid[r][c]>flood[i])mf.add_edge(out,2*(n*n*(h+1))+1,1);
              }else{
                  for(int j=0;j<5;j++){
                      int nr=r+dr[j],nc=c+dc[j];
                      if(0<=nr&&nr<n&&0<=nc&&nc<n){
                          int nin=2*((i+1)*n*n+nr*n+nc)+1,nout=2*((i+1)*n*n+nr*n+nc)+2;
                          if(grid[r][c]>flood[i]&&grid[nr][nc]>flood[i+1])mf.add_edge(out,nin,1);
                      }
                  }
              }
          }
      }
  }
  cout<<mf.dinic(source,sink);
  return 0;
}
