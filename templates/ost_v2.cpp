#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class OrderStatisticTree {
    vector<int> tree;
    vector<ll> coords; // Stores the original values for mapping
    int n;
    int current_size = 0;
    bool isUnique;

    // Standard Segment Tree Update
    void update(int p, int L, int R, int idx, int delta) {
        if (L == R) {
            tree[p] += delta;
            return;
        }
        int m = L + (R - L) / 2;
        if (idx <= m) update(2 * p, L, m, idx, delta);
        else update(2 * p + 1, m + 1, R, idx, delta);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }

    int query(int p, int L, int R, int i, int j) {
        if (i > j || R < i || L > j) return 0;
        if (i <= L && R <= j) return tree[p];
        int m = L + (R - L) / 2;
        return query(2 * p, L, m, i, j) + query(2 * p + 1, m + 1, R, i, j);
    }

    int kth(int p, int L, int R, int k) {
        if (L == R) return L;
        int m = L + (R - L) / 2;
        if (tree[2 * p] >= k) return kth(2 * p, L, m, k);
        return kth(2 * p + 1, m + 1, R, k - tree[2 * p]);
    }

    // Maps a real value to its compressed index [0...n-1]
    int get_idx(ll val) {
        auto it = lower_bound(coords.begin(), coords.end(), val);
        if (it == coords.end() || *it != val) return -1;
        return distance(coords.begin(), it);
    }

public:
    /**
     * @param all_possible_values All values that will be used in queries.
     * @param uniqueSet If true, duplicate inserts are ignored.
     */
    OrderStatisticTree(vector<ll> all_possible_values, bool uniqueSet = false) {
        isUnique = uniqueSet;
        sort(all_possible_values.begin(), all_possible_values.end());
        all_possible_values.erase(unique(all_possible_values.begin(), all_possible_values.end()), all_possible_values.end());
        
        coords = all_possible_values;
        n = coords.size();
        tree.assign(4 * n + 1, 0);
    }

    void insert(ll val) {
        int idx = get_idx(val);
        if (idx == -1) return;

        if (isUnique) {
            // Check if element already exists (count in range [idx, idx] is > 0)
            if (query(1, 0, n - 1, idx, idx) > 0) return;
        }

        update(1, 0, n - 1, idx, 1);
        current_size++;
    }

    void erase(ll val) {
        int idx = get_idx(val);
        if (idx == -1) return;

        int current_count = query(1, 0, n - 1, idx, idx);
        if (current_count == 0) return;

        // For multisets, we only remove one instance. 
        update(1, 0, n - 1, idx, -1);
        current_size--;
    }

    int rank_of(ll val) {
        // Returns number of elements <= val
        auto it = upper_bound(coords.begin(), coords.end(), val);
        if (it == coords.begin()) return 0;
        int idx = distance(coords.begin(), prev(it));
        return query(1, 0, n - 1, 0, idx);
    }

    ll kthSmallest(int k) {
        if (k < 1 || k > current_size) return -1; // Or throw error
        return coords[kth(1, 0, n - 1, k)];
    }

    ll successor(ll x) {
        int r = rank_of(x);
        if (r >= current_size) return -1; 
        return kthSmallest(r + 1);
    }

    ll predecessor(ll x) {
        int r = rank_of(x - 1);
        if (r == 0) return -1;
        return kthSmallest(r);
    }

    int size() { return current_size; }
};
