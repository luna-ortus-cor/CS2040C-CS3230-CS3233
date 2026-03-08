#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Node {
    int count = 0;
    int left = -1, right = -1;
};

class OnlineOST {
    vector<Node> tree;
    ll RANGE_MIN, RANGE_MAX;
    int root;
    bool isUnique;

    // Helper to create a new node and return its index
    int newNode() {
        tree.emplace_back();
        return tree.size() - 1;
    }

    void update(int &p, ll L, ll R, ll val, int delta) {
        if (p == -1) p = newNode();
        
        if (L == R) {
            tree[p].count += delta;
            return;
        }

        ll mid = L + (R - L) / 2;
        if (val <= mid) update(tree[p].left, L, mid, val, delta);
        else update(tree[p].right, mid + 1, R, val, delta);

        // Update count: handle cases where children might be -1
        int leftCount = (tree[p].left != -1) ? tree[tree[p].left].count : 0;
        int rightCount = (tree[p].right != -1) ? tree[tree[p].right].count : 0;
        tree[p].count = leftCount + rightCount;
    }

    int query(int p, ll L, ll R, ll i, ll j) {
        if (p == -1 || i > j || R < i || L > j) return 0;
        if (i <= L && R <= j) return tree[p].count;

        ll mid = L + (R - L) / 2;
        return query(tree[p].left, L, mid, i, j) + 
               query(tree[p].right, mid + 1, R, i, j);
    }

    ll kth(int p, ll L, ll R, int k) {
        if (L == R) return L;
        
        ll mid = L + (R - L) / 2;
        int leftCount = (tree[p].left != -1) ? tree[tree[p].left].count : 0;

        if (leftCount >= k) return kth(tree[p].left, L, mid, k);
        return kth(tree[p].right, mid + 1, R, k - leftCount);
    }

public:
    /**
     * @param minVal Minimum possible value (e.g., 0)
     * @param maxVal Maximum possible value (e.g., 1e18)
     * @param uniqueSet If true, duplicates are ignored
     */
    OnlineOST(ll minVal, ll maxVal, bool uniqueSet = false) {
        RANGE_MIN = minVal;
        RANGE_MAX = maxVal;
        isUnique = uniqueSet;
        root = newNode();
        tree.reserve(200000); // Optional: reserve space based on expected Q * log(Range)
    }

    void insert(ll val) {
        if (isUnique && count_range(val, val) > 0) return;
        update(root, RANGE_MIN, RANGE_MAX, val, 1);
    }

    void erase(ll val) {
        if (count_range(val, val) == 0) return;
        update(root, RANGE_MIN, RANGE_MAX, val, -1);
    }

    int rank_of(ll val) {
        return query(root, RANGE_MIN, RANGE_MAX, RANGE_MIN, val);
    }

    ll kthSmallest(int k) {
        if (k < 1 || k > tree[root].count) return -1;
        return kth(root, RANGE_MIN, RANGE_MAX, k);
    }

    int count_range(ll l, ll r) {
        return query(root, RANGE_MIN, RANGE_MAX, l, r);
    }

    int size() { return tree[root].count; }

    ll successor(ll x) {
        int r = rank_of(x);
        if (r >= size()) return -1;
        return kthSmallest(r + 1);
    }

    ll predecessor(ll x) {
        int r = rank_of(x - 1);
        if (r == 0) return -1;
        return kthSmallest(r);
    }
};
