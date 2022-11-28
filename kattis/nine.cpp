#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll fastexp(ll base,ll power,ll mod){
    ll ans=1;
    while(power>0){
        if(power%2==1){
            ans=ans*base%mod; 
            //e.g. for 9^99, we get the sequence 9^99=>9^49=>9^24=>9^12=>9^6=>9^3=>9^1=>9^0
            //which gives us multiplying by 9^1=>9^2=>n/a=>n/a=>n/a=>9^32=>9^64=>n/a
            //and,1+2+32+64=99
        }
        base=base*base%mod;
        power/=2;
    }
    return ans;
}

int main(){
    ll modulo = 1000000007;
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        ll d;
        ll ans=8;
        cin>>d;
        d--;
        ans=ans*fastexp(9,d,modulo)%modulo;
        cout<<ans<<endl;
    }
}
