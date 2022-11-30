#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// consider 1^b + 2^b + ... + a^b
// obvious that a^b = 0 mod a
// then (a-1)^b = (-1)^b mod a = -(1^b) mod a since b odd
// likewise, (a-2)^b = (-2)^b mod a = -(2^b) mod a
// so, if a is odd, then all the terms will cancel to 0
// if a is even, then take a/2 for the middle uncanceled term
// if b=1, then (a/2)^b = a/2 mod always, else
// if a/2 is even, then 0
// if a/2 is odd, then a/2
// to see why, consider x^b mod 2x, for x odd (x=2y+1) and x even (x=2y)
// if x=2y, then x^b=2^by^b mod 4y, which =0 for any b>=2
// if x=2y+1, then x^b=(4y+2)(P(x))+(2y+1)=2y+1 mod 2x
// intuitively this is because, modulo 4y+2, 
// (2y+1)^b=2y(2y+1)^(b-1)+1(2y+1)^(b-1)=(2y+1)^(b-1)=...=(2y+1)

int main(){
    ll a,b;
    cin>>a>>b;
    if(a%2==1){
        cout<<0<<endl;
    }else{
        a/=2;
        if(b==1){
            cout<<a<<endl;
        }else if(a%2==0){
            cout<<0<<endl;
        }else{
            cout<<a<<endl;            
        }
    }
}
