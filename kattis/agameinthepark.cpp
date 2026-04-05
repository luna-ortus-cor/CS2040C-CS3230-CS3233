#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ll n;
    cin>>n;
    vector<vector<ll>> grid(4,vector<ll>(n));
    for(ll i=0;i<4;i++){
        for(ll j=0;j<n;j++){
            cin>>grid[i][j];
        }
    }
    vector<ll> masks({0,1,2,4,5,8,9,10});
    vector<ll> dp(8,-1e18);
    dp[0]=0;
    for(ll j=0;j<n;j++){
        vector<ll> ndp(8,-1e18);
        vector<ll> sums(8,0);
        for(ll i=0;i<8;i++){
            for(ll k=0;k<4;k++){
                if((masks[i]>>k)&1)sums[i]+=grid[k][j];
            }
        }
        for(ll i=0;i<8;i++){
            for(ll j=0;j<8;j++){
                if(!(masks[i]&masks[j])){
                    ndp[i]=max(ndp[i],dp[j]+sums[i]);
                }
            }
        }
        dp=move(ndp);
    }
    cout<<*max_element(dp.begin(),dp.end());
    return 0;
}
