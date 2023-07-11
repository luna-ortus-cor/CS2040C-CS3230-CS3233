#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//use euclidean to find gcd
ll gcd(ll x, ll y){
    while(y!=0){
        ll temp = y;
        y = x%y;
        x=temp;
    }
    return x;
}

//use gcd to find lcm
ll lcm(ll x, ll y){
    ll d = gcd(max(x,y),min(x,y));
    return x/d*y;
}

int main(){
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    cout<< b/lcm(c,d) - a/lcm(c,d) + (a%lcm(c,d)?0:1)<<endl;
    return 0;
}
