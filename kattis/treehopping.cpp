#include<bits/stdc++.h>
using namespace std;

struct StaticLCA {
    vector<int> depth, first, euler, lg;
    vector<vector<int>> st;
    int n;

    StaticLCA(const vector<vector<int>> &adj, int root = 1) {
        n = adj.size();
        depth.resize(n);
        first.resize(n);
        euler.reserve(n * 2);
        dfs(adj, root, -1, 0);
        
        int m = euler.size();
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) lg[i] = lg[i / 2] + 1;
        st.assign(m, vector<int>(lg[m] + 1));
        for (int i = 0; i < m; i++) st[i][0] = euler[i];
        for (int j = 1; j <= lg[m]; j++) {
            for (int i = 0; i + (1 << j) <= m; i++) {
                int a = st[i][j - 1], b = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = (depth[a] < depth[b]) ? a : b;
            }
        }
    }

    void dfs(const vector<vector<int>> &adj, int u, int p, int d) {
        depth[u] = d;
        first[u] = euler.size();
        euler.push_back(u);
        for (int v : adj[u]) {
            if (v != p) {
                dfs(adj, v, u, d + 1);
                euler.push_back(u);
            }
        }
    }

    int get_lca(int u, int v) {
        int L = first[u], R = first[v];
        if (L > R) swap(L, R);
        int j = lg[R - L + 1];
        int a = st[L][j], b = st[R - (1 << j) + 1][j];
        return (depth[a] < depth[b]) ? a : b;
    }

    int get_dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector<vector<int>> adj(n+1);
        for(int i=0;i<n-1;i++){
            int a,b;
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        StaticLCA tree(adj, 1);
        vector<int> p(n);
        for(int i=0;i<n;i++)cin>>p[i];
        bool valid=true;
        for(int i=0;i<n-1;i++){
            if(tree.get_dist(p[i], p[i+1])>3){
                valid=false;
                break;
            }
        }
        cout<<(valid?1:0)<<"\n";
    }
    return 0;
}
