#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
vector<pair<int,int>> e[N];
int dis[N];
struct node{
  int x,d;
  bool operator < (const node & b) const {
    return d > b.d;
  }
};
int n,vis[N],ans[N];
void dij(int D){
  memset(dis,0x3f,sizeof(dis));
  int INF=dis[0];
  dis[D]=0;
  priority_queue<node> q;
  q.push({D,0});
  while(!q.empty()){
    auto [u, d] = q.top(); q.pop();
    if(vis[u]) continue;
    vis[u]=1;
    for(auto [v, w]:e[u])
      if(dis[v]>dis[u]+w){
        dis[v]=dis[u]+w;
        q.push({v,dis[v]});
      }
  }
 // for(int i=1;i<=n;++i) cerr<<dis[i]<<" ";cerr<<"???\n";
  for(int i=1;i<=n;++i){
    ans[i]=-1;
  }
  for(int v=1;v<=n;++v){
    if(dis[v]==INF) continue;
    for(auto [u,w]:e[v])
      if(dis[u]!=INF && dis[u]==dis[v]+w){
        if(ans[u]==-1) ans[u]=v;
        else if(ans[u]>v) ans[u]=v;
      }
  }
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m,D;
  cin>>n>>m>>D;
  for(int i=1;i<=m;++i){
    int u,v,w;
    cin>>u>>v>>w;
    e[v].push_back({u,w});
  }
  dij(D);
  int q;
  cin>>q;
  while(q--){
    int x;
    cin>>x;
    if(x==D) cout<<x<<"\n";
    else cout<<ans[x]<<"\n";
  }
}
