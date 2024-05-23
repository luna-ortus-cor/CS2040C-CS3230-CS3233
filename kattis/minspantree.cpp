#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
typedef pair<int,pi> pipi;

//kruskal requires use of disjoint set union structure, im lazy
//so use prim, start source at node 1

struct comp{
    bool operator()(pipi p1,pipi p2){
        return p1.first>p2.first;
    }
};

int main(){
    int n,m,u,v,w;
    while(cin>>n>>m){
        if(!n&&!m)break;
        vector<pi>ans;int cost=0;
        vector<int>visited(n,0);
        priority_queue<pipi,vector<pipi>,comp> pq;
        vector<vector<pi>> vec(n+1,vector<pi>());
        for(int i=0;i<m;i++){
            cin>>u>>v>>w;
            vec[u].push_back(make_pair(w,v));
            vec[v].push_back(make_pair(w,u));
        }
        int source=1;visited[source]=1;
        for(auto p:vec[source]){
            pipi pp=make_pair(p.first,make_pair(min(source,p.second),max(source,p.second)));
            pq.push(pp);
        }
        while(!pq.empty()){
            auto pp=pq.top();pq.pop();
            if(!visited[pp.second.first]){
                ans.push_back(pp.second);cost+=pp.first;
                visited[pp.second.first]=1;
                for(auto p:vec[pp.second.first]){
                    if(!visited[p.second]){
                        pipi pee=make_pair(p.first,make_pair(min(pp.second.first,p.second),max(pp.second.first,p.second)));
                        pq.push(pee);
                    }
                }
            }else if(!visited[pp.second.second]){
                ans.push_back(pp.second);cost+=pp.first;
                visited[pp.second.second]=1;
                for(auto p:vec[pp.second.second]){
                    if(!visited[p.second]){
                        pipi pee=make_pair(p.first,make_pair(min(pp.second.second,p.second),max(pp.second.second,p.second)));
                        pq.push(pee);
                    }
                }
            }
        }
        if(ans.size()!=n-1){cout<<"IMPOSSIBLE\n";continue;}
        sort(ans.begin(),ans.end());
        cout<<cost<<"\n";
        for(auto p:ans){
            cout<<p.first<<" "<<p.second<<"\n";
        }
    }
    return 0;
}


/**
int main(){
    int n,m;
    while(cin>>n>>m){
        if(!n&&!m)break;
        unordered_map<int,int> um;
        priority_queue<pipi,vector<pipi>,comp> pq;
        vector<pi> ans;int cost=0,temp;
        for(int i=0;i<m;i++){
            int u,v,w;
            cin>>u>>v>>w;
            pq.push(make_pair(w,make_pair(min(u,v),max(u,v))));
        }
        while(!pq.empty()){
            cout<<pq.top().first<<endl;
            auto p = pq.top().second;
            temp=pq.top().first;
            pq.pop();
            if(um.count(p.first)==0 && um.count(p.second)==0){
                um.emplace(make_pair(p.first,1));
                um.emplace(make_pair(p.second,1));
                ans.push_back(p);
                cost+=temp;
            }else if(um.count(p.first)==0){
                um.emplace(make_pair(p.first,1));
                ans.push_back(p);
                cost+=temp;
            }else if(um.count(p.second)==0){
                um.emplace(make_pair(p.second,1));
                ans.push_back(p);
                cost+=temp;
            }
        } //doesnt work since u may have a,b visited alrd (in um) but u need to connect
        //a,b in order to form MST, this disallows that
        cout<<ans.size()<<cost<<endl;
        if(ans.size()!=n-1)cout<<"IMPOSSIBLE\n";
        else{
            sort(ans.begin(),ans.end());
            cout<<cost<<"\n";
            for(auto p:ans){
                cout<<p.first<<" "<<p.second<<"\n";
            }
        }
    }
}**/
