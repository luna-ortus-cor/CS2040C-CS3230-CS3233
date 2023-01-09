#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ll;

//we use miller primality test (deterministic)
//use fastmul in fastexp to prevent integer overflow, otherwise 128 bit integers will be needed

ll fastmul(ll a, ll b, ll mod){
    ll ans = 0;
    while(b>0){
        if(b%2==1){
            ans=(ans+a)%mod;
        }
        a=(a*2)%mod;
        b/=2;
    }
    return ans;
}

ll fastexp(ll base, ll power, ll mod){
    ll ans=1;
    base=base%mod;
    while(power>0){
        if(power%2==1){
            ans=fastmul(ans,base,mod);
        }
        base=fastmul(base,base,mod);
        power/=2;
    }
    return ans%mod;
}

bool check_composite(ll n, ll a, ll d, ll s) {
    ll x = fastexp(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = fastmul(x,x,n);
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(ll n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    ll r = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int main(){
    ll N;
    cin>>N;
    if(N<=10000000000000000){
        ll limit = (ll) pow(N,0.5)+1;
        if(N==2){
            cout<<"YES"<<endl;
            return 0;
        }
        if(N%2==0){
            cout<<"NO"<<endl;
            return 0;
        }
        for(ll i=3;i<=limit;i+=2){
            if(N%i==0){
                cout<<"NO"<<endl;
                return 0;
            }
        }
        cout<<"YES"<<endl;
        return 0;
    }else{
        if(MillerRabin(N)){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
        return 0;
    }
}
