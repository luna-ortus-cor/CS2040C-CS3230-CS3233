#include <bits/stdc++.h>
using namespace std;

struct UnboundedKnapsack {

    // 1. Unbounded knapsack
    static int solve(int W, const vector<int>& coins) {
        vector<int> dp(W + 1, 1e9);
        dp[0] = 0;
        for (int c : coins)
            for (int i = c; i <= W; i++)
                dp[i] = min(dp[i], dp[i - c] + 1);
        return dp[W] > W ? -1 : dp[W];
    }

    // 2. Number of ways to make sum 
    static long long countWays(int W, const vector<int>& coins) {
        vector<long long> dp(W+1,0);
        dp[0]=1;

        for(int c:coins)
            for(int i=c;i<=W;i++)
                dp[i]+=dp[i-c];

        return dp[W];
    }

    // 3. Check if sum possible 
    static bool canMakeSum(int W,const vector<int>& a){
        vector<bool> dp(W+1,false);
        dp[0]=true;

        for(int x:a)
            for(int i=x;i<=W;i++)
                dp[i] |= dp[i-x];

        return dp[W];
    }

    // 4. Unbounded knapsack (maximize value) 
    static int maxValue(int W,const vector<int>& w,const vector<int>& v){
        vector<int> dp(W+1,0);

        for(int i=0;i<w.size();i++)
            for(int j=w[i];j<=W;j++)
                dp[j] = max(dp[j], dp[j-w[i]] + v[i]);

        return dp[W];
    }

    // 5. Rod Cutting 
    static int rodCutting(int n,const vector<int>& price){
        vector<int> dp(n+1,0);

        for(int len=1;len<=n;len++)
            for(int cut=1;cut<=len;cut++)
                dp[len] = max(dp[len],
                    price[cut-1] + dp[len-cut]);

        return dp[n];
    }

    // 6. Maximum segments (cut ribbon) 
    static int maxSegments(int n,const vector<int>& cuts){
        const int NEG = -1e9;
        vector<int> dp(n+1,NEG);
        dp[0]=0;

        for(int c:cuts)
            for(int i=c;i<=n;i++)
                dp[i] = max(dp[i], dp[i-c] + 1);

        return dp[n] < 0 ? -1 : dp[n];
    }

    // 7. Perfect Squares
    static int perfectSquares(int n){
        const int INF = 1e9;
        vector<int> dp(n+1,INF);
        dp[0]=0;

        for(int i=1;i*i<=n;i++){
            int sq=i*i;
            for(int j=sq;j<=n;j++)
                dp[j] = min(dp[j], dp[j-sq] + 1);
        }

        return dp[n];
    }

    // 8. Integer Break 
    static int integerBreak(int n){
        vector<int> dp(n+1,0);

        for(int i=1;i<n;i++)
            for(int j=i;j<=n;j++)
                dp[j] = max(dp[j],
                    max(i*(j-i), i*dp[j-i]));

        return dp[n];
    }

    // 9. Minimum cost to reach exactly W 
    static int minCostExactWeight(int W,const vector<int>& cost){
        const int INF = 1e9;
        int n=cost.size();

        vector<int> dp(W+1,INF);
        dp[0]=0;

        for(int i=0;i<n;i++){
            int w=i+1;
            if(cost[i]==-1) continue;

            for(int j=w;j<=W;j++)
                dp[j]=min(dp[j],dp[j-w]+cost[i]);
        }

        return dp[W]==INF?-1:dp[W];
    }

    // 10. Count ordered combinations 
    static long long countPermutations(int target,const vector<int>& nums){
        vector<long long> dp(target+1,0);
        dp[0]=1;

        for(int i=1;i<=target;i++)
            for(int x:nums)
                if(i>=x)
                    dp[i]+=dp[i-x];

        return dp[target];
    }

    // 11. Largest sum not exceeding W 
    static int maxSumLE(int W,const vector<int>& a){
        vector<bool> dp(W+1,false);
        dp[0]=true;

        for(int x:a)
            for(int i=x;i<=W;i++)
                dp[i]|=dp[i-x];

        for(int i=W;i>=0;i--)
            if(dp[i]) return i;

        return 0;
    }

    // 12. Generate one solution for coin change 
    static vector<int> reconstructCoins(int W,const vector<int>& coins){
        const int INF=1e9;
        vector<int> dp(W+1,INF), parent(W+1,-1);

        dp[0]=0;

        for(int c:coins)
            for(int i=c;i<=W;i++)
                if(dp[i] > dp[i-c] + 1){
                    dp[i] = dp[i-c] + 1;
                    parent[i] = c;
                }

        vector<int> res;

        if(dp[W]==INF) return res;

        while(W>0){
            res.push_back(parent[W]);
            W -= parent[W];
        }

        return res;
    }
};

// General idea

// Min items
dp[j] = min(dp[j], dp[j-x] + 1);

// Count combinations
dp[j] += dp[j-x];

// Max value
dp[j] = max(dp[j], dp[j-x] + value);

// Feasibility
dp[j] |= dp[j-x];
