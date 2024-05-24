#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//idea is given n,b, want to find x such that
//(b+1)^x>=n, since given b guesses able to split 
//search space into b+1 partition
//so x is ceil(log_(b+1)n), or just brute force iterate
//at most 63 (NO!)
//should be floor(log(n,b+1))+1 and not ceil(log(n,b+1))
//simplest eg to see why: 
//consider b=1, n=2^x, if use ceil, will be off by 1
//so use floor, even though in MOST CASES floor+1 and ceil will be equal

int main(){
    ll n,b;cin>>n>>b;
    cout<<floor(log(n)/log(b+1))+1<<endl;
    return 0;
}

//that is why this doesnt work (fails for perfect powers)
/**
int main(){
    ll n,b;cin>>n>>b;ll a=1;
    if(n==1){cout<<0<<endl;return 0;}
    for(int i=1;i<64;i++){
        a*=(b+1);
        if(a>=n){
            cout<<i<<endl;
            break;
        }
    }
    return 0;
}**/
