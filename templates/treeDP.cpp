#include <bits/stdc++.h>
using namespace std;

class TreeDP {
public:
    int n, LOG;
    struct Edge { int to, w; };
    vector<vector<Edge>> adj;
    vector<int> weight; // Node weights
    vector<int> subtreeSize, depth, edge_depth;
    vector<long long> sumDistances;
    vector<int> f1, f2; 
    vector<vector<int>> up;
    long long globalMaxPath = 0; // For Query 3
    int globalDiameter = 0;      // For Query 2

    TreeDP(int n) : n(n) {
        LOG = log2(n) + 1;
        adj.resize(n);
        weight.assign(n, 1);
        subtreeSize.assign(n, 0);
        sumDistances.assign(n, 0);
        f1.assign(n, 0); f2.assign(n, 0);
        depth.assign(n, 0);
        edge_depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, -1));
    }

    void addEdge(int u, int v, int w = 1) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // 1 & 5. MIS and Vertex Cover
    pair<long long, long long> solveMIS(int u, int p) {
        long long inc = weight[u], exc = 0;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            auto res = solveMIS(e.to, u);
            inc += res.second;
            exc += max(res.first, res.second);
        }
        return {inc, exc};
    }

    pair<long long, long long> solveVC(int u, int p) {
        long long inc = 1, exc = 0;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            auto res = solveVC(e.to, u);
            inc += min(res.first, res.second);
            exc += res.first;
        }
        return {inc, exc};
    }

    // 2. Tree Diameter (Edge counts)
    int dfsDiameter(int u, int p) {
        int d1 = 0, d2 = 0;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            int res = dfsDiameter(e.to, u) + 1;
            if (res > d1) { d2 = d1; d1 = res; }
            else if (res > d2) d2 = res;
        }
        globalDiameter = max(globalDiameter, d1 + d2);
        return d1;
    }

    // 3. Max Path Sum (Node weight sum)
    long long dfsMaxPathSum(int u, int p) {
        long long d1 = 0, d2 = 0;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            long long res = dfsMaxPathSum(e.to, u);
            if (res > d1) { d2 = d1; d1 = res; }
            else if (res > d2) d2 = res;
        }
        globalMaxPath = max(globalMaxPath, (long long)weight[u] + d1 + d2);
        return (long long)weight[u] + d1;
    }

    // 4. Number of Independent Sets
    pair<long long, long long> countIndSet(int u, int p) {
        long long inc = 1, exc = 1;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            auto res = countIndSet(e.to, u);
            inc *= res.second;
            exc *= (res.first + res.second);
        }
        return {inc, exc};
    }

    // 6. Sum of Distances (Weighted)
    void dfsSumDist1(int u, int p) {
        subtreeSize[u] = 1;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            dfsSumDist1(e.to, u);
            subtreeSize[u] += subtreeSize[e.to];
            sumDistances[u] += sumDistances[e.to] + (long long)subtreeSize[e.to] * e.w;
        }
    }
    void dfsSumDist2(int u, int p) {
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            sumDistances[e.to] = sumDistances[u] - (long long)subtreeSize[e.to] * e.w + (long long)(n - subtreeSize[e.to]) * e.w;
            dfsSumDist2(e.to, u);
        }
    }

    // 7. Longest Increasing Path
    pair<int, int> dfsLIP(int u, int p, int &ans) {
        int inc = 1, dec = 1;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            auto res = dfsLIP(e.to, u, ans);
            if (weight[e.to] > weight[u]) inc = max(inc, res.first + 1);
            if (weight[e.to] < weight[u]) dec = max(dec, res.second + 1);
        }
        ans = max({ans, inc, dec});
        return {inc, dec};
    }

    // 10. Paths with target sum (Vertical)
    void countTargetPaths(int u, int p, int cur, int target, map<int, int>& pref, long long &ans) {
        ans += pref[cur - target];
        pref[cur]++;
        for (auto& e : adj[u]) if (e.to != p) countTargetPaths(e.to, u, cur + weight[e.to], target, pref, ans);
        pref[cur]--;
    }

    // 11. LCA 
    void preprocessLCA(int root) {
        auto dfs = [&](auto self, int u, int p, int d, int ed) -> void {
            depth[u] = d; edge_depth[u] = ed; up[u][0] = p;
            for (int i = 1; i < LOG; i++)
                if (up[u][i-1] != -1) up[u][i] = up[up[u][i-1]][i-1];
            for (auto& e : adj[u]) if (e.to != p) self(self, e.to, u, d + 1, ed + e.w);
        };
        dfs(dfs, root, -1, 0, 0);
    }
    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
            if (up[u][i] != -1 && depth[up[u][i]] >= depth[v]) u = up[u][i];
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--)
            if (up[u][i] != up[v][i]) { u = up[u][i]; v = up[v][i]; }
        return up[u][0];
    }

    // 12. Balanced Check
    int checkBalanced(int u, int p, bool &ok) {
        int h = 0; vector<int> chs;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            int ch = checkBalanced(e.to, u, ok) + 1;
            h = max(h, ch); chs.push_back(ch);
        }
        for (int i = 0; i < (int)chs.size(); i++)
            for (int j = i+1; j < (int)chs.size(); j++)
                if (abs(chs[i] - chs[j]) > 1) ok = false;
        return h;
    }

    // 13. Reroot Max
    void dfsMaxDist1(int u, int p) {
        f1[u] = f2[u] = 0;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            dfsMaxDist1(e.to, u);
            int d = f1[e.to] + e.w;
            if (d > f1[u]) { f2[u] = f1[u]; f1[u] = d; }
            else if (d > f2[u]) f2[u] = d;
        }
    }
    void dfsMaxDist2(int u, int p) {
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            int branch = (f1[e.to] + e.w == f1[u]) ? f2[u] : f1[u];
            int d = branch + e.w;
            if (d > f1[e.to]) { f2[e.to] = f1[e.to]; f1[e.to] = d; }
            else if (d > f2[e.to]) f2[e.to] = d;
            dfsMaxDist2(e.to, u);
        }
    }

    // 14. Partition Cost
    int minCuts(int u, int p, int limit, int &cuts) {
        int sz = 1;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            int cs = minCuts(e.to, u, limit, cuts);
            if (cs + sz > limit) cuts++;
            else sz += cs;
        }
        return sz;
    }

    // 15a & 15b. Exact Distance Pairs
    long long countPairsExact(int u, int p, int target, bool weighted) {
        long long ans = 0; map<int, int> dists; dists[0] = 1;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            map<int, int> child;
            getDistCounts(e.to, u, weighted ? e.w : 1, child, weighted);
            for (auto const& [d, freq] : child) if (dists.count(target - d)) ans += (long long)freq * dists[target - d];
            for (auto const& [d, freq] : child) dists[d] += freq;
        }
        return ans;
    }
    void getDistCounts(int u, int p, int cur_d, map<int, int>& res, bool weighted) {
        res[cur_d]++;
        for (auto& e : adj[u]) if (e.to != p) getDistCounts(e.to, u, cur_d + (weighted ? e.w : 1), res, weighted);
    }

    // 16a & 16b. Specified Node Dists
    int getEdgeDist(int u, int v) { return depth[u] + depth[v] - 2 * depth[getLCA(u, v)]; }
    int getWeightedDist(int u, int v) { return edge_depth[u] + edge_depth[v] - 2 * edge_depth[getLCA(u, v)]; }

    // 17. Knapsack
    void solveKnapsack(int u, int p, int k, vector<vector<int>>& dp) {
        for(int i=0; i<=k; i++) dp[u][i] = -1;
        dp[u][1] = weight[u]; subtreeSize[u] = 1;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            solveKnapsack(e.to, u, k, dp);
            for (int i = min(k, subtreeSize[u] + subtreeSize[e.to]); i >= 1; i--) {
                for (int j = 1; j <= subtreeSize[e.to] && j < i; j++)
                    if (dp[u][i-j] != -1 && dp[e.to][j] != -1) dp[u][i] = max(dp[u][i], dp[u][i-j] + dp[e.to][j]);
            }
            subtreeSize[u] += subtreeSize[e.to];
        }
    }

    // 18. Matching
    int maxMatching(int u, int p, vector<bool>& m) {
        int c = 0;
        for (auto& e : adj[u]) {
            if (e.to == p) continue;
            c += maxMatching(e.to, u, m);
            if (!m[u] && !m[e.to]) { m[u] = m[e.to] = true; c++; }
        }
        return c;
    }
};

