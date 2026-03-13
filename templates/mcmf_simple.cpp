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
