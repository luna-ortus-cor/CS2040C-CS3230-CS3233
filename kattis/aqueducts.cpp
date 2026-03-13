#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Edge {
    ll to, rev, cap, cost;
};

struct MCMF {
    int n;
    vector<vector<Edge>> g;
    vector<ll> dist;
    vector<int> pv, pe;

    MCMF(int n):n(n),g(n),dist(n),pv(n),pe(n){}

    void add_edge(int u,int v,ll cap,ll cost){
        g[u].push_back({v,(int)g[v].size(),cap,cost});
        g[v].push_back({u,(int)g[u].size()-1,0LL,-cost});
    }

    pair<ll,ll> solve(int s,int t){
        ll flow=0;
        ll cost=0;

        while(true){
            fill(dist.begin(),dist.end(),LLONG_MAX);
            dist[s]=0;

            queue<int>q;
            vector<bool>inq(n);
            q.push(s); inq[s]=1;

            while(!q.empty()){
                int v=q.front(); q.pop();
                inq[v]=0;
                for(int i=0;i<g[v].size();i++){
                    auto &e=g[v][i];
                    if(e.cap && dist[e.to] > dist[v]+e.cost){
                        dist[e.to]=dist[v]+e.cost;
                        pv[e.to]=v;
                        pe[e.to]=i;
                        if(!inq[e.to]){
                            inq[e.to]=1;
                            q.push(e.to);
                        }
                    }
                }
            }

            if(dist[t]==LLONG_MAX) break;

            ll add=1e18;
            for(int v=t;v!=s;v=pv[v])
                add=min(add,g[pv[v]][pe[v]].cap);

            flow+=add;
            cost+=add*dist[t];

            for(int v=t;v!=s;v=pv[v]){
                auto &e=g[pv[v]][pe[v]];
                e.cap-=add;
                g[v][e.rev].cap+=add;
            }
        }

        return {flow,cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,s,t,q;
    cin>>n>>s>>t>>q;
    vector<vector<ll>> hills(n+1);
    for(int i=1;i<=n;i++){
        ll x,y,h;
        cin>>x>>y>>h;
        hills[i]={x,y,h};
    }
    vector<int> springs(s);
    vector<int> towns(t);
    for(int i=0;i<s;i++)cin>>springs[i];
    for(int i=0;i<t;i++)cin>>towns[i];
    vector<vector<pair<int,double>>> adj(n+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            auto a=hills[i];
            auto b=hills[j];
            ll x1=a[0],y1=a[1],h1=a[2];
            ll x2=b[0],y2=b[1],h2=b[2];
            if(h1<=h2)continue;
            ll dx=x1-x2;
            ll dy=y1-y2;
            ll dh=h1-h2;
            double d=sqrt(dx*dx+dy*dy+dh*dh);
            if(d<=q+1e-9)adj[i].push_back({j,d});
        }
    }
    vector<vector<double>> dist_spring(s,vector<double>(t,1e18));
    for(int i=0;i<s;i++){
        int start=springs[i];
        vector<double> dist(n+1,1e18);
        priority_queue<pair<double,int>,vector<pair<double,int>>,greater<>> pq;
        dist[start]=0;
        pq.push({0,start});
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>dist[u])continue;
            for(auto [v,w]:adj[u]){
                if(dist[v]>d+w){
                    dist[v]=d+w;
                    pq.push({dist[v],v});
                }
            }
        }
        for(int j=0;j<t;j++){
            dist_spring[i][j]=dist[towns[j]];
        }
    }
    MCMF mcmf(s+t+2);
    int source=0,sink=s+t+1;
    for(int i=0;i<s;i++){
        for(int j=0;j<t;j++){
            if(dist_spring[i][j]<1e18)
                mcmf.add_edge(i+1,j+s+1,1,llround(dist_spring[i][j]*1e7));
        }
    }
    for(int i=1;i<=s;i++)mcmf.add_edge(source,i,1LL,0LL);
    for(int j=s+1;j<=s+t;j++)mcmf.add_edge(j,sink,1LL,0LL);
    pair<ll,ll> ans=mcmf.solve(source,sink);
    if(ans.first!=t)cout<<"IMPOSSIBLE";
    else cout<<fixed<<setprecision(10)<<((double)ans.second/1e7);
    return 0;
}
