#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define mod 1000000007

//this is the closed formula
//F(a,n) = fib(n+2a)+ \sum_{i=0}^{a-3} \binom{n+i}{i} fib(a-2-i) - \sum_{i=0}^{a-2} \binom{n+i}{i} fib(2(a-i)-1)
//if not, use
//F(x,y) = \sum_{i=0}^{x} \binom{x+y-1-i}{y-1}fib(i) + \sum_{i=0}^{y} \binom{x+y-1-i}{x-1}fib(i)
//since mod is prime, we notice that a^mod-1 = 1 mod mod
//so a^mod-2 = a^-1 mod mod i.e. a^mod-2 is modular inverse of a
//this is faster to calculate than finding modular inverse via extended euclid algorithm

vector<ll> fibo;
vector<ll> factorial;

//calculate a^n
ll power(ll base, ll e){
    ll res = 1;
    while(e>0){
        if(e%2==1){
            res = res*base%mod;
        }
        e/=2;
        base=base*base%mod;
    }
    return res;
}
//calculate modular inverse
ll inverse(ll a){
    return power(a, mod-2);
}
ll binom(ll n,ll k){
    if(k>n){
        return 0;
    }
    ll x1 = factorial[n];
    ll x2 = factorial[k]*factorial[n-k]%mod;
    return (x1*inverse(x2)%mod);
}

int main(){
    ll x,y;
    cin>>x>>y;
    if(x>y){
        swap(x,y);
    }
    fibo.push_back(0);
    fibo.push_back(1);
    for(int i=2;i<=y+2*x;i++){
        fibo.push_back((fibo[i-1]+fibo[i-2])%mod);
    }
    factorial.push_back(1);
    for(int i=1;i<=x+y;i++){
        factorial.push_back(i*factorial[i-1]%mod);
    }
    //method 1
    ll x1=0,x2=0;
    for(ll i=0;i<=x-3;i++){
        x1 = (x1+(binom(y+i,i)*fibo[x-2-i]%mod))%mod;
    }
    for(ll i=0;i<=x-2;i++){
        x2 = (x2+(binom(y+i,i)*fibo[2*(x-i)-1]%mod))%mod;
    }
    ll x3 = x1-x2;
    if(x3<0){
        x3+=mod;
    }
    x3 = (x3+fibo[y+2*x])%mod;
    cout<<x3<<endl;
    /*
    //method 2
    ll x4=0;
    for(ll i=0;i<=x;i++){
        x4 = (x4+(fibo[i]*binom(x+y-1-i,y-1)%mod))%mod;
    }
    for(ll i=0;i<=y;i++){
        x4 = (x4+(fibo[i]*binom(x+y-1-i,x-1)%mod))%mod;
    }
    cout<<x4<<endl;
    //both methods return same result
    //both methods also take about same time to run
    */
    return 0;
}
