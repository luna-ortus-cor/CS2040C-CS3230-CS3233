#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll C;
    cin>>C;
    while(C--){
        ll n;
        cin>>n;
        ll ans=0;
        vector<ll> a(n);
        for(ll i=0;i<n;i++)cin>>a[i];
        vector<ll> x(n,0LL);
        for(ll b=63;b>=0;b--){
            if(ans&(1LL<<b))continue;
            vector<ll> idx;
            for(ll i=0;i<n;i++){
                if(a[i]&(1LL<<b))idx.push_back(i);
            }
            if(idx.size()>=2){
                x[idx[0]]|=(1LL<<b);
                ans|=(1LL<<b);
                x[idx[1]]|=((1LL<<b)-1LL);
                ans|=((1LL<<b)-1LL);
                break;
            }else if(idx.size()==1){
                x[idx[0]]|=(1LL<<b);
                ans|=(1LL<<b);
            }
        }
        cout<<ans<<"\n";
        for(ll i=0;i<n;i++)cout<<x[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
