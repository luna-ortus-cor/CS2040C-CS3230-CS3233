#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//first observe that for an edge to be traversed and backtracked
//we require k>=2; then notice that if k>=2, we can traverse any
//edge and return to the original node without worry
//thus since the structure of the N nodes and N-1 edges forms a tree
//it is guaranteed that there is at least one "initial" node from which
//we can start from, traverse its first subtree, return, traverse its
//second subtree, return, traverse its third subtree, etc etc.
//this applies to the subtrees themselves as well, so if k>=2 we are
//able to collect all resources along all edges
//for k=1, we must find the "diameter" of the tree, not in terms of edges
//in the diameter but in the sum of the weights of the edges in the diameter
//this can be done by the usual diameter-finding algorithm
//DFS from any node u, let v be another node with maximal "distance"=sum of edge weights
//from u, then DFS from v, let z be another node with maximal "distance" from v
//then v->z is a diameter, and the sum of edge weights along it is the answer
//also note that we are guaranteed with N-1 edges for N nodes that
//there are no cycles in the graph

void DFS(vector<unordered_map<int,int>> &adj, vector<int> &visited, int prev, int curr, ll currsum, ll &currmax, int &maxidx){
    visited[curr]=1;
    if(prev!=curr){
        currsum+=adj[prev][curr];
        if(currsum>currmax){
            currmax=currsum;
            maxidx=curr;
        }
    }
    for(auto &[k,v]:adj[curr]){
        if(!visited[k]){
            DFS(adj,visited,curr,k,currsum,currmax,maxidx);
        }
    }
}

int main(){
    int N,k,u,v,c;
    cin>>N>>k;
    vector<unordered_map<int,int>> adj(N+1);
    vector<int> visited(N+1,0);
    N--;
    ll total=0;
    while(N--){
        cin>>u>>v>>c;
        total+=c;
        adj[u][v]=c;
        adj[v][u]=c;
    }
    if(k>1){
        cout<<total<<"\n";
    }else{
        ll currmax=0;
        int maxidx=1;
        DFS(adj,visited,1,1,0,currmax,maxidx);
        fill(visited.begin(),visited.end(),0);
        currmax=0;
        int newmaxidx=maxidx;
        DFS(adj,visited,maxidx,maxidx,0,currmax,newmaxidx);
        cout<<currmax<<"\n";
    }
    return 0;
}
