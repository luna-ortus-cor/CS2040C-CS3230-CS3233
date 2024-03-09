#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
//straightforward pq implementation
struct myComp{
    constexpr bool operator()(pair<ll,ll> const& a,pair<ll,ll> const& b) const noexcept{
        return a.first!=b.first ? a.first<b.first : a.second>b.second;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--){
        ll n,k;
        cin>>n>>k;
        priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,myComp> pq;
        for(ll i=1;i<n+1;i++){
            ll h;
            cin>>h;
            ll rem = (h%k==0 ? k:h%k);
            pq.push(make_pair(rem,i));
        }
        while(!pq.empty()){
            auto p = pq.top();
            pq.pop();
            cout<<p.second<<' ';
        }
        cout<<endl;
    }
    return 0;
}
