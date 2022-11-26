#include <iostream>
#include <cmath>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
#define inf 10001

int main(){
    int tc;
    cin >> tc;
    for(int i=0;i<tc;i++){
        int price;
        cin>>price;
        int n;
        cin>>n;
        vector<int> denom;
        vector<int> nums(100000,0);
        int dp[10001];
        for(int i=0;i<inf;i++){
            dp[i]=inf;
        }
        dp[0]=0;
        int temp;
        for(int j=0;j<n;j++){
            cin>>temp;
            denom.push_back(temp);
        }
        sort(denom.begin(),denom.end(),greater<int>());
        int value=inf;
        for(int c:denom){
            for(int v=value-c-1;v>=0;v--){
                dp[v+c]=min(dp[v+c],dp[v]+1);
                //cout<<v+c<<" "<<dp[v+c]<<endl;
            }
        }
        for(int i=price;i<inf;i++){
            //cout<<i<<dp[1500]<<endl;
            if(dp[i]!=inf){
                cout<<i<<" "<<dp[i]<<endl;
                break;
            }
        }
    }
}
