#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll m=10000;
//very straightforward, need to implement fast mult and exp since inputs are very big (2^32)
//implent these via binary value of b, add/mult result by a whenever b%2
//add/mult a by itself, div b by 2 after every binary digit of b
ll add(ll a, ll b){
    return (a+b)%m;
}

ll mult(ll a, ll b){
    ll res=0;
    while(b){
        if(b%2){
            res=(res+a)%m;
        }
        b/=2;
        a=(a*2)%m;
    }
    return res%m;
}

ll exp(ll a, ll b){
    ll res=1;
    while(b){
        if(b%2){
            res=(res*a)%m;
        }
        b/=2;
        a=(a*a)%m;
    }
    return res%m;
}

int main(){
    ll a,b;char c;
    while(cin>>a>>c>>b){
        if(c=='+'){
            cout<<add(a,b)<<endl;
        }else if(c=='*'){
            cout<<mult(a,b)<<endl;
        }else{
            cout<<exp(a,b)<<endl;
        }
    }
    return 0;
}
