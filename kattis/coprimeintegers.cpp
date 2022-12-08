#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// refer to https://codeforces.com/blog/entry/53925
// and https://crypto.stanford.edu/pbc/notes/numbertheory/mobius.html
// for understanding of the Mobius Inversion used to solve this

vector<int> mobius(ll stop){
    vector<int> visited(stop+1,0); //0 for havent visit, 1 for visited (known prime or known square of prime), -1 for visited but not prime and not square of prime
    vector<int> mu(stop+1,0); //use sieve of eratosthenes to eliminate known primes or known square of primes, O(nlogn)
    mu[0]=0;
    mu[1]=1;
    visited[0]=1;
    visited[1]=1;
    for(ll i=2;i<=stop;i++){
        if(visited[i]==0){
            visited[i]=1;
            mu[i]=-1;
            for(ll j = 2;j<=stop/i;j++){
                if(j%i==0){
                    visited[j*i]=1;
                    mu[j*i]=0;
                }else{
                    if(visited[j*i]!=1){
                        visited[j*i]=-1;
                        mu[j*i]++;
                    }
                }
            }
        }else if(visited[i]==-1){
            visited[i]=1;
            if(mu[i]%2==0){
                mu[i]=1;
            }else{
                mu[i]=-1;
            }
        }else{
            continue;
        }
    }
    return mu;
}

ll solve(ll b, ll d, vector<int> mu){
    ll s = 0;
    for(ll i=1;i<=min(b,d);i++){
        s+=mu[i]*((ll)b/i)*((ll)d/i);
    }
    return s;
}

int main(){
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    vector<int> mu = mobius(min(b,d));
    ll ans = solve(b,d, mu)-solve(a-1,d,mu)-solve(b,c-1,mu)+solve(a-1,c-1,mu);
    cout<<ans<<endl;
    return 0;
}
