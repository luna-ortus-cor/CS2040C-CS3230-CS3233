#include <bits/stdc++.h>
using namespace std;

template<int MAXN>
struct SubsetPartitionSolver {
    int n;
    vector<int> dp;
    vector<int> parent;
    vector<int> valid_masks;

    SubsetPartitionSolver(int n) : n(n) {
        dp.assign(1 << n, 1e9);
        parent.assign(1 << n, 0);
    }

    // Step 1: Pre-calculate all bitmasks that satisfy your specific constraints
    void find_valid_subsets(const function<bool(int)>& is_valid) {
        valid_masks.clear();
        for (int mask = 1; mask < (1 << n); mask++) {
            if (is_valid(mask)) {
                valid_masks.push_back(mask);
            }
        }
    }

    // Step 2: Solve using the "First-Free-Bit" optimized DP
    int solve() {
        dp[0] = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == 1e9) continue;

            // Optimization: Find the first person not yet covered
            int first_free = 0;
            while (first_free < n && (mask >> first_free) & 1) first_free++;
            if (first_free == n) break;

            for (int sub : valid_masks) {
                // To avoid O(3^N), we only attempt subsets that 
                // fix the 'first_free' hole we found.
                if (!(sub & (1 << first_free))) continue;
                if (mask & sub) continue; // Must be disjoint

                int next_mask = mask | sub;
                if (dp[next_mask] > dp[mask] + 1) {
                    dp[next_mask] = dp[mask] + 1;
                    parent[next_mask] = sub;
                }
            }
        }
        return dp[(1 << n) - 1];
    }

    // Step 3: Backtrack to get the actual groups
    vector<vector<int>> get_groups() {
        vector<vector<int>> groups;
        int curr = (1 << n) - 1;
        while (curr > 0) {
            int sub = parent[curr];
            vector<int> group;
            for (int i = 0; i < n; i++) {
                if ((sub >> i) & 1) group.push_back(i);
            }
            groups.push_back(group);
            curr ^= sub;
        }
        return groups;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,k,c;
    cin>>n>>k>>c;
    SubsetPartitionSolver<20> solver(n);
    unordered_map<string,int> um;
    vector<string> v;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        um[s]=i;
        v.push_back(s);
    }
    vector<int> adj(n,0);
    for(int i=0;i<k;i++){
        string s1,s2;
        cin>>s1>>s2;
        adj[um[s1]]|=(1<<um[s2]);
        adj[um[s2]]|=(1<<um[s1]);
        cin.ignore();
    }
    solver.find_valid_subsets([&](int mask) {
        if (__builtin_popcount(mask) > c) return false;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                if (adj[i] & mask) return false; // Conflict edge
            }
        }
        return true;
    });
    solver.solve();
    auto ans=solver.get_groups();
    cout<<ans.size()<<"\n";
    for(auto g:ans){
        for(auto e:g){
            cout<<v[e]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
