#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

/**
 * Dynamic Hungarian Algorithm
 * Supports: 
 * 1. Adding a row (vertex to the left side) in O(N^2)
 * 2. Updating a weight and re-matching in O(N^2)
 * Designed for Maximum Weight Perfect Matching.
 */
struct DynamicHungarian {
    int n; // Current number of rows/cols
    int max_n; // Maximum capacity
    vector<vector<ll>> cost;
    vector<ll> u, v; // Potentials
    vector<int> p;   // p[j] = row matched with column j
    vector<int> way; // for path reconstruction

    DynamicHungarian(int max_n) : max_n(max_n), n(0) {
        cost.assign(max_n + 1, vector<ll>(max_n + 1, -INF));
        u.assign(max_n + 1, 0);
        v.assign(max_n + 1, 0);
        p.assign(max_n + 1, 0);
        way.assign(max_n + 1, 0);
    }

    // O(N^2) procedure to augment matching for a specific row index r
    void augment(int r) {
        p[0] = r;
        int j0 = 0;
        vector<ll> minv(max_n + 1, INF);
        vector<bool> used(max_n + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= max_n; j++) {
                if (!used[j]) {
                    // Note: we use -cost because the algorithm finds min-cost
                    // while potentials are maintained for max-weight logic
                    ll cur = -cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= max_n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        // Path reconstruction
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    // Adds a row with given weights and updates matching in O(N^2)
    void add_row(const vector<ll>& weights) {
        n++;
        for (int j = 1; j <= (int)weights.size(); j++) {
            cost[n][j] = weights[j - 1];
        }
        augment(n);
    }

    // Updates weight of edge (r, c) and re-augments in O(N^2)
    void update_weight(int r, int c, ll new_w) {
        cost[r][c] = new_w;
        
        // Find which column was matched to row r
        int matched_col = -1;
        for (int j = 1; j <= max_n; j++) {
            if (p[j] == r) {
                matched_col = j;
                break;
            }
        }

        // To re-augment: un-match row r and call augment
        if (matched_col != -1) {
            p[matched_col] = 0;
            augment(r);
        }
    }

    ll get_max_weight() {
        return -v[0];
    }

    vector<pair<int, int>> get_matches() {
        vector<pair<int, int>> matches;
        for (int j = 1; j <= n; j++) {
            if (p[j] != 0) matches.push_back({p[j], j});
        }
        return matches;
    }
};

int main() {
    // 1. Initialize for a potential 4x4 matrix
    DynamicHungarian dh(4);

    // 2. Add first two rows (Partially building the graph)
    dh.add_row({10, 5, 8});  // Row 1
    dh.add_row({2, 11, 3});  // Row 2
    
    cout << "Initial Max Weight (2x3): " << dh.get_max_weight() << endl;

    // 3. Add a third row dynamically - O(N^2)
    dh.add_row({1, 2, 15});  // Row 3
    cout << "Max Weight after adding Row 3: " << dh.get_max_weight() << endl;

    cout << "Matches:" << endl;
    for (auto m : dh.get_matches()) {
        cout << "Row " << m.first << " <-> Col " << m.second << endl;
    }

    // 4. Update an edge weight dynamically - O(N^2)
    // Let's make Row 1 <-> Col 2 extremely valuable
    cout << "\nUpdating Row 1, Col 2 weight to 100..." << endl;
    dh.update_weight(1, 2, 100);

    cout << "New Max Weight: " << dh.get_max_weight() << endl;
    cout << "New Matches:" << endl;
    for (auto m : dh.get_matches()) {
        cout << "Row " << m.first << " <-> Col " << m.second << endl;
    }
    return 0;
}
