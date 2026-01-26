#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<ll> vll;

int main(){
    ll n,k,ti;
    cin>>n>>k;
    vll t;
    for(ll i=0;i<n;i++){
        cin>>ti;
        t.push_back(ti);
    }
    priority_queue<pll,vector<pll>,greater<pll>> minheap;
    sort(t.begin(),t.end());
    ll drivers=min(n,k);
    for(ll i=0;i<drivers;i++){
        minheap.push({t[i],t[i]});
    }
    ll rem=n;
    ll time=0;
    while(rem>0){
        pll fast=minheap.top();
        minheap.pop();
        time=max(time,fast.first);
        if(fast.first==fast.second){
            rem-=5;
        }else{
            rem-=4;
        }
        minheap.push({fast.first+2*fast.second,fast.second});
    }
    cout<<time<<"\n";
    return 0;
}
