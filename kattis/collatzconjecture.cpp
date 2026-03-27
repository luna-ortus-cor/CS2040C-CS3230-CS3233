#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a,ll b){
    while(b){
        a%=b;
        swap(a,b);
    }
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin>>n;
    unordered_set<ll> D,d;
    ll a;
    for(int i=0;i<n;i++){
        cin>>a;
        unordered_set<ll> nd;
        for(ll v:d)nd.insert(gcd(v,a));
        nd.insert(a);
        for(ll v:nd)D.insert(v);
        d=move(nd);
    }
    cout<<D.size();
    return 0;
}
