#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define modulo 1000000007

ll fastexp(ll base, ll power){
    ll ans = 1;
    while(power){
        if(power%2){ //or if(power&1)
            ans = (ans*base)%modulo;
        }
        base=(base*base)%modulo;
        power>>=1;
    }
    return ans;
}

int main(){
    ll T,R,C;
    cin>>T;
    for(ll i = 0;i<T;i++){
        cin>>R>>C;
        //if 1x1, 18
        //every extra R,C along axis, x6
        //every extra R,C not along axis, x2
        //18*6^(R-1+C-1)*2^((R-1)(C-1))
        //cout<<18*fastexp(6,R+C-2)%modulo*fastexp(2,(R-1)*(C-1))%modulo<<endl;
        //i think there's some modulo error in the above, we simplify by
        //3^(R+C)*2^RC
        //3^2 * 2^1 * 2^(RC-R-C+1) * 3^(R+C-2) * 2^(R+C-2)
        //3^(R+C) * 2^RC
        cout<<(fastexp(3,R+C)*fastexp(2,R*C))%modulo<<endl;
    }
    return 0;
}
