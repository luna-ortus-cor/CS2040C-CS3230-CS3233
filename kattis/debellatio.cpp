#include <bits/stdc++.h>
using namespace std;

struct Blossom {
    int n;
    vector<vector<int>> adj;
    vector<int> match, p, base, q;
    vector<bool> used, blossom;

    Blossom(int n) : n(n), adj(n), match(n, -1), p(n), base(n), used(n), blossom(n) {}

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    int lca(int a, int b) {
        vector<bool> seen(n, false);
        while (true) {
            a = base[a]; seen[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (seen[b]) return b;
            b = p[match[b]];
        }
    }

    void mark_path(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    int find_path(int root) {
        fill(used.begin(), used.end(), false);
        fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;
        used[root] = true;
        q = {root};
        int head = 0;
        while(head < q.size()){
            int v = q[head++];
            for (int to : adj[v]) {
                if (base[v] == base[to] || match[v] == to) continue;
                if (to == root || (match[to] != -1 && p[match[to]] != -1)) {
                    int cur_base = lca(v, to);
                    fill(blossom.begin(), blossom.end(), false);
                    mark_path(v, cur_base, to);
                    mark_path(to, cur_base, v);
                    for (int i = 0; i < n; i++) {
                        if (blossom[base[i]]) {
                            base[i] = cur_base;
                            if (!used[i]) { used[i] = true; q.push_back(i); }
                        }
                    }
                } else if (p[to] == -1) {
                    p[to] = v;
                    if (match[to] == -1) return to;
                    to = match[to];
                    used[to] = true; q.push_back(to);
                }
            }
        }
        return -1;
    }

    int max_matching() {
        // Randomized Greedy Pre-processing
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 0);
        
        // Randomize the order of vertices to process
        static mt19937 rng(time(0));
        shuffle(nodes.begin(), nodes.end(), rng);
    
        for (int u : nodes) {
            if (match[u] == -1) {
                // Optional: Shuffle adjacency list for even more randomness
                // shuffle(adj[u].begin(), adj[u].end(), rng);
                for (int v : adj[u]) {
                    if (match[v] == -1) {
                        match[u] = v;
                        match[v] = u;
                        break; 
                    }
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                int v = find_path(i);
                while (v != -1) {
                    int pv = p[v], ppv = match[pv];
                    match[v] = pv; match[pv] = v;
                    v = ppv;
                }
            }
        }
        for (int i = 0; i < n; i++) if (match[i] != -1) result++;
        return result / 2;
    }

    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> pairs;
        for (int i = 0; i < n; i++) {
            // match[i] > i ensures we only count each edge once
            if (match[i] != -1 && match[i] > i) {
                pairs.push_back({i, match[i]});
            }
        }
        return pairs;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    Blossom blossom(n);
    while(m--){
        int u,v;
        cin>>u>>v;
        blossom.add_edge(u-1,v-1);
    }
    int num_matches=blossom.max_matching();
    if (num_matches*2==n){
        cout<<2<<endl<<flush;
    }else{
        cout<<1<<endl<<flush;
        for(int i=0;i<n;i++){
            if (blossom.match[i]==-1){
                cout<<i+1<<endl<<flush;
                break;
            }
        }
    }
    while(true){
        int opp;
        cin>>opp;
        if(opp==0)break;
        opp--;
        cout<<blossom.match[opp]+1<<endl<<flush;
    }
    return 0;
}
