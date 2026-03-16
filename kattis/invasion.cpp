#include <bits/stdc++.h>
using namespace std;

//just start a BFS from every new base Bi
//need to cleverly prune the BFS, else will TLE or MLE

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N,M,A,K;
    cin>>N>>M>>A>>K;
    while(N){
        vector<int> visited(N,0);
        vector<vector<pair<int,int>>> adj(N);
        for(int i=0;i<M;i++){
            int t1,t2,d;
            cin>>t1>>t2>>d;
            adj[t1-1].push_back({t2-1,d});
            adj[t2-1].push_back({t1-1,d});
        }
        int safe=N;
        vector<int> dist(N,1e9);
        for(int i=0;i<A;i++){
            int B;
            cin>>B;
            B--;
            queue<pair<int,int>> q;
            q.push({B,0});
            dist[B]=0;
            while(!q.empty()){
                auto [u,d]=q.front();
                q.pop();
                if(!visited[u]){
                    safe--;
                    visited[u]=1;
                }
                for(auto [v,dd]:adj[u]){
                    if(d+dd<dist[v]&&d+dd<K){
                        q.push({v,d+dd});
                        dist[v]=d+dd;
                    }
                }
            }
            cout<<safe<<"\n";
        }
        cout<<"\n";
        cin>>N>>M>>A>>K;
    }
    return 0;
}
