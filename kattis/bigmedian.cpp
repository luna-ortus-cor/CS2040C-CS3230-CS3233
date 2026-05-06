#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N,K;
    cin>>N>>K;
    vector<int>a(N);
    for(auto &x:a) cin>>x;
    auto ok=[&](int X){
        vector<int>b(N);
        for(int i=0;i<N;i++)
            b[i]=(a[i]>=X?1:-1);
        if(accumulate(b.begin(),b.end(),0)<K)return false;
        int cnt=0;
        for(int i=0;i<N;){
            int sum=0;
            bool cut=false;
            for(int j=i;j<N;j++){
                sum+=b[j];
                if(((j-i)%2==0) && sum>=1){
                    cnt++;
                    i=j+1;
                    cut=true;
                    break;
                }
            }
            if(!cut) break;
        }
        return cnt>=K;
    };
    int lo=0,hi=1e9,ans=0;
    while(lo<=hi){
        int mid=(lo+hi)/2;
        if(ok(mid)){
            ans=mid;
            lo=mid+1;
        }else hi=mid-1;
    }
    cout<<ans<<"\n";
    return 0;
}
