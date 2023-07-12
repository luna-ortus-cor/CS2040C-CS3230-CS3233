#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//suppose we have n which is prime factorizable
//n = p1^x1 * p2^x2 * ... * pi^xi
//then the highest power of p that divides m!
//is f(m,p) = \sum floor(m/p) + floor(m/p^2) + ... 
//the highest power of n that divides m! is
//min(f(m,pi)/xi) over all i
//include additional statement to handle when n is prime 
//or when n has a prime factor larger than its square root e.g. 10=2*5, sqrt(10)<4
//https://math.stackexchange.com/questions/49670/how-to-find-maximum-x-that-kx-divides-n

ll f(ll m, ll p){
    ll ans = 0;
    ll pp = p;
    while(pp<=m){
        ans += m/pp;
        pp*=p;
        //cout<<pp<<' '<<ans<<endl;
    }
    return ans;
}

ll k(ll n, ll m){
    ll i = 2;
    ll ans = 100000000000000;
    ll sq = pow(n,0.5)+1;
    while(i<=sq){
        ll power = 0;
        while(n%i==0){
            power++;
            n/=i;
        }
        if(power){
            ans = min(ans,f(m,i)/power);
            //cout<<ans<<' '<<m<<' '<<i<<' '<<power<<endl;
        }
        i++;
    }
    if(n!=1){
        ans = min(ans,f(m,n));
    }
    return ans;
}

int main(){
    ll n,m;
    cin>>n>>m;
    cout<<k(n,m)<<endl;
    return 0;
}
