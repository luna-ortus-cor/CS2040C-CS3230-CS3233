#include <bits/stdc++.h>
using namespace std;

struct Knapsack01 {

    // 1. 0/1 Knapsack (max value)
    static long long solve(int W, const vector<int>& w, const vector<int>& v) {
        vector<long long> dp(W + 1, 0);

        for (int i = 0; i < w.size(); i++)
            for (int j = W; j >= w[i]; j--)
                dp[j] = max(dp[j], dp[j - w[i]] + v[i]);

        return dp[W];
    }

    // 2. Subset Sum (decision)
    static bool subsetSum(int sum, const vector<int>& a) {
        vector<bool> dp(sum + 1, false);
        dp[0] = true;

        for (int x : a)
            for (int j = sum; j >= x; j--)
                dp[j] = dp[j] || dp[j - x];

        return dp[sum];
    }

    // 3. Count Subsets With Given Sum 
    static long long countSubsetSum(int sum, const vector<int>& a) {
        vector<long long> dp(sum + 1, 0);
        dp[0] = 1;

        for (int x : a)
            for (int j = sum; j >= x; j--)
                dp[j] += dp[j - x];

        return dp[sum];
    }

    // 4. Equal Partition 
    static bool canPartition(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        if (total % 2) return false;
        return subsetSum(total / 2, a);
    }

    // 5. Minimum Subset Sum Difference 
    static int minSubsetDifference(const vector<int>& a) {
        int total = accumulate(a.begin(), a.end(), 0);
        int n = a.size();

        vector<bool> dp(total + 1, false);
        dp[0] = true;

        for (int x : a)
            for (int j = total; j >= x; j--)
                dp[j] = dp[j] || dp[j - x];

        int ans = INT_MAX;

        for (int s = 0; s <= total / 2; s++)
            if (dp[s])
                ans = min(ans, total - 2 * s);

        return ans;
    }

    // 6. Target Sum
    static int targetSumWays(const vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if ((sum + target) % 2 || abs(target) > sum)
            return 0;

        int S = (sum + target) / 2;

        vector<int> dp(S + 1, 0);
        dp[0] = 1;

        for (int x : nums)
            for (int j = S; j >= x; j--)
                dp[j] += dp[j - x];

        return dp[S];
    }

    // 7. Minimum Number of Elements to Reach Sum 
    static int minItemsForSum(int sum, const vector<int>& a) {
        const int INF = 1e9;
        vector<int> dp(sum + 1, INF);
        dp[0] = 0;

        for (int x : a)
            for (int j = sum; j >= x; j--)
                dp[j] = min(dp[j], dp[j - x] + 1);

        return dp[sum] == INF ? -1 : dp[sum];
    }

    // 8. Count Partitions With Given Difference 
    static int countPartitionsDiff(const vector<int>& a, int diff) {
        int sum = accumulate(a.begin(), a.end(), 0);

        if ((sum + diff) % 2) return 0;

        int target = (sum + diff) / 2;

        vector<int> dp(target + 1, 0);
        dp[0] = 1;

        for (int x : a)
            for (int j = target; j >= x; j--)
                dp[j] += dp[j - x];

        return dp[target];
    }

    // 9. List All Possible Subset Sums 
    static vector<int> allSubsetSums(const vector<int>& a) {
        int sum = accumulate(a.begin(), a.end(), 0);

        vector<bool> dp(sum + 1, false);
        dp[0] = true;

        for (int x : a)
            for (int j = sum; j >= x; j--)
                dp[j] = dp[j] || dp[j - x];

        vector<int> res;

        for (int i = 0; i <= sum; i++)
            if (dp[i]) res.push_back(i);

        return res;
    }

    // 10. Recover One Optimal Knapsack Selection 
    static vector<int> recoverItems(int W,
        const vector<int>& w,
        const vector<int>& v) {

        int n = w.size();
        vector<vector<int>> dp(n+1, vector<int>(W+1,0));

        for(int i=1;i<=n;i++)
            for(int j=0;j<=W;j++){
                dp[i][j]=dp[i-1][j];
                if(j>=w[i-1])
                    dp[i][j]=max(dp[i][j],
                        dp[i-1][j-w[i-1]]+v[i-1]);
            }

        vector<int> items;

        int j=W;
        for(int i=n;i>0;i--)
            if(dp[i][j]!=dp[i-1][j]){
                items.push_back(i-1);
                j-=w[i-1];
            }

        reverse(items.begin(),items.end());
        return items;
    }
};

// General idea

// Maximize value
dp[j] = max(dp[j], dp[j-w] + value);

// Feasibility
dp[j] |= dp[j-w];

// Count
dp[j] += dp[j-w];

// Minimize cost
dp[j] = min(dp[j], dp[j-w] + 1);
