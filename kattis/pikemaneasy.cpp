#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll next(ll A, ll B, ll C, ll t){
    return ((A*t+B)%C)+1;
}

int main(){
    ll N,T;
    cin>>N>>T;
    vector<ll> ts;
    ll A,B,C,t;
    cin>>A>>B>>C>>t;
    ts.push_back(t);
    for(ll i=1;i<N;i++){
        ll temp = next(A,B,C,t);
        t=temp;
        ts.push_back(t);
    }
    sort(ts.begin(),ts.end());
    ll n=0,tt=0,pen=0;
    while(tt+ts[n]<=T && n<N){
        //cout<<ts[n]<<endl;
        tt+=ts[n];
        pen=(pen+tt)%1000000007;
        n++;
    }
    cout<<n<<" "<<pen<<"\n";
    return 0;
}
