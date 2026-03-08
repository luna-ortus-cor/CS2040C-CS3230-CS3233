#include <bits/stdc++.h>
using namespace std;

class OrderStatisticTree {
    vector<int> tree;
    int n;
    int current_size = 0;

    void update(int p, int L, int R, int idx, int delta) {
        if (L == R) {
            tree[p] += delta;
            return;
        }
        int m = (L + R) / 2;
        if (idx <= m) update(2 * p, L, m, idx, delta);
        else update(2 * p + 1, m + 1, R, idx, delta);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }

    int query(int p, int L, int R, int i, int j) {
        if (i > j || R < i || L > j) return 0;
        if (i <= L && R <= j) return tree[p];
        int m = (L + R) / 2;
        return query(2 * p, L, m, i, j) + query(2 * p + 1, m + 1, R, i, j);
    }

    int kth(int p, int L, int R, int k) {
        if (L == R) return L;
        int m = (L + R) / 2;
        if (tree[2 * p] >= k) return kth(2 * p, L, m, k);
        return kth(2 * p + 1, m + 1, R, k - tree[2 * p]);
    }

public:
    OrderStatisticTree(int N) : n(N), tree(4 * N, 0) {}

    void insert(int val) { 
        if (val < 0 || val >= n) return;
        update(1, 0, n - 1, val, 1); 
        current_size++;
    }

    void erase(int val) {
        if (val < 0 || val >= n || rank_of(val) == rank_of(val - 1)) return; 
        update(1, 0, n - 1, val, -1);
        current_size--;
    }

    // --- NEW METHODS ---

    // 1. Total elements in set
    int size() { return current_size; }

    // 2. Number of elements <= x
    int rank_of(int x) { 
        if (x < 0) return 0;
        if (x >= n) return current_size;
        return query(1, 0, n - 1, 0, x); 
    }

    // 3. Count elements in range [l, r]
    int count_range(int l, int r) {
        return rank_of(r) - rank_of(l - 1);
    }

    // 4. Smallest element currently in the tree
    int find_min() {
        if (current_size == 0) return -1;
        return kthSmallest(1);
    }

    // 5. Largest element currently in the tree
    int find_max() {
        if (current_size == 0) return -1;
        return kthSmallest(current_size);
    }

    // 6. Successor: Smallest element strictly > x
    int successor(int x) {
        int r = rank_of(x);
        if (r >= current_size) return -1; // No successor
        return kthSmallest(r + 1);
    }

    // 7. Predecessor: Largest element strictly < x
    int predecessor(int x) {
        int r = rank_of(x - 1);
        if (r == 0) return -1; // No predecessor
        return kthSmallest(r);
    }

    // 8. Find the k-th smallest element (1-indexed)
    int kthSmallest(int k) {
        if (k < 1 || k > current_size) return -1;
        return kth(1, 0, n - 1, k);
    }

    // 9. Wipe the tree
    void clear() {
        fill(tree.begin(), tree.end(), 0);
        current_size = 0;
    }
};
