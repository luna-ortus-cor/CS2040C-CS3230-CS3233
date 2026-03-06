#include <bits/stdc++.h>
using namespace std;

struct GridDP {

    // 1. Minimum Path Sum (2 directions: Right, Down) 
    static int minPath(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (i == 0 && j == 0) continue;
                int from_top = (i > 0) ? grid[i-1][j] : 1e9;
                int from_left = (j > 0) ? grid[i][j-1] : 1e9;
                grid[i][j] += min(from_top, from_left);
            }
        }
        return grid[r-1][c-1];
    }

    // 2. Maximum Path Sum (2 directions: Right, Down) 
    static int maxPath(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (i == 0 && j == 0) continue;
                int from_top = (i > 0) ? grid[i-1][j] : INT_MIN;
                int from_left = (j > 0) ? grid[i][j-1] : INT_MIN;
                grid[i][j] += max(from_top, from_left);
            }
        }
        return grid[r-1][c-1];
    }

    // 3. Unique Paths Count (Right, Down, no obstacles) 
    static int uniquePaths(int r, int c) {
        vector<vector<int>> dp(r, vector<int>(c, 1));
        for(int i=1;i<r;i++)
            for(int j=1;j<c;j++)
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        return dp[r-1][c-1];
    }

    // 4. Unique Paths with Obstacles 
    static int uniquePathsObstacles(vector<vector<int>>& grid) {
        int r=grid.size(), c=grid[0].size();
        vector<vector<int>> dp(r, vector<int>(c,0));
        if(grid[0][0]==0) dp[0][0]=1;

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(grid[i][j]==1) { dp[i][j]=0; continue; }
                if(i>0) dp[i][j]+=dp[i-1][j];
                if(j>0) dp[i][j]+=dp[i][j-1];
            }
        }
        return dp[r-1][c-1];
    }

    // 5. Max Square of 1s (Right, Down, Diagonal) 
    static int maxSquare(vector<vector<int>>& mat){
        int r=mat.size(), c=mat[0].size();
        vector<vector<int>> dp=r>0? vector<vector<int>>(r, vector<int>(c,0)) : vector<vector<int>>{};
        int ans=0;

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(mat[i][j]==1){
                    if(i>0 && j>0)
                        dp[i][j]=1+min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                    else
                        dp[i][j]=1;
                    ans=max(ans, dp[i][j]);
                }
            }
        }
        return ans;
    }

    // 6. Max Rectangle of 1s 
    // Treat each row as histogram, then use largest rectangle in histogram
    static int maxRectangle(vector<vector<int>>& mat){
        int r=mat.size(), c=mat[0].size();
        if(r==0) return 0;
        vector<int> height(c,0);
        int maxArea=0;

        auto largestRectangle = [](vector<int>& h){
            int n=h.size();
            stack<int> st;
            int area=0;
            for(int i=0;i<=n;i++){
                int cur = (i==n?0:h[i]);
                while(!st.empty() && cur<h[st.top()]){
                    int height=h[st.top()]; st.pop();
                    int width=st.empty()?i:i-st.top()-1;
                    area=max(area, height*width);
                }
                st.push(i);
            }
            return area;
        };

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                height[j] = mat[i][j]==0?0:height[j]+1;
            }
            maxArea = max(maxArea, largestRectangle(height));
        }

        return maxArea;
    }

    // 7. Minimum Path Sum (4 directions: Up, Down, Left, Right) 
    static int minPath4Dir(vector<vector<int>>& grid){
        int r=grid.size(), c=grid[0].size();
        vector<vector<int>> dp=grid;
        bool changed=true;

        while(changed){
            changed=false;
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    int best=dp[i][j];
                    if(i>0) best=min(best, dp[i-1][j]+grid[i][j]);
                    if(i<r-1) best=min(best, dp[i+1][j]+grid[i][j]);
                    if(j>0) best=min(best, dp[i][j-1]+grid[i][j]);
                    if(j<c-1) best=min(best, dp[i][j+1]+grid[i][j]);
                    if(best!=dp[i][j]) { dp[i][j]=best; changed=true; }
                }
            }
        }
        return dp[r-1][c-1];
    }

    // 8. Max Path Sum 8 directions 
    static int maxPath8Dir(vector<vector<int>>& grid){
        int r=grid.size(), c=grid[0].size();
        vector<vector<int>> dp=r>0? vector<vector<int>>(r, vector<int>(c,INT_MIN)) : vector<vector<int>>{};
        dp[0][0]=grid[0][0];

        int dr[]={-1,-1,-1,0,0,1,1,1};
        int dc[]={-1,0,1,-1,1,-1,0,1};

        bool changed=true;
        while(changed){
            changed=false;
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++){
                    for(int d=0;d<8;d++){
                        int ni=i+dr[d], nj=j+dc[d];
                        if(ni>=0 && ni<r && nj>=0 && nj<c){
                            if(dp[ni][nj]+grid[i][j]>dp[i][j]){
                                dp[i][j]=dp[ni][nj]+grid[i][j];
                                changed=true;
                            }
                        }
                    }
                }
            }
        }
        return dp[r-1][c-1];
    }

    // 9. Longest Increasing Path (4/8 directions) 
    static int longestIncPath(vector<vector<int>>& grid){
        int r=grid.size(), c=grid[0].size();
        vector<vector<int>> dp(r, vector<int>(c,0));

        function<int(int,int)> dfs=[&](int i,int j){
            if(dp[i][j]>0) return dp[i][j];
            int dr[]={-1,0,1,0,-1,1,-1,1};
            int dc[]={0,-1,0,1,-1,-1,1,1};
            int best=1;
            for(int d=0;d<8;d++){
                int ni=i+dr[d], nj=j+dc[d];
                if(ni>=0 && ni<r && nj>=0 && nj<c && grid[ni][nj]>grid[i][j]){
                    best=max(best,1+dfs(ni,nj));
                }
            }
            return dp[i][j]=best;
        };

        int ans=0;
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                ans=max(ans, dfs(i,j));
        return ans;
    }

    // 10. Number of Paths With Sum (classic 2 directions) 
    static int countPathsWithSum(vector<vector<int>>& grid,int target){
        int r=grid.size(), c=grid[0].size();
        vector<vector<int>> dp(r, vector<int>(c,0));
        dp[0][0]=grid[0][0]==target?1:0;

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(i>0) dp[i][j]+=dp[i-1][j];
                if(j>0) dp[i][j]+=dp[i][j-1];
            }
        }
        return dp[r-1][c-1];
    }

    // 11. Maximum Subrectangle Sum 
    static int maxRectangleSum(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        int maxSum = INT_MIN;

        for(int top=0; top<r; top++){
            vector<int> colSum(c,0);
            for(int bottom=top; bottom<r; bottom++){
                for(int j=0; j<c; j++)
                    colSum[j] += grid[bottom][j];

                // Max subarray on colSum
                int currMax = colSum[0];
                int sumNow = colSum[0];
                for(int j=1;j<c;j++){
                    sumNow = max(colSum[j], sumNow + colSum[j]);
                    currMax = max(currMax, sumNow);
                }
                maxSum = max(maxSum, currMax);
            }
        }

        return maxSum;
    }

    // 12. Maximum Subsquare Sum 
    static int maxSquareSum(vector<vector<int>>& grid) {
        int r = grid.size(), c = grid[0].size();
        vector<vector<int>> prefix(r+1, vector<int>(c+1,0));

        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                prefix[i][j] = grid[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];

        int maxSum = INT_MIN;
        int n = min(r,c);
        for(int len=1;len<=n;len++){
            for(int i=len;i<=r;i++){
                for(int j=len;j<=c;j++){
                    int sum = prefix[i][j] - prefix[i-len][j] - prefix[i][j-len] + prefix[i-len][j-len];
                    maxSum = max(maxSum,sum);
                }
            }
        }
        return maxSum;
    }

    // 13. Minimum Cost Grid DP with Arbitrary Cost Function 
    // cost(i,j,k,l) returns cost to move from (i,j) -> (k,l)
    static int minCostGrid(vector<vector<int>>& grid,
        function<int(int,int,int,int)> cost) {

        int r = grid.size(), c = grid[0].size();
        vector<vector<int>> dp(r, vector<int>(c, INT_MAX));
        dp[0][0] = grid[0][0];

        // Directions: right and down (no cycles)
        int dr[2] = {0, 1};
        int dc[2] = {1, 0};

        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                for(int d=0;d<2;d++){
                    int ni=i+dr[d], nj=j+dc[d];
                    if(ni<r && nj<c){
                        dp[ni][nj] = min(dp[ni][nj], dp[i][j] + cost(i,j,ni,nj));
                    }
                }
            }
        }
        return dp[r-1][c-1];
    }

    // 14. Minimum Cost with 4-direction movement (Dijkstra) 
    static int minCost4Dir(vector<vector<int>>& grid,
        function<int(int,int,int,int)> cost) {

        int r=grid.size(), c=grid[0].size();
        vector<vector<int>> dp(r, vector<int>(c, INT_MAX));
        dp[0][0]=grid[0][0];

        using pii=pair<int,pair<int,int>>;
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        pq.push({dp[0][0],{0,0}});

        int dr[]={-1,1,0,0};
        int dc[]={0,0,-1,1};

        while(!pq.empty()){
            auto [cur, pos]=pq.top(); pq.pop();
            int i=pos.first, j=pos.second;
            if(cur>dp[i][j]) continue;

            for(int d=0;d<4;d++){
                int ni=i+dr[d], nj=j+dc[d];
                if(ni>=0 && ni<r && nj>=0 && nj<c){
                    int newCost = dp[i][j] + cost(i,j,ni,nj);
                    if(newCost<dp[ni][nj]){
                        dp[ni][nj]=newCost;
                        pq.push({newCost,{ni,nj}});
                    }
                }
            }
        }

        return dp[r-1][c-1];
    }
};
