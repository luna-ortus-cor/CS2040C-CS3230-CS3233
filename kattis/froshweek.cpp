#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

//we use mergesort to solve this
//we have two pointers i,j pointing at the start of the left and right arrays (sorted in descending)
//if the left pointer is greater than the right pointer, then every element in the right is smaller than the left, so we add the number of items at and after the pointer
//to the ans array, which contains the number of integers smaller and to the right of a number
//we continue mergesort in the normal way

void merge(vector<pll> &v, vector<ll> &ans, ll l, ll m, ll h){
    vector<pll> temp;
    ll i,j;
    i=l;
    j=m+1;
    while(i<=m&&j<=h){
        if(v[i].first>v[j].first){
            temp.push_back(v[i]);
            ans[v[i].second]+=(h-j+1);
            i++;
        }else{
            temp.push_back(v[j]);
            j++;
        }
    }
    while(i<=m){
        temp.push_back(v[i]);
        i++;
    }
    while(j<=h){
        temp.push_back(v[j]);
        j++;
    }
    for(ll k=0,i=l;k<temp.size();k++,i++){
        //cout<<temp[k]<<endl;
        v[i]=temp[k];
    }
}

void mergesort(vector<pll> &v, vector<ll> &ans, ll l, ll h){
    if(l<h){
       ll m = (l+h)/2;
       mergesort(v,ans,l,m);
       mergesort(v,ans,m+1,h);
       merge(v,ans,l,m,h); 
    }
}

int main(){
    ll n;
    cin>>n;
    vector<pll> v;
    vector<ll> ans(n,0);
    ll temp;
    for(ll i=0;i<n;i++){
        cin>>temp;
        v.push_back(make_pair(temp,i));
    }
    mergesort(v,ans,0,n-1);
    ll s=0;
    for(ll i=0;i<n;i++){
        //cout<<ans[i]<<endl;
        s+=ans[i];
    }
    cout<<s<<endl;
    return 0;
}
