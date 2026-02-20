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

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int F,S,C;
  cin>>F>>S>>C;
  cin.ignore();
  int total_nodes=1+F+2*S+C+1;
  max_flow mf(total_nodes);
  int source=0;
  int sink=1+F+2*S+C;
  for(int f=1;f<=F;f++)mf.add_edge(source,f,1);
  unordered_map<string,int> sug2id;
  int next_id=0;
  vector<vector<string>> friend_sugs(F+1);
  for(int f=1;f<=F;f++){
    string line;
    getline(cin,line);
    stringstream ss(line);
    string sug;
    while(ss>>sug){
      friend_sugs[f].push_back(sug);
      if(!sug2id.count(sug))sug2id[sug]=++next_id;
    }
  }
  vector<int> cat_limit(C+1);
  vector<vector<string>> cat_sugs(C+1);
  for(int c=1;c<=C;c++){
    int n;
    cin>>n;
    cat_limit[c]=n;
    string line;
    getline(cin,line);
    stringstream ss(line);
    string sug;
    while(ss>>sug){
      cat_sugs[c].push_back(sug);
      if(!sug2id.count(sug))sug2id[sug]=++next_id;
    }
  }
  for(int f=1;f<=F;f++){
    for(auto sug:friend_sugs[f]){
      int id=sug2id[sug];
      mf.add_edge(f,F+id,1);
    }
  }
  for(int id=1;id<=next_id;id++)mf.add_edge(F+id,F+S+id,1);
  for(int c=1;c<=C;c++){
    for(auto sug:cat_sugs[c]){
      auto it=sug2id.find(sug);
      if(it!=sug2id.end()){
        int id=it->second;
        mf.add_edge(F+S+id,F+2*S+c,1);
      }
    }
  }
  for(int c=1;c<=C;c++)mf.add_edge(F+2*S+c,sink,cat_limit[c]);
  cout<<mf.dinic(source,sink);
  return 0;
}
