#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//determine N such that exists X such that NC=KX+1 i.e. NC=1modK
//i.e. multiplicative inverse of C modulo K
//using extended euclidean algorithm
//need to handle special case of C=1, K=1 (or both)

ll mod(ll a, ll b){return(a%b+b)%b;} //to handle negative modulo

ll eea(ll a, ll b){//find mult inverse of a mod b
    ll n=b;ll q,r=-1;
    ll t1=0,t2=1,t3;
    ll s1=1,s2=0,s3;
    while(r){
        q=b/a;r=b%a;
        s3=s1-(q*s2);t3=t1-(q*t2);
        //cout<<b<<" "<<a<<" "<<q<<" "<<r<<" "<<t1<<" "<<t2<<" "<<t3<<"\n";
        b=r==0?b:a;
        a=r==0?a:r;
        s1=r==0?s1:s2;s2=r==0?s2:s3;
        t1=r==0?t1:t2;t2=r==0?t2:t3;
    }
    if(a==1){return mod(t2,n);}
    else{return 0;}
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll t,K,C,ans;cin>>t;
    while(t--){
        cin>>K>>C;
        if(K==1){cout<<(C>1?1:2)<<"\n";continue;}
        if(C==1){cout<<K+1<<"\n";continue;}
        ans=eea(C,K);
        if(ans)cout<<ans<<"\n";
        else cout<<"IMPOSSIBLE\n";
    }
    return 0;
}
