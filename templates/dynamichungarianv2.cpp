#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct RectangularHungarian {
    int num_rows, num_cols;
    vector<vector<ll>> cost;
    vector<ll> u, v; 
    vector<int> p;   // p[j] = row assigned to column j
    vector<int> way; 

    // Initialize with the maximum possible columns you expect
    RectangularHungarian(int max_cols) : num_rows(0), num_cols(max_cols) {
        cost.assign(max_cols + 1, vector<ll>(max_cols + 1, -INF));
        u.assign(max_cols + 1, 0);
        v.assign(max_cols + 1, 0);
        p.assign(max_cols + 1, 0);
        way.assign(max_cols + 1, 0);
    }

    void augment(int r) {
        p[0] = r;
        int j0 = 0;
        vector<ll> minv(num_cols + 1, INF);
        vector<bool> used(num_cols + 1, false);

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = INF;
            for (int j = 1; j <= num_cols; j++) {
                if (!used[j]) {
                    // Standard reduced cost logic
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
            for (int j = 0; j <= num_cols; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    // Add a row that has weights for all 'num_cols'
    void add_row(const vector<ll>& row_weights) {
        num_rows++;
        for (int j = 1; j <= num_cols; j++) {
            cost[num_rows][j] = (j <= (int)row_weights.size()) ? row_weights[j-1] : -INF;
        }
        augment(num_rows);
    }

    ll get_max_weight() {
        return -v[0];
    }
};
