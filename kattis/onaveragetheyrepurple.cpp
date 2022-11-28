#include <bits/stdc++.h>

using namespace std;

// BFS

int main(){
    int N,M;
    cin>>N>>M;
    list<pair<int,int>> toVisit;
    toVisit.push_back(make_pair(1,0));
    int visited[N+2]={0};
    unordered_map<int,vector<int>> adj;
    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        if(adj.find(a)!=adj.end()){
            adj[a].push_back(b);
        }else{
            vector<int> temp={b};
            adj.emplace(a,temp);
        }
        if(adj.find(b)!=adj.end()){
            adj[b].push_back(a);
        }else{
            vector<int> temp={a};
            adj.emplace(b,temp);
        }
    }
    while(true){
        int curr=toVisit.front().first;
        int move=toVisit.front().second;
        if(curr==N){
            cout<<move-1<<endl;
            break;
        }else if(visited[curr]==1){
            toVisit.pop_front();
            continue;
        }else{
            visited[curr]=1;
            for(int j:adj[curr]){
                if(visited[j]==0){
                    toVisit.push_back(make_pair(j,move+1));
                }
            }
            toVisit.pop_front();
        }
    }
    return 0;
}
