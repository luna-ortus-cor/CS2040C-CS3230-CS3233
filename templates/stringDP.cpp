#include <bits/stdc++.h>
using namespace std;

struct StringDP {

    // 1. Edit Distance (Levenshtein)
    static int editDistance(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1));

        for(int i=0;i<=n;i++) dp[i][0]=i;
        for(int j=0;j<=m;j++) dp[0][j]=j;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1])
                    dp[i][j]=dp[i-1][j-1];
                else
                    dp[i][j]=1+min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }

        return dp[n][m];
    }

    // 2. Longest Common Subsequence
    static int LCS(string s1, string s2) {
        int n=s1.size(), m=s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1,0));

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1])
                    dp[i][j]=dp[i-1][j-1]+1;
                else
                    dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
            }
        }

        return dp[n][m];
    }

    // 3. Longest Palindromic Subsequence
    static int LPS(string s) {
        string r = s;
        reverse(r.begin(), r.end());
        return LCS(s, r);
    }

    // 4. Distinct Subsequences
    static long long distinctSubseq(string s, string t) {
        int n=s.size(), m=t.size();
        vector<vector<long long>> dp(n+1, vector<long long>(m+1,0));

        for(int i=0;i<=n;i++) dp[i][0]=1;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                dp[i][j]=dp[i-1][j];
                if(s[i-1]==t[j-1])
                    dp[i][j]+=dp[i-1][j-1];
            }
        }

        return dp[n][m];
    }

    // 5. Shortest Common Supersequence length
    static int SCS(string s1, string s2) {
        int l = LCS(s1,s2);
        return s1.size()+s2.size()-l;
    }

    // 6. Longest Common Substring
    static int longestCommonSubstring(string s1, string s2) {
        int n=s1.size(), m=s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1,0));
        int ans=0;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1]){
                    dp[i][j]=dp[i-1][j-1]+1;
                    ans=max(ans,dp[i][j]);
                }
            }
        }

        return ans;
    }

    // 7. Check if s3 is interleaving of s1 and s2
    static bool interleave(string s1,string s2,string s3){
        int n=s1.size(), m=s2.size();
        if(n+m!=s3.size()) return false;

        vector<vector<bool>> dp(n+1, vector<bool>(m+1,false));
        dp[0][0]=true;

        for(int i=0;i<=n;i++){
            for(int j=0;j<=m;j++){
                if(i>0 && s1[i-1]==s3[i+j-1])
                    dp[i][j]|=dp[i-1][j];

                if(j>0 && s2[j-1]==s3[i+j-1])
                    dp[i][j]|=dp[i][j-1];
            }
        }

        return dp[n][m];
    }

    // 8. Shortest Common Supersequence
    static string shortestCommonSupersequence(string a,string b){
        int n=a.size(), m=b.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));

        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i-1]==b[j-1])
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);

        int i=n,j=m;
        string res;

        while(i>0 && j>0){
            if(a[i-1]==b[j-1]){
                res+=a[i-1];
                i--; j--;
            }
            else if(dp[i-1][j]>dp[i][j-1]){
                res+=a[i-1];
                i--;
            } else{
                res+=b[j-1];
                j--;
            }
        }

        while(i>0) res+=a[--i];
        while(j>0) res+=b[--j];

        reverse(res.begin(),res.end());
        return res;
    }

    // 9. Min deletions to make strings equal
    static int minDeleteToEqual(string a,string b){
        int l = LCS(a,b);
        return a.size()+b.size()-2*l;
    }

    // 10. Minimum ASCII Delete Sum
    static int minASCIIDeleteSum(string s1,string s2){
        int n=s1.size(), m=s2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1,0));

        for(int i=n-1;i>=0;i--)
            dp[i][m]=dp[i+1][m]+s1[i];

        for(int j=m-1;j>=0;j--)
            dp[n][j]=dp[n][j+1]+s2[j];

        for(int i=n-1;i>=0;i--)
        for(int j=m-1;j>=0;j--){
            if(s1[i]==s2[j])
                dp[i][j]=dp[i+1][j+1];
            else
                dp[i][j]=min(
                    s1[i]+dp[i+1][j],
                    s2[j]+dp[i][j+1]
                );
        }

        return dp[0][0];
    }

    // 11. Wildcard Matching (* and ?)
    static bool wildcardMatch(string s,string p){
        int n=s.size(), m=p.size();
        vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));

        dp[0][0]=true;

        for(int j=1;j<=m;j++)
            if(p[j-1]=='*')
                dp[0][j]=dp[0][j-1];

        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(p[j-1]=='*')
                dp[i][j]=dp[i][j-1]||dp[i-1][j];
            else if(p[j-1]=='?' || s[i-1]==p[j-1])
                dp[i][j]=dp[i-1][j-1];
        }

        return dp[n][m];
    }

    // 12. Regex Matching (. and *)
    static bool regexMatch(string s,string p){
        int n=s.size(), m=p.size();
        vector<vector<bool>> dp(n+1,vector<bool>(m+1,false));
        dp[0][0]=true;

        for(int j=2;j<=m;j++)
            if(p[j-1]=='*')
                dp[0][j]=dp[0][j-2];

        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(p[j-1]=='.' || p[j-1]==s[i-1])
                dp[i][j]=dp[i-1][j-1];
            else if(p[j-1]=='*'){
                dp[i][j]=dp[i][j-2];
                if(p[j-2]=='.' || p[j-2]==s[i-1])
                    dp[i][j]|=dp[i-1][j];
            }
        }

        return dp[n][m];
    }

    // 13. LCS for 3 strings
    static int LCS3(string a,string b,string c){
        int n=a.size(), m=b.size(), k=c.size();
        vector dp(n+1, vector(m+1, vector<int>(k+1,0)));

        for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        for(int z=1;z<=k;z++)
            if(a[i-1]==b[j-1] && a[i-1]==c[z-1])
                dp[i][j][z]=dp[i-1][j-1][z-1]+1;
            else
                dp[i][j][z]=max({dp[i-1][j][z],dp[i][j-1][z],dp[i][j][z-1]});

        return dp[n][m][k];
    }

    // 14. Insertions and Deletions for 2 strings
    static pair<int,int> minInsertDelete(string s1,string s2){
        int l=LCS(s1,s2);
    
        int deletions = s1.size()-l;
        int insertions = s2.size()-l;
    
        return {insertions,deletions};
    }

    // 15. Longest Repeating Subsequence
    static int longestRepeatingSubseq(string s){
        int n=s.size();
        vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    
        for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(s[i-1]==s[j-1] && i!=j)
                dp[i][j]=dp[i-1][j-1]+1;
            else
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
    
        return dp[n][n];
    }

    // Utility function, compute palindromes
    static vector<vector<bool>> palindromeTable(string s){
        int n=s.size();
        vector<vector<bool>> pal(n,vector<bool>(n,false));
    
        for(int i=n-1;i>=0;i--)
            for(int j=i;j<n;j++)
                if(s[i]==s[j] && (j-i<2 || pal[i+1][j-1]))
                    pal[i][j]=true;
    
        return pal;
    }

    // 16. Get all palindrome partitions
    static vector<vector<string>> palindromePartitions(string s){
        int n=s.size();
        auto pal=palindromeTable(s);
    
        vector<vector<string>> res;
        vector<string> path;
    
        function<void(int)> dfs=[&](int start){
            if(start==n){
                res.push_back(path);
                return;
            }
    
            for(int end=start;end<n;end++){
                if(pal[start][end]){
                    path.push_back(s.substr(start,end-start+1));
                    dfs(end+1);
                    path.pop_back();
                }
            }
        };
    
        dfs(0);
        return res;
    }

    // 17. Minimum number of cuts to partition to palindrome
    static int minPalindromeCuts(string s){
        int n=s.size();
        auto pal=palindromeTable(s);
    
        vector<int> dp(n);
    
        for(int i=0;i<n;i++){
            dp[i]=i;
    
            for(int j=0;j<=i;j++)
                if(pal[j][i])
                    dp[i]= (j==0) ? 0 : min(dp[i],dp[j-1]+1);
        }
    
        return dp[n-1];
    }

    // 18. Word break
    static vector<string> wordBreak(string s, unordered_set<string>& dict){
        int n=s.size();
        unordered_map<int,vector<string>> memo;
    
        function<vector<string>(int)> dfs=[&](int start){
    
            if(memo.count(start))
                return memo[start];
    
            vector<string> res;
    
            if(start==n){
                res.push_back("");
                return res;
            }
    
            for(int end=start+1;end<=n;end++){
                string word=s.substr(start,end-start);
    
                if(dict.count(word)){
                    auto subs=dfs(end);
    
                    for(string sub:subs)
                        res.push_back(word + (sub.empty()?"":" "+sub));
                }
            }
    
            return memo[start]=res;
        };
    
        return dfs(0);
    }
};

