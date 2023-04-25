#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define inf 9223372036854775807

//we modify modified dijkstra to ascertain lowest cost to target
//while also keeping track of relevant parents in the lowest cost path

int main(){
    int P,T;
    cin>>P>>T;
    vector<vector<pll>> AL(P,vector<pll>());
    unordered_map<ll,unordered_map<ll,ll>> AM;
    vector<vector<ll>> parent(P,vector<ll>());
    priority_queue<pll,vector<pll>,greater<pll>> pq;
    vector<ll> dist(P,inf);
    vector<ll> visited(P,0);
    
    for(int i=0;i<T;i++){
        ll p1,p2,w;
        cin>>p1>>p2>>w;
        if(p1==p2){
            continue;
        }
        AL[p1].push_back(make_pair(w,p2)); //allows for multiple path of same length between p1,p2
        AL[p2].push_back(make_pair(w,p1));
        if(AM.count(p1)==0||AM[p1].count(p2)==0){ //check if p1,p2 already have other weights in AM
            AM[p1][p2]=w;
            AM[p2][p1]=w;
        }else{ //else take min value of current and new weight (in case there are multiple paths between p1,p2)
            AM[p1][p2]=min(AM[p1][p2],w);
            AM[p2][p1]=min(AM[p2][p1],w);
        } //ensure if multiple path between p1,p2 they must be of same length
    }
    pq.push(make_pair(0,0));
    dist[0]=0;
    while(!pq.empty()){
        ll curr = pq.top().second;
        pq.pop();
        if(visited[curr]){ //dijkstra guarantees we will not need to revisit node once popped from pq since shortest dist alrd
            continue;
        }
        visited[curr]=1;
        //alternatively if dont want use visited can check
        //if pq.top().first>dist[curr] continue
        for(pll p:AL[curr]){
            ll w = p.first;
            ll c = p.second;
            if(dist[curr]+w<dist[c]){
                dist[c]=dist[curr]+w;
                parent[c].clear(); //all old parents invalid
                parent[c].push_back(curr); 
                pq.push(make_pair(dist[c],c));
            }else if(dist[curr]+w==dist[c]){ //the difference
                parent[c].push_back(curr);
            }
        }
    }
    int ans=0;
    visited.clear();
    visited.resize(P,0); //reinitialize visited to make sure we dont double count weights when finding parents
    //i.e. if we come across a parent previously we dont want to readd weights of its parents etc.
    queue<ll> q;
    q.push(P-1);
    while(!q.empty()){ //add weights of the parents of highest peak recursively until entrance
        ll curr = q.front();
        q.pop();
        if(visited[curr]){
            continue;
        }
        visited[curr]=1;
        for(ll p:parent[curr]){ //enum all possible parent paths
            ans+=AM[curr][p];
            q.push(p);
        }
    }
    cout<<ans*2<<endl; //dont forget to x2
}
