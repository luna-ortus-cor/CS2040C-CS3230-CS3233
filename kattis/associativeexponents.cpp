#include <bits/stdc++.h>
#define inf 1000000007
using namespace std;
typedef long long ll;
//just do the usual fast exponentiation algorithm, modulo a prime modulo
//here mod 1e9+7
ll expmod(ll x, ll y, ll m){
    ll res=1;
    while(y){
        if(y%2){
            res=(res*x)%m;
        }
        y/=2;
        x=(x*x)%m;
    }
    return res;
}

int main(){
    ll a,b,c;
    cin>>a>>b>>c;
    if(expmod(expmod(a,b,inf),c,inf)==expmod(a,expmod(b,c,inf),inf)){
        cout<<"What an excellent example!"<<endl;
    }else{
        cout<<"Oh look, a squirrel!"<<endl;
    }
    return 0;
}
