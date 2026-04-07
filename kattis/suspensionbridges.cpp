#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld f(ld a,ld d,ld s){
    return a*coshl(d/(2*a))-a-s;
}

ld solve(ld d,ld s){
    ld lo=1e-9,hi=1e9;
    for(int i=0;i<1000;i++){
        ld mid=(lo+hi)/2;
        if(f(mid,d,s)>0) lo=mid;
        else hi=mid;
    }
    ld a=(lo+hi)/2;
    return 2*a*sinhl(d/(2*a));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ld d,s;
    cin>>d>>s;
    cout<<fixed<<setprecision(10)<<solve(d,s);
}
