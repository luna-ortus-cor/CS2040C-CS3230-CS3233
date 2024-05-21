#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//idea is just count how many times 2 divides the x's
//then check if this is >= K

ll div(ll x){
    ll ans=0;
    while(x%2==0){
        ans++;
        x/=2;
    }
    return ans;
}

int main(){
    ll N,K,x;cin>>N>>K;
    ll ans=0;
    while(N--){
        cin>>x;ans+=div(x);
    }
    cout<<(ans>=K?1:0)<<endl;
    return 0;
}
