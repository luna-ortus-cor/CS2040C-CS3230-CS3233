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
  
  ll get_size() { return EL.size(); }
  
  ll get_flow(int idx) { return get<2>(EL[idx]); }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N,M,a,b;
  while(cin>>N>>M){
      vector<int> points(N);
      for(int i=0;i<N;i++)cin>>points[i];
      vector<pair<int,int>> matches;
      vector<pair<int,int>> all_matches;
      for(int i=0;i<M;i++){
          cin>>a>>b;
          all_matches.push_back({a,b});
          if(a!=N&&b!=N)matches.push_back({a,b});
      }
      int maxP=points[N-1]+2*(M-matches.size());
      if(*max(points.begin(),points.end()-1)>=maxP){cout<<"NO\n";continue;}
      max_flow mf(2+N-1+matches.size());
      vector<int> edges;
      for(int i=1;i<=matches.size();i++){
          mf.add_edge(0,i,2);
          edges.push_back(mf.get_size());
          mf.add_edge(i,matches.size()+matches[i-1].first,2);
          mf.add_edge(i,matches.size()+matches[i-1].second,2);
          
      }
      for(int i=1;i<N;i++){
          mf.add_edge(matches.size()+i,matches.size()+N,maxP-1-points[i-1]);
      }
      int val=mf.dinic(0,matches.size()+N);
      if(val==2*matches.size()){
          int idx=0;
          for(auto [a,b]:all_matches){
              if(a==N)cout<<"0 ";
              else if(b==N)cout<<"2 ";
              else{
                  auto c=mf.get_flow(edges[idx]);
                  if(c==2){
                      cout<<"0 ";
                  }else if(c==0){
                      cout<<"2 ";
                  }else{
                      cout<<"1 ";
                  }
                  idx++;
              }
              
          }
          cout<<"\n";
      }else cout<<"NO\n";
  }
  return 0;
}
