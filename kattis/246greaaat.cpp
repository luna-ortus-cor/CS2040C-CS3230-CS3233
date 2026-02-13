#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
//#pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//The idea is clearly Dijkstra, by taking cheers (edges) with the smallest difficulty first
//However the number of enthusiasm states (vertices) is very large
//We can notice a few things
//Firstly, we can bound the number of states to [0,T+largest_minimum_si_cheer]
//This is because we can rearrange the order of cheers
//Then any sequence that sums to T has an ordering such that
//the partial sums are within this range
//Secondly, we improve on the time complexity of Dijkstra (which will TLE)
//By using Dial's Algorithm/Bucketed Dijkstra
//We maintain the list of list of all nodes with difficulty d
//We iterate through this for each difficulty d from 0 to T
//(also note that due to (1,1) cheer the upper bound for d is T)
//extract the nodes at this difficulty and then consider all
//possible next nodes (i.e. iterate through the cheers to determine next difficulty)
//again ensure this new enthusiasm is within bounds
//and update an array that stores the minimum difficulty to reach a given enthusiasm
//when we update we also update the parent (which enthusiasm level it came form)
//and the parent cheer (which cheer we took to arrive at new enthusiasm)
//Time complexity improves from O(VElogV) to O(VE) where V is also reduced
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N,T;
    cin>>N>>T;
    vector<pair<ll,ll>> cheer(N + 2);
    ll min_cheer=200005;
    ll max_cheer=-200005;
    for(ll i=1;i<=N;i++){
        ll S,D;
        cin>>S>>D;
        cheer[i+1]={S,D};
        min_cheer=min(min_cheer,S);
        max_cheer=max(max_cheer,S);
    }
    cheer[1]={1,1};
    min_cheer=min(min_cheer,1LL);
    max_cheer=max(max_cheer,1LL);
    ll MAX_NODE=T-min(min_cheer,0LL);
    unordered_map<ll, pair<ll,ll>> um; 
    vector<queue<ll>> Q(T+1);
    vector<ll> diff(MAX_NODE+1,LLONG_MAX);
    vector<ll> parent(MAX_NODE+1,-1);
    vector<ll> parent_cheer(MAX_NODE+1,-1);
    diff[0]=0;
    Q[0].push(0);
    for(ll d=0;d<=T;d++) {
        while(!Q[d].empty()){
            ll u=Q[d].front();Q[d].pop();
            if(diff[u]!=d)continue;
            for(ll i=1;i<=N+1;i++) {
                ll v=u+cheer[i].first;
                if(v<0||v>MAX_NODE)continue;
                ll nd=diff[u]+cheer[i].second;
                if(nd<diff[v]){
                    diff[v]=nd;
                    parent[v]=u;
                    parent_cheer[v]=i;
                    if(nd<=T)Q[nd].push(v);
                }
            }
        }
    }
    vector<ll> ans;
    ll curr=T;
    while(curr!=0){
        ans.push_back(parent_cheer[curr]);
        curr=parent[curr];
    }
    cout<<ans.size()<< "\n";
    for(auto x:ans)cout<<x<<" ";
    return 0;
}
