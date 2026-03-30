#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin>>s;
    const ll mod=1e9+7;
    ll one=0;
    ll inv=0;
    ll branch=1;
    for(char c:s){
        if(c=='1')one=(one+branch)%mod;
        else if(c=='0')inv=(inv+one)%mod;
        else{
            inv=(2*inv+one)%mod;
            one=(2*one+branch)%mod;
            branch=(2*branch)%mod;
        }
    }
    cout<<inv;
    return 0;
}
