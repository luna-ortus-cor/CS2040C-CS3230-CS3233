#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define inf 1000000007

// compute modular multiplicative inverse of b mod a (i.e. find b^-1)
// assume a>b
ll xEuclid(ll a, ll b, ll&x, ll&y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll x0, y0, gcd=xEuclid(b,a%b,x0,y0);
    x=y0;
    y=x0-(a/b)*y0;
    return gcd;
}

ll inverse(ll a, ll b){
    ll x,y;
    xEuclid(a,b,x,y);
    return y;
}

int main(){
    ll N,K,temp;
    cin>>N>>K;
    // pre compute all N factorials mod 10e9+7
    vector<ll> factorial(N+1);
    factorial[0]=1;
    for(int i=1;i<=N;i++){
        factorial[i]=factorial[i-1]*i%inf;
    }
    vector<ll> keys;
    for(ll i=0;i<N;i++){
        cin>>temp;
        keys.push_back(temp);
    }
    sort(keys.begin(),keys.end(),greater<int>());
    // for every key value, calculate how many combinations have
    // that key as maxmimum value (p choose q)
    int counter=N;
    ll ans = 0;
    int p = N-1;
    int q = K-1;
    int i = 0;
    while(counter>=K){
        // this does not work since modular division just doesnt work like that
        // temp = (ll) (keys[i]*(((factorial[p]%inf)/(factorial[q]*factorial[p-q]%inf))%inf))%inf;
        // rather, we make use of the fact that (a/b) mod m = a*b^-1 mod m, where b^-1 is modular inverse of b
        ll y1 = inverse(inf, factorial[q]);
        ll y2 = inverse(inf, factorial[p-q]);
        if(y1<0){
            y1+=inf;
        }
        if(y2<0){
            y2+=inf;
        }
        temp = (ll) ((keys[i]*factorial[p]%inf)*(y1*y2%inf))%inf;
        ans = (ans+temp)%inf;
        counter--;
        p--;
        i++;
    }
    cout<<ans<<endl;
}
