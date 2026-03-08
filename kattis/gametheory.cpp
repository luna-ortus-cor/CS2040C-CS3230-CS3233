#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> dplus,dminus,p,a;

ll solveminus(ll x,ll n);

ll solveplus(ll x,ll n){
    if(x>n)return 0LL;
    if(dplus[x]!=2e18)return dplus[x];
    ll val=-2e18;
    for(ll k=p[x];k<=2*n;k+=p[x]){
        val=max(val,solveminus(x+k,n));
    }
    dplus[x]=a[x]+val;
    return dplus[x];
}

ll solveminus(ll x,ll n){
    if(x>n)return 0LL;
    if(dminus[x]!=2e18)return dminus[x];
    ll val=2e18;
    for(ll k=p[x];k<=2*n;k+=p[x]){
        val=min(val,solveplus(x+k,n));
    }
    dminus[x]=a[x]+val;
    return dminus[x];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll C;
    cin>>C;
    while(C--){
        ll n;
        cin>>n;
        p.resize(n+1,2e18);
        a.resize(n+1,2e18);
        for(ll i=1;i<=n;i++)cin>>p[i];
        for(ll i=1;i<=n;i++)cin>>a[i];
        dplus.assign(n+1,2e18);
        dminus.assign(n+1,2e18);
        for(ll i=1;i<=n;i++)cout<<solveplus(i,n)<<" ";
        cout<<"\n";
    }
    return 0;
}