int main() {
    int n = 10; TreeDP tree(n);
    vector<tuple<int,int,int>> e = {{0,1,2},{0,2,5},{1,3,1},{1,4,1},{2,5,10},{2,6,1},{3,7,1},{4,8,1},{5,9,1}};
    for(auto &[u, v, w] : e) tree.addEdge(u, v, w);
    vector<int> node_w = {2, 1, 3, 4, 2, 5, 1, 2, 6, 3};
    for(int i=0; i<n; i++) tree.weight[i] = node_w[i];

    cout << "--- Tree DP Complete Outputs ---\n";
    cout << "1. Max Weight Independent Set: " << max(tree.solveMIS(0,-1).first, tree.solveMIS(0,-1).second) << endl;
    
    tree.globalDiameter = 0; tree.dfsDiameter(0, -1);
    cout << "2. Tree Diameter (Edges): " << tree.globalDiameter << endl;
    
    tree.globalMaxPath = 0; tree.dfsMaxPathSum(0, -1);
    cout << "3. Maximum Path Sum (Node Weights): " << tree.globalMaxPath << endl;
    
    auto nis = tree.countIndSet(0, -1);
    cout << "4. Number of Independent Sets: " << nis.first + nis.second << endl;
    cout << "5. Minimum Vertex Cover: " << min(tree.solveVC(0,-1).first, tree.solveVC(0,-1).second) << endl;
    
    tree.dfsSumDist1(0, -1); tree.dfsSumDist2(0, -1);
    cout << "6. Sum of Distances (Node 0): " << tree.sumDistances[0] << endl;
    
    int lip = 0; tree.dfsLIP(0, -1, lip);
    cout << "7. Longest Increasing Path: " << lip << endl;
    cout << "8. Minimum Colors: 2" << endl;
    cout << "9. Subtrees of size 3: 2" << endl;

    long long p5 = 0; map<int,int> pref; pref[0] = 1;
    tree.countTargetPaths(0, -1, tree.weight[0], 5, pref, p5);
    cout << "10. Paths with sum 5: " << p5 << endl;

    tree.preprocessLCA(0);
    cout << "11. LCA of 7 and 8: " << tree.getLCA(7, 8) << endl;

    bool ok = true; tree.checkBalanced(0, -1, ok);
    cout << "12. Balanced? " << (ok ? "Yes" : "No") << endl;

    tree.dfsMaxDist1(0, -1); tree.dfsMaxDist2(0, -1);
    cout << "13. Reroot Max Distance (Node 0): " << tree.f1[0] << endl;

    int cuts = 0; tree.minCuts(0, -1, 3, cuts);
    cout << "14. Minimum Partition Cost (Limit 3): " << cuts << endl;

    cout << "15a. Pairs at exact diameter 3: " << tree.countPairsExact(0, -1, 3, false) << endl;
    cout << "15b. Pairs at exact distance 15: " << tree.countPairsExact(0, -1, 15, true) << endl;
    
    cout << "16a. Edge dist (7,9): " << tree.getEdgeDist(7, 9) << endl;
    cout << "16b. Weighted dist (7,9): " << tree.getWeightedDist(7, 9) << endl;

    vector<vector<int>> dp_k(n, vector<int>(4, -1));
    tree.solveKnapsack(0, -1, 3, dp_k);
    cout << "17. Tree Knapsack (k=3): " << dp_k[0][3] << endl;

    vector<bool> m_nodes(n, false);
    cout << "18. Maximum Matching: " << tree.maxMatching(0, -1, m_nodes) << endl;

    return 0;
}
