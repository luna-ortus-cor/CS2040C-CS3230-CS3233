#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//we will use a generalization of euler (totient) theorem
//claim: for any n,m, n^2phi(m)=n^phi(m) mod m
//proof: for all prime power p^k|m
//case p|n
//we have phi(m)>=phi(p^k)>=p^(k-1)(p-1)>=2^(k-1)>=k
//so p^k|n^k|n^phi(m) and n^k=0 mod p^k => n^phi(m)=0 mod p^k => n^2phi(m)=0 mod p^k
//thus n^2phi(m)=n^phi(m)=0 mod p^k
//case p|/n
//now n,p are coprime =>n,p^k are coprime
//by euler (totient) theorem have
//n^phi(p^k)=1 mod p^k and since phi(p^k)|phi(m) => d*phi(p^k)=phi(m)
//we have n^phi(m)=n^d*phi(p^k)=1^d=1 mod p^k
//so both n^2phi(m) and n^phi(m) satisfy
//x=1 mod pi^k, x=0 mod pj^k for relevant pi,pj with pi!=pj
//and by the uniqueness result of CRT result follows
//so n^2phi(m)=n^phi(m) mod m for all n,m
//corollary: if k>=phi(m) then n^k=n^(phi(m)+k mod phi(m)) mod m
//refer to https://codegolf.stackexchange.com/questions/124391/evaluate-modular-power-towers

ll phi(ll x){
    ll res=1;
    for(ll p=2;p*p<=x;p++){
        if(x%p==0){
            res*=(p-1);
            x/=p;
        }
        while(x%p==0){
            res*=p;
            x/=p;
        }
    }
    if(x>1){
        res*=(x-1);
    }
    return res;
}

ll pow(ll a, ll b, ll m){ //a^b mod m
    ll res=1;
    while(b){
        if(b&1){
            res=(res*a)%m;
        }
        b/=2;
        a=(a*a)%m;
    }
    return res;
}

ll trunc(ll n){ //handle small case separately
    return n<4?n<3?n:9:1<<9;
}

ll solve(ll n, ll m){ //impl of the formula
    if(m==1)return 0;
    if(n==1)return 1;
    ll pm=phi(m);
    ll e=trunc(n-1);
    if(e==1<<9){
        e=pm+solve(n-1,pm);
    }
    return pow(n,e,m);
}

int main(){
    ll n,m;
    cin>>n>>m;
    cout<<solve(n,m)<<endl;
    return 0;
}