// general idea for string dp
for (int i=0;i<=n;i++)
for (int j=0;j<=m;j++) {

    if (i==0 || j==0) continue;

    if (A[i-1]==B[j-1])
        dp[i][j] = dp[i-1][j-1] + MATCH;

    dp[i][j] = combine(
        dp[i][j],
        dp[i-1][j] + COST1,
        dp[i][j-1] + COST2
    );
}

// Alignment/Edit Operations
dp[i][j] = cost to convert s1[0..i-1] → s2[0..j-1]
dp[i][j] = min({
    dp[i-1][j] + delete,
    dp[i][j-1] + insert,
    dp[i-1][j-1] + replace
});

// Match/Skip (Subsequence)
dp[i][j] = answer using s1[0..i-1] and s2[0..j-1]
if (s1[i-1] == s2[j-1])
    dp[i][j] = dp[i-1][j-1] + value;
else
    dp[i][j] = combine(dp[i-1][j], dp[i][j-1]);

// Counting Subsequence
dp[i][j] = number of ways to form t[0..j-1] from s[0..i-1]
dp[i][j] = dp[i-1][j];
if (s[i-1] == t[j-1])
    dp[i][j] += dp[i-1][j-1];

// Contiguous Match (Substring)
dp[i][j] = length of common substring ending at i,j
if (s1[i-1] == s2[j-1])
    dp[i][j] = dp[i-1][j-1] + 1;
else
    dp[i][j] = 0;

// Interleaving/Merge
dp[i][j] = can we form s3[0..i+j-1]
dp[i][j] =
    (dp[i-1][j] && s1[i-1]==s3[i+j-1]) ||
    (dp[i][j-1] && s2[j-1]==s3[i+j-1]);

// Partition
dp[i] = best answer for prefix s[0..i]
for j in [0..i]:
    if substring j..i valid:
        dp[i] = combine(dp[j-1])
