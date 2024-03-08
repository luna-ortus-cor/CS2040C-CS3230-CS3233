#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//firstly note that 205023!=2.503898932×10^1000004 i.e. 1e6 digits
//next suppose there exists some bijective function H
//such that H(x)=x mod m for some m
//so given input x (which is n!) we can find y=H(x) mod m
//similarly calculate H(n!)=n! mod m
//by choosing large m, we reduce the chance of collision
//wherein H(p)=H(q) but p!=q
//note ideal choice of m should be prime 
//calculation of H is simple, for every digit
//take current ans (modded), mult 10, add digit, re mod

const ll m = 1e9+7;
//use smallest 10 digit prime first, 1e9+7
//trial and error if 1e9+7 doesnt work

int main(){
    string x;
    cin>>x;
    ll y=0;
    for(char c:x){
        y=(y*10 + c-'0')%m;
    }
    //for(ll i=1,n=1;i<205023;i++){ 
        //will go up to 205023 only
        //the i<205023 is technically unnecessary
    for(ll i=1,n=1;;i++){
        n=n*i%m;
        if(n==y){
            cout<<i<<endl;
            return 0;
        }
    }
    return 0;
}
