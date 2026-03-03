#include <bits/stdc++.h>
using namespace std;

//realise each soldier has max 3 enemies implies k=1 or 2
//to see this, suppose we randomly intialise soldiers to 1 of 2 groups
//if soldier has 0 or 1 enemies in group, no issue
//else, soldier has 2 or 3 enemies in group. then soldier has 0 or 1 enemies in other group
//so just switch groups
//to handle case of 1 group only, first initialise all to 1 group
//if no conflict then 1 group, else 2 group
//if 2 group put all conflicting in queue, pop each one and switch groups
//update conflicts in new and old group
//finally just output as desired

const int MAXN=100005;
vector<int> adj[MAXN];
vector<int> group(MAXN,0);
int internal_conflicts[MAXN];
bool in_queue[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        internal_conflicts[i]=adj[i].size();
        if(internal_conflicts[i]>1){
            q.push(i);
            in_queue[i]=true;
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        in_queue[u]=false;
        if(internal_conflicts[u]>1){
            group[u]=1-group[u];
            int new_conflicts=0;
            for(int v:adj[u]){
                if(group[v]==group[u]){
                    new_conflicts++;
                    internal_conflicts[v]++;
                }else{
                    internal_conflicts[v]--;
                }
                if(internal_conflicts[v]>1&&!in_queue[v]){
                    q.push(v);
                    in_queue[v]=true;
                }
            }
            internal_conflicts[u]=new_conflicts;            
        }
    }
    int num_group=(accumulate(group.begin(),group.end(),0)==0?1:2);
    if(num_group==1){
        cout<<num_group<<"\n";
        for(int i=1;i<=n;i++)cout<<i<<" ";
    }else{
        cout<<num_group<<"\n";
        for(int i=1;i<=n;i++){
            if(group[i]==0)cout<<i<<" ";
        }
        cout<<"\n";
        for(int i=1;i<=n;i++){
            if(group[i]==1)cout<<i<<" ";
        }
    }
    return 0;
}
