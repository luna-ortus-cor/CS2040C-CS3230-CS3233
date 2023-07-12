#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n;
    while(cin>>n){
        if(n<0){
            cout<<-1<<' ';
            n=abs(n);
        }
        ll power=0;
        while(n%2==0){
            power++;
            n/=2;
        }
        if(power&&power>1){
            cout<<2<<'^'<<power<<' ';
        }else if(power){
            cout<<2<<' ';
        }
        ll sq = pow(n,0.5)+1;
        for(ll i=3;i<=sq;i+=2){
            power=0;
            while(n%i==0){
                power++;
                n/=i;
            }
            if(power&&power>1){
                cout<<i<<'^'<<power<<' ';
            }else if(power){
                cout<<i<<' ';
            }
            sq=pow(n,0.5)+1;
        }
        if(n>1){
            cout<<n<<endl;
        }else{
            cout<<endl;
        }
    }
    return 0;
}
