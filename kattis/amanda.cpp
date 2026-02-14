#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> adj(n+1);
    vector<int> state(n+1,-1);
    int ans=0;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(c==0&&(state[a]==1||state[b]==1)){cout<<"impossible";return 0;}
        if(c==2&&(state[a]==0||state[b]==0)){cout<<"impossible";return 0;}
        if(c==0){state[a]=state[b]=0;}
        if(c==2){state[a]=state[b]=1;}
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    queue<int> q;
    for(int i=1;i<=n;i++)if(state[i]!=-1)q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto [v,t]:adj[u]){
            if(t==1){
                if(state[v]!=-1&&state[v]!=1-state[u]){
                    cout<<"impossible";
                    return 0;
                }
                if(state[v]==-1){
                    state[v]=1-state[u];
                    q.push(v);
                }
            }
        }
    }
    for(int i=1;i<=n;i++)if(state[i]==1)ans++;
    for(int i=1;i<=n;i++){
        if(state[i]==-1){
            vector<int> component;
            queue<int> cq;
            state[i]=0;
            cq.push(i);
            component.push_back(i);
            int count=0,head=0;
            bool possible=true;
            while(head<component.size()){
                int u=component[head++];
                if(state[u]==1)count++;
                for(auto [v,t]:adj[u]){
                    if(state[v]==-1){
                        state[v]=1-state[u];
                        component.push_back(v);
                    }else if(state[v]!=1-state[u])possible=false;
                }
            }
            if(!possible){cout<<"impossible";return 0;}
            ans+=min(count,(int)component.size()-count);
        }
    }
    cout<<ans;
    return 0;    
}
