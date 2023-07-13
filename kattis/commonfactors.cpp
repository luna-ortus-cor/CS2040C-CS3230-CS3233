#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf (ll)1000000000000000000

//we observe, by definition of euler totient function
//phi(k) = k \Pi_{p|k} (1-(1/p))
//this gives number of coprime integers, and so
//number of non coprime integers is then
//k-phi(k) = f(k) = k(1-\Pi_{p|k} (1-(1/p)))
//and g(k) = (k-phi(k))/k = 1- \Pi_{p|k} (1-(1/p))
//for k<=n, max g(k) is obtained at min \Pi_{p|k} (1-(1/p))
//it is simple to see that this k is obtained by multiplying 
//prime numbers p1, p2, p3,... until product is maximal
//and less than or equal to n
//we further observe, by the constraint of n<=10E18,
//that multiplication of all prime numbers below 50 
//gives us a product just below that bound
//we make further use of the fact that
//phi(m)phi(n) = phi(mn) for coprime m,n
//to calcuate phi(k)
//calculating g(k) is straightforward
//given numerator k-phi(k) and denominator k
//we know factorization of k, and fraction can 
//only be simplified for factors of k
//so just iterate through primes and check
//if p divides k-phi(k) and p divides k
//Note: multiplying primes must check no overflow

int main(){
    vector<ll> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};
    vector<ll> totient;
    for(auto p:primes){
        totient.push_back(p-1);
    }
    ll n;
    cin>>n;
    ll k = 1;
    ll t = 1;
    vector<ll>::iterator it = primes.begin();
    vector<ll>::iterator tot = totient.begin();
    while(k*(*it)<=n && inf/k>(*it)){
        k*=(*it);
        it++;
        t*=(*tot);
        tot++;
    }
    ll num = k-t;
    ll denom = k;
    //cout<<num<<'/'<<denom<<endl;
    for(auto p:primes){
        //cout<<p<<' '<<num<<' '<<denom<<endl;
        if(num%p==0 && denom%p==0){
            num/=p;
            denom/=p;
        }
    }
    cout<<num<<'/'<<denom<<endl;
    return 0;
}
