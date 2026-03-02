#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//this is O(N^2) worst case (with log1e13=44 as constant factor)
//bsta on S, there should be a way for O(N) or O(NlogN) check though (using DSU?)
//check is minimally O(N) though, since for any starting point we have to iterate
//through entire array to determine if feasible

bool check(const ll S, const ll n, const vector<ll>& a) {
    vector<int> visited(n,0);
    for(ll i=0;i<n;i++){
        if(a[i]>S||visited[i])continue;
        ll l=i,r=i;
        ll curr=S+a[i];
        ll count=1;
        visited[i]=1;
        while(count<n){
            ll nr=(r+1)%n,nl=(l-1+n)%n;
            if(curr>=a[nr]){
                curr+=a[nr];
                r=nr;
                visited[r]=1;
                count++;
            }else if(curr>=a[nl]){
                curr+=a[nl];
                l=nl;
                visited[l]=1;
                count++;
            }else{
                break;
            }
        }
        if(count==n)return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin>>n;
    vector<ll> spice(n);
    for(int i=0;i<n;i++)cin>>spice[i];
    ll lo=0,hi=1e13;
    ll ans=1e13;
    while(lo<=hi){
        ll mid=(lo+hi)/2;
        if(check(mid,n,spice)){
            ans=mid;
            hi=mid-1;
        }else lo=mid+1;
    }
    cout<<ans;
    return 0;
}
