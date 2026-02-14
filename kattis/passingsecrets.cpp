#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string name1,name2;
    while(cin>>name1>>name2){
        int n;
        cin>>n;
        cin.ignore();
        unordered_map<string,int> name2id;
        vector<string> id2name;
        auto get_id=[&](string name){
            if(name2id.find(name)==name2id.end()){
                name2id[name]=id2name.size();
                id2name.push_back(name);
            }
            return name2id[name];
        };
        vector<unordered_map<int,int>> adj;
        for(int i=0;i<n;i++){
            string line;
            getline(cin,line);
            stringstream ss(line);
            vector<int> group;
            string name;
            while(ss>>name)group.push_back(get_id(name));
            int weight=group.size()-2;
            if(adj.size()<id2name.size())adj.resize(id2name.size());
            for(int j=0;j<group.size();j++){
                for(int k=j+1;k<group.size();k++){
                    int u=group[j],v=group[k];
                    if(adj[u].find(v)==adj[u].end()||adj[u][v]>weight){
                        adj[u][v]=weight;
                        adj[v][u]=weight;
                    }
                }
            }
        }
        if(name2id.find(name1)==name2id.end()||name2id.find(name2)==name2id.end()){
            cout<<"impossible"<<"\n";
            continue;
        }
        int s=name2id[name1],t=name2id[name2];
        vector<int> dist(id2name.size(),INF);
        vector<int> parent(id2name.size(),-1);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        dist[s]=0;
        pq.push({0,s});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(d>dist[u])continue;
            if(u==t)break;
            for(auto [v,w]:adj[u]){
                if(v==t){
                    if(dist[u]+w<dist[v]){
                        dist[v]=dist[u]+w;
                        parent[v]=u;
                        pq.push({dist[v],v});
                    }
                }else{
                    if(dist[u]+w+1<dist[v]){
                        dist[v]=dist[u]+w+1;
                        parent[v]=u;
                        pq.push({dist[v],v});
                    }
                }
            }
        }
        if(dist[t]==INF)cout<<"impossible"<<"\n";
        else{
            vector<string> path;
            for(int curr=t;curr!=-1;curr=parent[curr]){
                path.push_back(id2name[curr]);
            }
            reverse(path.begin(),path.end());
            cout<<dist[t]<<" ";
            for(int i=0;i<path.size();i++){
                cout<<path[i]<<" ";
            }
            cout<<"\n";
        }
    }
    return 0;
}
