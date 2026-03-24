#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll X,Y,N;
    ld R;
    cin>>X>>Y>>N>>R;
    while(N){
        ld r=(ld)R/(12.0*100.0);
        ll m=(ll)N*12;
        if(r==0){
            if((ld)X<=(ld)Y*m)cout<<"YES\n";
            else cout<<"NO\n";
        }else{
            ld p=pow(1.0+r,m);
            if(X*p-Y*(p-1)/r<+1e-9)cout<<"YES\n";
            else cout<<"NO\n";
        }
        cin>>X>>Y>>N>>R;
    }
    return 0;
}
