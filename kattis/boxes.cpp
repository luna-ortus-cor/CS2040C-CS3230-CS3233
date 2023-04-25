#include <bits/stdc++.h>

using namespace std;

//treat as directed graph, then flood fill for each box in each query, 
//making sure not to revisit, using recursive dfs
//graph is parent->list of immediate children

int dfs(int v, vector<vector<int>> &graph, vector<int> &visited){
    int ans = 0;
    visited[v]=1;
    for(int u:graph[v]){
        if(!visited[u]){
            ans+=(1+dfs(u,graph,visited));
        }
    }
    return ans;
}

int main(){
    int N;
    cin>>N;
    vector<vector<int>> graph(N+1,vector<int>());
    for(int i=1;i<N+1;i++){
        int parent;
        cin>>parent;
        if(parent){
            graph[parent].push_back(i);
        }
    }
    int Q;
    cin>>Q;
    for(int i=0;i<Q;i++){
        int M;
        cin>>M;
        int ans=0;
        vector<int> boxes;
        for(int j=0;j<M;j++){
            int b;
            cin>>b;
            boxes.push_back(b);
        }
        vector<int> visited(N+1,0);
        for(int b:boxes){
            if(!visited[b]){
                ans+=(1+dfs(b,graph,visited));
            }
        }
        cout<<ans<<endl;
    }
}
