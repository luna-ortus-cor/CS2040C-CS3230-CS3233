#include <bits/stdc++.h>
using namespace std;

struct SATSolver {
    int num_vars;
    vector<vector<int>> clauses;
    vector<int> assignment; // 0: unassigned, 1: true, -1: false
    vector<vector<int>> all_solutions;

    SATSolver(int vars) : num_vars(vars), assignment(vars + 1, 0) {}

    void add_clause(vector<int> clause) {
        clauses.push_back(clause);
    }

    // Evaluates a literal based on current assignment
    int eval_literal(int lit) {
        int var = abs(lit);
        if (assignment[var] == 0) return 0; // Unassigned
        return (lit > 0) ? assignment[var] : -assignment[var];
    }

    // Unit Propagation
    bool unit_propagate() {
        bool changed = true;
        while (changed) {
            changed = false;
            for (const auto& clause : clauses) {
                int unassigned_count = 0, last_lit = 0;
                bool clause_satisfied = false;

                for (int lit : clause) {
                    int val = eval_literal(lit);
                    if (val == 1) { clause_satisfied = true; break; }
                    if (val == 0) { unassigned_count++; last_lit = lit; }
                }

                if (clause_satisfied) continue;
                if (unassigned_count == 0) return false; // Conflict!
                if (unassigned_count == 1) {
                    assignment[abs(last_lit)] = (last_lit > 0 ? 1 : -1);
                    changed = true;
                }
            }
        }
        return true;
    }

    bool dpll(bool find_all) {
        if (!unit_propagate()) return false;

        // Check if all satisfied
        int var_to_assign = -1;
        for (int i = 1; i <= num_vars; i++) {
            if (assignment[i] == 0) {
                var_to_assign = i;
                break;
            }
        }

        if (var_to_assign == -1) {
            // Found a solution!
            if (find_all) {
                all_solutions.push_back(assignment);
                return false; // Continue searching
            }
            return true;
        }

        // Branching
        vector<int> state_backup = assignment;
        
        // Try True
        assignment[var_to_assign] = 1;
        if (dpll(find_all)) return true;
        
        // Backtrack and Try False
        assignment = state_backup;
        assignment[var_to_assign] = -1;
        if (dpll(find_all)) return true;

        return false;
    }

    bool is_satisfiable() {
        fill(assignment.begin(), assignment.end(), 0);
        return dpll(false);
    }

    vector<int> get_assignment() {
        return assignment;
    }

    vector<vector<int>> get_all_assignments() {
        all_solutions.clear();
        fill(assignment.begin(), assignment.end(), 0);
        dpll(true);
        return all_solutions;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n>>m;
        cin.ignore();
        SATSolver solver(n);
        for(int i=0;i<m;i++){
            vector<int> clause;
            string line;
            getline(cin,line);
            stringstream ss(line);
            string literal;
            while(ss>>literal){
                if(literal=="v")continue;
                if(literal[0]=='X'){
                    clause.push_back(stoi(literal.substr(1)));
                }else{
                    clause.push_back(-stoi(literal.substr(2)));
                }
            }
            solver.add_clause(clause);
        }
        cout<<(solver.is_satisfiable()?"satisfiable":"unsatisfiable")<<"\n";
    }
    return 0;
}
