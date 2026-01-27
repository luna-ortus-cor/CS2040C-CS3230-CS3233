#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//note that for i<j, for j to be reachable from i
//we must have j-i=ai+aj <=> j-aj=ai+i
//likewise for i>j, just swap the indices
//we can precompute these for each i,j
//then initialize a queue with start pebble
//and bfs to find all reachable pebbles
//at same time keep track of max dist pebble

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N;
    cin>>N;
    vector<ll> pebble(N);
    unordered_map<ll,vector<ll>> i_to_p;
    unordered_map<ll,ll> p_to_i;
    unordered_map<ll,vector<ll>> j_to_p;
    unordered_map<ll,ll> p_to_j;
    for(ll k=0;k<N;k++){
        cin>>pebble[k];
        ll i=pebble[k]+k;
        ll j=k-pebble[k];
        i_to_p[i].push_back(k);
        p_to_i[k]=i;
        j_to_p[j].push_back(k);
        p_to_j[k]=j;
    }
    vector<int> visited(N,0);
    queue<ll> q;
    q.push(0);
    visited[0]=1;
    ll ans=0;
    while(!q.empty()){
        ll curr=q.front();
        ans=max(ans,curr);
        q.pop();
        for(ll next:j_to_p[p_to_i[curr]]){
            if(visited[next]==0){
                visited[next]=1;
                q.push(next);
            }
        }
        for(ll next:i_to_p[p_to_j[curr]]){
            if(visited[next]==0){
                visited[next]=1;
                q.push(next);
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
