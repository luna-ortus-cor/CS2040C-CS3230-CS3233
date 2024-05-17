#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main(){
    ll N;cin>>N;stack<ll> s;
    for(ll i=1;i<=1000000;i++){
        if(i*i>N){
            break;
        }
        if(N%i==0){
            cout<<i-1<<" ";
            if(N/i!=i){
                s.push(N/i-1);
            }
        }
    }
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
    }
    return 0;
}
