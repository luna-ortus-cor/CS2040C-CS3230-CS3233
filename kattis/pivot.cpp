#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//do 2 passes through array
//in forward pass keep track of max element seen so far and store at each index
//in backward pass keep track of min element seen so far aand store at each index
//then a pivot p is such that v[i]<=p<=v[j] for all i before p and j after p
//i.e. pivot p iff forward and backward passes return same value at an index

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin>>n;
    vector<int> forward(n,0);
    vector<int> backward(n,0);
    vector<int> nums;
    int num;
    while(cin>>num){
        nums.push_back(num);
    }
    int m=nums[0];
    for(int i=0;i<n;i++){
        m=max(m,nums[i]);
        forward[i]=m;
    }
    m=nums[n-1];
    for(int i=n-1;i>-1;i--){
        m=min(m,nums[i]);
        backward[i]=m;
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(forward[i]==backward[i])ans++;
    }
    cout<<ans;
    return 0;
}
