#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf 100000000000000000
 
//same as below except we realise a,b are relatively small (<1E6)
//and so brute force on b is possible
 
ll find(ll n, ll k, vector<ll> &fib){
    if(k-3>=fib.size()){
        return 0;
    }
    ll ans = 0;
    for(ll b = 1;b<=n;b++){
        
        ll a = (n-(b*fib[k-2]))/fib[k-3];
        
        if(0<=a&&a<=b&&a*fib[k-3]+b*fib[k-2]==n){
            //cout<<a<<' '<<b<<endl;
            ans++;
        }
    }
    return ans;
}
 
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    vector<ll> fib={1,1};
    ll f = 0;
    while(f<=inf){
        vector<ll>::iterator it = fib.end();
        f = *(it-1) + *(it-2);
        fib.push_back(f);
    }
    ll tc,n,k;
    cin>>tc;
    while(tc--){
        cin>>n>>k;
        ll ans = find(n,k,fib);
        cout<<ans<<endl;
    }
    return 0;
}
