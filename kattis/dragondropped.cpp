#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll N;
    cin>>N;
    ll s,e;
    ll K=0;
    while(true){
        cout<<"NEXT GABBY\n"<<flush;
        cin>>s>>e;
        cout<<"NEXT SPIKE\n"<<flush;
        cin>>s>>e;
        cout<<"NEXT SPIKE\n"<<flush;
        cin>>s>>e;
        //if(s==0){cout<<"ASK SPIKE\n"<<flush;return 0;}
        K++;
        if(e==1)break;
    }
    ll L=0;
    while(true){
        cout<<"NEXT SPIKE\n"<<flush;
        cin>>s>>e;
        if(s==0){cout<<"ASK SPIKE\n"<<flush;return 0;}
        L++;
        if(e==1)break;
    }
    ll ans=(N-K)%L;
    for(ll i=0;i<ans;i++){
        cout<<"NEXT GABBY\n"<<flush;
        cin>>s>>e;
    }
    cout<<"ASK GABBY\n"<<flush;
    return 0;
}
