#include <bits/stdc++.h>
using namespace std;

struct BoundedKnapsack {

    // 1. Classic Bounded Knapsack DP 
    static int solve(int W,const vector<int>& w,const vector<int>& v,const vector<int>& count){
        vector<int> dp(W+1,0);
        int n = w.size();

        for(int i=0;i<n;i++){
            for(int j=W;j>=0;j--){
                for(int k=1;k<=count[i] && k*w[i]<=j;k++){
                    dp[j] = max(dp[j], dp[j-k*w[i]] + k*v[i]);
                }
            }
        }

        return dp[W];
    }

    // 2. Bounded Knapsack with Binary Optimization 
    static int solveBinary(int W,const vector<int>& w,const vector<int>& v,const vector<int>& count){
        vector<int> dp(W+1,0);
        int n = w.size();

        for(int i=0;i<n;i++){
            int c = count[i];
            int k = 1;
            while(c>0){
                int take = min(k,c);
                int wt = w[i]*take;
                int val = v[i]*take;

                for(int j=W;j>=wt;j--)
                    dp[j] = max(dp[j], dp[j-wt]+val);

                c-=take;
                k*=2;
            }
        }

        return dp[W];
    }

    // 3. Maximum Value with Exact Capacity 
    static int maxExact(int W,const vector<int>& w,const vector<int>& v,const vector<int>& count){
        const int NEG = -1e9;
        vector<int> dp(W+1,NEG);
        dp[0]=0;

        int n=w.size();
        for(int i=0;i<n;i++){
            int c=count[i];
            int k=1;
            while(c>0){
                int take = min(k,c);
                int wt=w[i]*take;
                int val=v[i]*take;

                for(int j=W;j>=wt;j--)
                    dp[j] = max(dp[j], dp[j-wt]+val);

                c-=take;
                k*=2;
            }
        }

        return dp[W]<0?-1:dp[W];
    }

    // 4. Count Number of Ways to Fill Capacity (Bounded) 
    static long long countWays(int W,const vector<int>& w,const vector<int>& count){
        int n=w.size();
        vector<long long> dp(W+1,0);
        dp[0]=1;

        for(int i=0;i<n;i++){
            int c=count[i];
            for(int j=W;j>=0;j--){
                for(int k=1;k<=c && k*w[i]<=j;k++)
                    dp[j]+=dp[j-k*w[i]];
            }
        }

        return dp[W];
    }

    // 5. Generate One Optimal Selection 
    static vector<int> reconstruct(int W,const vector<int>& w,const vector<int>& v,const vector<int>& count){
        int n=w.size();
        vector<vector<int>> dp(n+1,vector<int>(W+1,0));

        for(int i=1;i<=n;i++){
            for(int j=0;j<=W;j++){
                dp[i][j]=dp[i-1][j];
                for(int k=1;k<=count[i-1] && k*w[i-1]<=j;k++)
                    dp[i][j]=max(dp[i][j], dp[i-1][j-k*w[i-1]] + k*v[i-1]);
            }
        }

        vector<int> items(n,0);
        int j=W;
        for(int i=n;i>0;i--){
            int used=0;
            for(int k=0;k<=count[i-1];k++){
                if(k*w[i-1]<=j && dp[i][j]==dp[i-1][j-k*w[i-1]]+k*v[i-1]){
                    used=k;
                    break;
                }
            }
            items[i-1]=used;
            j-=used*w[i-1];
        }

        return items;
    }
};
