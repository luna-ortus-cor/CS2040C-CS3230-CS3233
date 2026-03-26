#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef long long ll;

ld f[1000001];
void precompute(){
    f[0]=0;
    for(int i=1;i<=1000000;i++){
        f[i]=f[i-1]+log10((ld)i);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    precompute();
    int n;
    cin>>n;
    int D=365;
    ll S=0;
    map<int,int> count;
    for(int i=0;i<n;i++){
        int c;
        cin>>c;
        S+=c;
        count[c]++;
    }

    ld res=f[S];
    for(auto const& [val,freq]:count){
        res-=(ld)freq*f[val];
    }

    res+=f[D];
    res-=f[D-n];
    for(auto const& [val,freq]:count){
        res-=f[freq];
    }

    res-=(ld)S*log10((ld)D);

    cout<<fixed<<setprecision(10)<<(double)res<<endl;
    return 0;
}
