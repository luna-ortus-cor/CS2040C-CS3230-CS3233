#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll t;
    cin>>t;
    while(t--){
        ll vals[3];
        int ids[3]={1,2,3};
        cin>>vals[0]>>vals[1]>>vals[2];
        vector<pair<int,int>> ops;
        while(vals[0]>0&&vals[1]>0&&vals[2]>0){
            for(int i=0;i<2;i++){
                for(int j=i+1;j<3;j++){
                    if(vals[i]>vals[j]){
                        swap(vals[i],vals[j]);
                        swap(ids[i],ids[j]);
                    }
                }
            }
            ll q=vals[1]/vals[0];
            for(int i=0;(1LL<<i)<=q;i++){
                if((q>>i)&1){
                    ops.push_back({ids[1],ids[0]});
                    vals[1]-=vals[0];
                    vals[0]*=2;
                }else{
                    ops.push_back({ids[2],ids[0]});
                    vals[2]-=vals[0];
                    vals[0]*=2;
                }
            }
        }
        cout<<ops.size()<<"\n";
        for(auto const& op:ops){
            cout<<op.first<<" "<<op.second<<"\n";
        }
    }
    return 0;
}
