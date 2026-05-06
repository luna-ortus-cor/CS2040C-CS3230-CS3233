#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int m,n;
        cin>>m>>n;
        vector<array<int,4>> ans;
        for(int r=m+1;r<=n;r++){
            for(int c=1;c+1<=2*r-1;c+=2){
                ans.push_back({r,c,r,c+1});
            }
        }
        cout<<ans.size()<<"\n";
        for(auto &x:ans){
            for(auto e:x)cout<<e<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
