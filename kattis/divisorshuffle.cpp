#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N;
    cin>>N;
    unordered_map<ll,ll> factors;
    ll m = 0;
    ll temp;
    for(ll i = 0;i<N;i++){
        cin>>temp;
        m=max(m,temp);
        if(factors.find(temp)==factors.end()){
            factors.emplace(make_pair(temp,1));
        }else{
            factors[temp]++;
        }
    }
    ll B = m;
    m = 0;
    for(auto p:factors){
        if(B%p.first==0&&p.second!=1){
            m=max(m,p.first);
        }
        if(B%p.first!=0){
            m=max(m,p.first);
        }
    }
    ll A = m;
    cout<<A<<" "<<B<<endl;
}

//run time error
/*
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N;
    cin>>N;
    unordered_map<ll,ll> position;
    unordered_map<ll,ll> dup_position;
    ll m = 0;
    for(ll i=0;i<N;i++){
        ll temp;
        cin>>temp;
        if(position.find(temp)==position.end()){
            position.emplace(make_pair(temp,i));
        }else{
            dup_position.emplace(make_pair(temp,i));
        }
        m=max(m,temp);
    }
    ll B = m;
    ll A;
    while(true){
        position.erase(m);
        m=max_element(position.begin(),position.end())->first;
        if(B%m!=0){
            A=m;
            break;
        }
        if(B%m==0 && dup_position.find(m)!=dup_position.end()){
            A=m;
            break;
        }
    }
    cout<<A<<" "<<B<<endl;
    return 0;
}
*/
