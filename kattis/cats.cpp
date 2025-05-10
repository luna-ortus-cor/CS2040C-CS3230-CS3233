#include <bits/stdc++.h>
using namespace std;

//this is a graph problem, specifically
//minimum spanning tree rooted at 0
//with the added constraint that each node
//also has cost 1, not just the edge cost
//use Prim's algorithm to determine MST
//and keep track of MST cost, then add
//number of cats to get total cost
//i.e. amt of milk minimally required
//maintain adjlist containing neighbouring cats and distance
//for each cat
//maintain pq of distances from all cats already visited to
//other cats not visited
//add cat 0 to visited
//add distances from cat 0 to other cats to pq
//then while not all cats visited
//pop smallest distance from pq, check not visited
//add the corresponding cat to visited
//add the adjlist of the new cat to pq

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T,M,C,i,j,D;
    cin>>T;
    while(T--){
        cin>>M>>C;
        vector<vector<pair<int,int>>> adj(C,vector<pair<int,int>>());
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(int x=0;x<C*(C-1)/2;x++){
            cin>>i>>j>>D;
            if(i==0 || j==0){
                pq.emplace(D,max(i,j));
            }else{
                adj[i].push_back(make_pair(D,j));
                adj[j].push_back(make_pair(D,i));
            }
        }
        set<int> visited;
        visited.insert(0);
        int cost=0;
        while(visited.size()!=C){
            auto [dist, idx]=pq.top();
            pq.pop();
            if(visited.count(idx)){
                continue;
            }
            visited.insert(idx);
            cost+=dist;
            for(auto [newdist,newidx] : adj[idx]){
                if(!visited.count(newidx)){
                    pq.emplace(newdist,newidx);
                }
            }
        }
        if(M>=C+cost){
            cout<<"yes\n";
        }else{
            cout<<"no\n";
        }
    }
    return 0;
}
