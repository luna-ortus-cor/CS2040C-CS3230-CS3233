#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n,m,s,t;
    cin>>n>>m>>s>>t;
    vector<vector<ll>> adj(n);
    for(ll i=0;i<m;i++){
        ll x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<ll> squawks(n,0);
    squawks[s]=1;
    ll ans=0;
    for(ll i=0;i<t;i++){
        vector<ll> temp(n,0);
        ans=0;
        for(ll j=0;j<n;j++){
            if(squawks[j]>0){
                for(auto v:adj[j]){
                    temp[v]+=squawks[j];
                    ans+=squawks[j];
                }
            }
        }
        squawks=temp;
    }
    cout<<ans;
    return 0;
}
