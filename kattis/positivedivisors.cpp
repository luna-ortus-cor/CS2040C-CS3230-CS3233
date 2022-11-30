#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    vector<ll> forward;
    vector<ll> backward;
    ll N;
    cin>>N;
    for(ll i=1;i<=(ll)pow(N,0.5);i++){
        if(N%i==0 && i!=N/i){
            forward.push_back(i);
            backward.push_back(N/i);
        }else if(N%i==0){
            forward.push_back(i);
        }else{
            continue;
        }
    }
    for(ll i=0;i<forward.size();i++){
        cout<<forward[i]<<endl;
    }
    for(ll i=backward.size()-1;i>=0;i--){
        cout<<backward[i]<<endl;
    }
}
