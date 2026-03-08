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
        vector<ll> w(n),l(n);
        for(ll i=0;i<n;i++)cin>>w[i];
        for(ll i=0;i<n;i++)cin>>l[i];
        ll wsum=accumulate(w.begin(),w.end(),0LL);
        ll lsum=accumulate(l.begin(),l.end(),0LL);
        ll diff=wsum-lsum;
        sort(l.begin(),l.end());
        ll ans=l[0];
        for(ll i=1;i<n;i++){
            ll delta=l[i]-l[i-1];
            if(i*delta<=diff){
                diff-=i*delta;
                ans=l[i];
            }else{
                ans+=diff/i;
                diff=0LL;
                break;
            }
        }
        ans+=diff/n;
        cout<<ans<<"\n";
    }
    return 0;
}
