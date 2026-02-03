#include <bits/stdc++.h>
using namespace std;

int N,W,tgt;
//can avoid const ref by initializing vectors here
int solve(int n, int w, const vector<vector<int>>& prices, const vector<vector<int>>& sales, vector<vector<int>>& dp, const vector<int> ksize){
    if(w<0)return 0;
    if(n<0)return 0;
    if(dp[n][w]!=-1)return dp[n][w];
    //dp[n][w]=solve(n,w-1,prices,sales,dp); //cannot set no price
    for(int i=0;i<ksize[W-w];i++){
        int subcase=prices[W-w][i]*(n<sales[W-w][i]?n:sales[W-w][i])+solve(n-sales[W-w][i],w-1,prices,sales,dp,ksize);
        if(w==W && subcase>dp[n][w])tgt=prices[W-w][i];
        if(w==W && subcase==dp[n][w])tgt=min(tgt,prices[W-w][i]);
        dp[n][w]=max(dp[n][w],subcase);
    }
    return dp[n][w];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int K,p,s;
    cin>>N>>W;
    vector<int> ksize;
    vector<vector<int>> prices(W+1,vector<int>());
    vector<vector<int>> sales(W+1,vector<int>());
    vector<vector<int>> dp(N+1,vector<int>(W+1,-1));
    for(int i=0;i<=W;i++){
        cin>>K;
        ksize.push_back(K);
        for(int j=0;j<K;j++){
            cin>>p;
            prices[i].push_back(p);
        }
        for(int j=0;j<K;j++){
            cin>>s;
            sales[i].push_back(s);
        }
    }
    int ans=solve(N,W,prices,sales,dp,ksize);
    cout<<ans<<"\n"<<tgt<<"\n";
    return 0;
}
