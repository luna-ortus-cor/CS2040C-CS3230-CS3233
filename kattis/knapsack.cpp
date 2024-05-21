#include <bits/stdc++.h>
using namespace std;
//let m[i,w] be max value attained with i obj and weight up to w
//need m[n,W], recurrence is
//m[0,w]=0
//m[i,w]=m[i-1,w] if wi>w
//m[i,w]=max(m[i-1,w],m[i-1,w-wi]+vi) if wi<=w

int main(){
    int W,n,wt,v;
    while(cin>>W>>n){
        vector<vector<int>>dp(n+1,vector<int>(W+1,0));
        vector<int>wts(n);vector<int>vals(n);
        for(int i=0;i<n;i++){
            cin>>v>>wt;wts[i]=wt;vals[i]=v;
        }
        for(int i=1;i<=n;i++){
            for(int w=1;w<=W;w++){
                //cout<<wts[i-1]<<"\n";
                if(wts[i-1]<=w)dp[i][w]=max(dp[i-1][w],dp[i-1][w-wts[i-1]]+vals[i-1]);
                else dp[i][w]=dp[i-1][w];
            }
        }
        //cout<<dp[n][W]<<"\n";
        int idx=n;
        vector<int>ans;
        while(idx){
            if(dp[idx][W]-dp[idx-1][W-wts[idx-1]]==vals[idx-1]){
                ans.push_back(idx-1);
                W-=wts[idx-1];
            }
            idx--;
        }
        cout<<ans.size()<<"\n";
        for(auto i:ans)cout<<i<<" ";
        cout<<"\n";
    }
}
