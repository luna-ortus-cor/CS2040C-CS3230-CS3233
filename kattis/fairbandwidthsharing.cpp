#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld check(ld T, int n, const vector<ld>& L, const vector<ld>& U, const vector<ld>& W) {
    ld sum=0.0;
    for(int i=0;i<n;i++){
        ld val=W[i]*T;
        if(val<L[i])val=L[i];
        if(val>U[i])val=U[i];
        sum+=val;
    }
    return sum;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ld t;
    cin>>n>>t;
    vector<ld> L(n),U(n),W(n);
    for(int i=0;i<n;i++)cin>>L[i]>>U[i]>>W[i];
    ld lo=0.0,hi=1e13; 
    for(int i=0;i<90;i++){
        ld mid=(lo+hi)/2.0;
        ld val=check(mid, n, L, U, W);
        if(abs(val-t)<1e-9)break;
        if(val<t)lo=mid;
        else hi=mid;
    }
    cout<<fixed<<setprecision(10);
    for(int i=0;i<n;i++) {
        ld xi=W[i]*lo;
        if(xi<L[i])xi=L[i];
        if(xi>U[i])xi=U[i];
        cout<<(double)xi<<"\n";
    }
    return 0;
}
