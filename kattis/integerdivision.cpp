#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//idea is just go thru list, divide by divisor
//add to unordered map (result:count), use combinatorics formula
//for each possible result, calc count(count-1)/2, add to ans

int main(){
    ll n,d,a;cin>>n>>d;
    unordered_map<ll,ll> um;
    for(ll i=0;i<n;i++){
        cin>>a;
        if(um.contains(a/d))um[a/d]++;
        else um.emplace(a/d,1);
    }
    ll ans=0;
    for(auto&it:um){
        ll s=it.second;
        ans+=((s*(s-1))/2);
    }
    cout<<ans<<endl;
    return 0;
}
