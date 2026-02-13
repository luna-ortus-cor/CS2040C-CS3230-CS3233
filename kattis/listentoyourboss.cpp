#include <bits/stdc++.h>
using namespace std;

//Use LCA with RMQ using sparse table, dfs to create euler and first array
//need to convert graph into numbered order by bfs using unordered_map<int,int>
//need to maintain bidirectional mapping, 
//since RMQ will return index of numbered graph, need to find employee number
//but euler dfs will go through employee number, need to store index in euler
//refer to:
//https://cp-algorithms.com/graph/lca.html
//https://cp-algorithms.com/data_structures/sparse-table.html#range-minimum-queries-rmq
//https://en.wikipedia.org/wiki/Lowest_common_ancestor
//https://www.geeksforgeeks.org/sparse-table/
//note that if graph is in numbered order we can RMQ on euler, else RMQ on height
//here need to convert to numbered due to nature of query

//void dfs(int curr, vector<vector<int>> &AL, vector<int> &visited, vector<int> &euler, vector<int> &first, vector<int>& height, int h, unordered_map<int,int> forwardmapping){
void dfs(int curr, vector<vector<int>> &AL, vector<int> &visited, vector<int> &euler, vector<int> &first, unordered_map<int,int> &forwardmapping){
    first[forwardmapping[curr]]=euler.size();
    euler.push_back(forwardmapping[curr]);
    //height[forwardmapping[curr]]=h;
    visited[curr]=1;
    for(int i:AL[curr]){
        if(!visited[i]){
            //dfs(i, AL, visited, euler, first,height,h+1,forwardmapping);
            dfs(i, AL, visited, euler, first,forwardmapping);
            euler.push_back(forwardmapping[curr]);
            //height.push_back(forwardmapping[curr]);
        }
    }
}

void bfs(unordered_map<int,int> &forwardmapping, unordered_map<int,int> &backwardmapping, vector<vector<int>> &AL, vector<int> &visited){
    int idx=1;
    queue<int> q;
    q.push(1);
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        if(visited[curr]){
            continue;
        }
        visited[curr]=1;
        forwardmapping[curr]=idx;
        backwardmapping[idx]=curr;
        idx++;
        for(int i:AL[curr]){
            if(!visited[i]){
                q.push(i);
            }
        }
    }
    
}

int main(){
    int N,M;
    cin>>N>>M;
    const int K = 18;
    //const int MAXN = N+1;
    vector<vector<int>> AL(N+1,vector<int>());
    for(int i=2;i<N+1;i++){
        int j;
        cin>>j;
        AL[j].push_back(i);
    }
    vector<int> visitedbfs(N+1,0);
    unordered_map<int,int> forwardmapping;
    unordered_map<int,int> backwardmapping;
    bfs(forwardmapping, backwardmapping, AL, visitedbfs);
    vector<int> euler;
    vector<int> first(N+1,-1);
    vector<int> visiteddfs(N+1,0);
    //vector<int> height(N+1,-1);
    //dfs(1,AL,visiteddfs,euler,first,height,0, forwardmapping);
    dfs(1,AL,visiteddfs,euler,first, forwardmapping);
    vector<vector<int>> sparse(K,vector<int>(euler.size()+2));
    for(int i=0;i<euler.size();i++){
        sparse[0][i]=euler[i];
    }
    for(int i=1;i<K;i++){
        for(int j=0;j+(1<<i)<euler.size()+2;j++){
            sparse[i][j]=min(sparse[i-1][j],sparse[i-1][j+(1<<(i-1))]);
        }
    }
    
    for(int i=0;i<M;i++){
        ios_base::sync_with_stdio(false);
        cin.tie(0);
        int a,b;
        cin>>a>>b;
        int R = max(first[forwardmapping[a]],first[forwardmapping[b]]);
        int L = min(first[forwardmapping[a]],first[forwardmapping[b]]);
        int j = (int) log2(R - L + 1);
        int minimum = min(sparse[j][L], sparse[j][R - (1 << j) + 1]);
        //cout<<backwardmapping[minimum]<<endl;
        if(backwardmapping[minimum]==b){
            cout<<"No"<<endl;
        }else{
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}

//memory limit exceeded
/*
void dfs(int curr, vector<vector<int>> &AL, vector<unordered_map<int,int>> &vmap, unordered_map<int,int> &store){
    store.emplace(make_pair(curr,1));
    for(int i:AL[curr]){
        vmap[i]=store;
        dfs(i,AL,vmap,store);
    }
    store.erase(curr);
    return;
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<unordered_map<int,int>> vmap(N+1);
    vector<vector<int>> AL(N+1,vector<int>());
    unordered_map<int,int> store;
    for(int i=2;i<N+1;i++){
        int j;
        cin>>j;
        AL[j].push_back(i);
    }
    store.emplace(make_pair(1,1));
    vmap[1]=store;
    dfs(1,AL,vmap,store);
    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        if(vmap[a].count(b)!=0){
            cout<<"No"<<endl;
        }else{
            cout<<"Yes"<<endl;
        }
    }
}
*/
