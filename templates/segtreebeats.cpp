#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/**
 * Segment Tree Beats
 * Supports: Range Add, Range Chmin, Range Chmax, Range Sum
 * Complexity: O((N + Q) log^2 N) amortized
 */

const ll INF = 2e18; // Safe infinity to prevent overflow on additions

struct Node {
    ll sum;
    ll max1, max2;
    int cnt_max;
    ll min1, min2;
    int cnt_min;
    ll lazy_add;
};

class SegTreeBeats {
private:
    int n;
    vector<Node> tree;

    void push_up(int p) {
        Node &res = tree[p], &a = tree[p << 1], &b = tree[p << 1 | 1];
        res.sum = a.sum + b.sum;

        // Merge Max
        if (a.max1 > b.max1) {
            res.max1 = a.max1; res.cnt_max = a.cnt_max;
            res.max2 = max(a.max2, b.max1);
        } else if (a.max1 < b.max1) {
            res.max1 = b.max1; res.cnt_max = b.cnt_max;
            res.max2 = max(a.max1, b.max2);
        } else {
            res.max1 = a.max1; res.cnt_max = a.cnt_max + b.cnt_max;
            res.max2 = max(a.max2, b.max2);
        }

        // Merge Min
        if (a.min1 < b.min1) {
            res.min1 = a.min1; res.cnt_min = a.cnt_min;
            res.min2 = min(a.min2, b.min1);
        } else if (a.min1 > b.min1) {
            res.min1 = b.min1; res.cnt_min = b.cnt_min;
            res.min2 = min(a.min1, b.min2);
        } else {
            res.min1 = a.min1; res.cnt_min = a.cnt_min + b.cnt_min;
            res.min2 = min(a.min2, b.min2);
        }
    }

    void apply_add(int p, int L, int R, ll v) {
        Node &node = tree[p];
        node.sum += v * (R - L + 1);
        node.max1 += v; 
        if (node.max2 != -INF) node.max2 += v;
        node.min1 += v; 
        if (node.min2 != INF) node.min2 += v;
        node.lazy_add += v;
    }

    void apply_chmin(int p, ll v) {
        Node &node = tree[p];
        node.sum += (v - node.max1) * node.cnt_max;
        if (node.min1 == node.max1) node.min1 = v;
        else if (node.min2 == node.max1) node.min2 = v;
        node.max1 = v;
    }

    void apply_chmax(int p, ll v) {
        Node &node = tree[p];
        node.sum += (v - node.min1) * node.cnt_min;
        if (node.max1 == node.min1) node.max1 = v;
        else if (node.max2 == node.min1) node.max2 = v;
        node.min1 = v;
    }

    void push_down(int p, int L, int R) {
        int mid = (L + R) >> 1;
        // 1. Apply addition first
        if (tree[p].lazy_add != 0) {
            apply_add(p << 1, L, mid, tree[p].lazy_add);
            apply_add(p << 1 | 1, mid + 1, R, tree[p].lazy_add);
            tree[p].lazy_add = 0;
        }
        // 2. Propagate Chmin
        if (tree[p << 1].max1 > tree[p].max1) apply_chmin(p << 1, tree[p].max1);
        if (tree[p << 1 | 1].max1 > tree[p].max1) apply_chmin(p << 1 | 1, tree[p].max1);
        // 3. Propagate Chmax
        if (tree[p << 1].min1 < tree[p].min1) apply_chmax(p << 1, tree[p].min1);
        if (tree[p << 1 | 1].min1 < tree[p].min1) apply_chmax(p << 1 | 1, tree[p].min1);
    }

    void build(const vector<ll> &a, int p, int L, int R) {
        if (L == R) {
            tree[p] = {a[L], a[L], -INF, 1, a[L], INF, 1, 0};
            return;
        }
        int mid = (L + R) >> 1;
        build(a, p << 1, L, mid);
        build(a, p << 1 | 1, mid + 1, R);
        push_up(p);
    }

    void range_add(int p, int L, int R, int i, int j, ll v) {
        if (R < i || L > j) return;
        if (i <= L && R <= j) {
            apply_add(p, L, R, v);
            return;
        }
        push_down(p, L, R);
        int mid = (L + R) >> 1;
        range_add(p << 1, L, mid, i, j, v);
        range_add(p << 1 | 1, mid + 1, R, i, j, v);
        push_up(p);
    }

    void range_chmin(int p, int L, int R, int i, int j, ll v) {
        if (R < i || L > j || tree[p].max1 <= v) return;
        if (i <= L && R <= j && tree[p].max2 < v) {
            apply_chmin(p, v);
            return;
        }
        push_down(p, L, R);
        int mid = (L + R) >> 1;
        range_chmin(p << 1, L, mid, i, j, v);
        range_chmin(p << 1 | 1, mid + 1, R, i, j, v);
        push_up(p);
    }

    void range_chmax(int p, int L, int R, int i, int j, ll v) {
        if (R < i || L > j || tree[p].min1 >= v) return;
        if (i <= L && R <= j && tree[p].min2 > v) {
            apply_chmax(p, v);
            return;
        }
        push_down(p, L, R);
        int mid = (L + R) >> 1;
        range_chmax(p << 1, L, mid, i, j, v);
        range_chmax(p << 1 | 1, mid + 1, R, i, j, v);
        push_up(p);
    }

    ll query_sum(int p, int L, int R, int i, int j) {
        if (R < i || L > j) return 0;
        if (i <= L && R <= j) return tree[p].sum;
        push_down(p, L, R);
        int mid = (L + R) >> 1;
        return query_sum(p << 1, L, mid, i, j) + query_sum(p << 1 | 1, mid + 1, R, i, j);
    }

public:
    SegTreeBeats(const vector<ll> &a) : n(a.size()) {
        tree.resize(n * 4);
        build(a, 1, 0, n - 1);
    }
    void add(int l, int r, ll v) { range_add(1, 0, n - 1, l, r, v); }
    void chmin(int l, int r, ll v) { range_chmin(1, 0, n - 1, l, r, v); }
    void chmax(int l, int r, ll v) { range_chmax(1, 0, n - 1, l, r, v); }
    ll sum(int l, int r) { return query_sum(1, 0, n - 1, l, r); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // Example usage
    int N = 5;
    vector<ll> a = {1, 5, 2, 8, 3};
    SegTreeBeats st(a);
    st.chmin(0, 3, 4); // {1, 4, 2, 4, 3}
    cout << st.sum(0, 4) << "\n"; // Output: 14
    return 0;
}
