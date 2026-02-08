#include <bits/stdc++.h>
using namespace std;

const double EPS=1e-9;
const double INF=1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    vector<double> M(N+1);
    vector<vector<pair<int,double>>> adj(N+1);
    vector<int> indeg(N+1,0);

    for(int i=1;i<=N;i++) {
        cin>>M[i];
        int k;
        cin>>k;
        for (int j=0;j<k;j++) {
            int to;
            double w;
            cin>>to>>w;
            adj[i].push_back({to,w/100.0});
            indeg[to]++;
        }
    }

    vector<double> I(N+1,0.0);
    vector<double> U(N+1,0.0);

    queue<int> q;
    for(int i=1;i<=N;i++) {
        if(indeg[i]==0){
            I[i]=INF;
            U[i]=M[i];
            q.push(i);
        }
    }

    while(!q.empty()){
        int p=q.front();
        q.pop();
        for (auto &[to,frac]:adj[p]) {
            I[to]+=U[p]*frac;
            indeg[to]--;
            if(indeg[to]==0){
                U[to]=min(I[to],M[to]);
                q.push(to);
            }
        }
    }

    for (int i=1;i<=N;i++) {
        if(fabs(U[i]-M[i])<=EPS){
            cout<<i<<" ";
        }
    }
    return 0;
}
