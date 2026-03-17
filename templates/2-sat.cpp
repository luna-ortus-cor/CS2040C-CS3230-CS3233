#include <bits/stdc++.h>
using namespace std;

struct TwoSATSolver {
    int n;
    vector<vector<int>> adj;
    vector<int> disc, low, scc;
    vector<bool> on_stack;
    stack<int> st;
    int timer, scc_cnt;
    bool computed = false;
    bool satisfiable = false;

    // Node mapping: 2*i = True literal, 2*i + 1 = False literal
    TwoSATSolver(int n) : n(n), adj(2 * n), disc(2 * n, 0), low(2 * n, 0), 
                          scc(2 * n, 0), on_stack(2 * n, false) {}

    void add_clause(int u_lit, int v_lit) {
        auto get_id = [&](int lit) {
            return (lit > 0) ? 2 * (lit - 1) : 2 * (abs(lit) - 1) + 1;
        };
        int u = get_id(u_lit), v = get_id(v_lit);
        // (u or v) is equivalent to (~u -> v) and (~v -> u)
        adj[u ^ 1].push_back(v);
        adj[v ^ 1].push_back(u);
        computed = false; // Reset if new edges are added
    }

    void tarjan(int u) {
        disc[u] = low[u] = ++timer;
        st.push(u);
        on_stack[u] = true;
        for (int v : adj[u]) {
            if (!disc[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
        if (low[u] == disc[u]) {
            scc_cnt++;
            while (true) {
                int v = st.top(); st.pop();
                on_stack[v] = false;
                scc[v] = scc_cnt;
                if (u == v) break;
            }
        }
    }

    // solve() is void: it performs the SCC computation
    void solve() {
        fill(disc.begin(), disc.end(), 0);
        fill(low.begin(), low.end(), 0);
        fill(scc.begin(), scc.end(), 0);
        timer = scc_cnt = 0;
        for (int i = 0; i < 2 * n; i++) if (!disc[i]) tarjan(i);
        
        satisfiable = true;
        for (int i = 0; i < n; i++) {
            if (scc[2 * i] == scc[2 * i + 1]) {
                satisfiable = false;
                break;
            }
        }
        computed = true;
    }

    bool is_satisfiable() {
        if (!computed) solve();
        return satisfiable;
    }

    // Returns a single satisfying assignment
    vector<int> get_one_solution() {
        if (!is_satisfiable()) return {};
        vector<int> res(n + 1);
        for (int i = 0; i < n; i++) {
            // Tarjan's returns SCCs in reverse topological order.
            // We pick the literal that appears later (smaller SCC index).
            res[i + 1] = (scc[2 * i] < scc[2 * i + 1]);
        }
        return res;
    }

    // --- All Solutions Logic (Backtracking) ---
    void backtrack_all(int var_idx, vector<int>& current, vector<vector<int>>& all) {
        if (var_idx == n + 1) {
            all.push_back(current);
            return;
        }
        // Try both True (1) and False (0)
        for (int val : {1, 0}) {
            current[var_idx] = val;
            if (is_consistent(var_idx, current)) {
                backtrack_all(var_idx + 1, current, all);
            }
        }
    }

    bool is_consistent(int var_idx, const vector<int>& current) {
        // Check if the current assignment violates any implication edges
        for (int i = 1; i <= var_idx; i++) {
            int u_node = 2 * (i - 1) + (current[i] ? 0 : 1);
            for (int v_node : adj[u_node]) {
                int v_var = (v_node / 2) + 1;
                int v_val = (v_node % 2 == 0);
                if (v_var <= var_idx && current[v_var] != v_val) return false;
            }
        }
        return true;
    }

    vector<vector<int>> get_all_solutions() {
        if (!is_satisfiable()) return {};
        vector<vector<int>> all;
        vector<int> current(n + 1);
        backtrack_all(1, current, all);
        return all;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    int n,m;
    cin>>s>>s>>n>>m;
    TwoSATSolver solver(n);
    for(int i=0;i<m;i++){
        int a,b,zero;
        cin>>a>>b>>zero;
        solver.add_clause(a,b);
    }
    solver.solve();
    if(solver.is_satisfiable()){
        cout<<"s SATISFIABLE\n";
        vector<int> assignment=solver.get_one_solution();
        cout<<"v ";
        for(int i=1;i<=n;i++){
            if(assignment[i])cout<<i<<" ";
            else cout<<-i<<" ";
        }
        cout<<"0\n";
    }else{
        cout<<"s UNSATISFIABLE\n";
    }
    return 0;
}
