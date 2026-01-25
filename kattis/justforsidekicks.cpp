#include <bits/stdc++.h>
using namespace std;
#define LSOne(S) ((S)&-(S))
typedef long long ll;
typedef vector<ll> vll;

class FenwickTree{
private:
    vll ft;
public:
    FenwickTree(ll m){ft.assign(m+1,0);}
    ll rsq(ll j){
        ll sum=0;
        for(;j;j-=LSOne(j))
            sum+=ft[j];
        return sum;
    }
    ll rsq(ll i,ll j){return rsq(j)-rsq(i-1);}
    void update(ll i,ll v){
        for(;i<(ll)ft.size();i+=LSOne(i))
            ft[i]+=v;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N,Q,V1,V2,V3,V4,V5,V6,a,b,c;
    cin>>N>>Q;
    cin>>V1>>V2>>V3>>V4>>V5>>V6;
    vll values={V1,V2,V3,V4,V5,V6};
    vector<FenwickTree> vft(6,FenwickTree(N));
    string P;
    cin>>P;
    unordered_map<ll,ll> um;
    for(ll i=0;i<N;i++){
        vft[P[i]-'1'].update(i+1,1);
        um[i]=P[i]-'1';
    }
    while(Q--){
        cin>>a>>b>>c;
        if(a==1){
            vft[um[b-1]].update(b,-1);
            vft[c-1].update(b,1);
            um[b-1]=c-1;
        }else if(a==2){
            values[b-1]=c;
        }else if(a==3){
            ll sum=0;
            for(ll i=0;i<6;i++){
                sum+=vft[i].rsq(b,c)*values[i];
            }
            cout<<sum<<"\n";
        }
    }
    return 0;
}
