#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

const ll INF = 2e18;

struct Node {
    ll sum, mn, mx, xr;

    static Node merge(const Node& a, const Node& b) {
        return {
            a.sum + b.sum,
            min(a.mn, b.mn),
            max(a.mx, b.mx),
            a.xr ^ b.xr
        };
    }
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;
    vector<ll> lazy_add, lazy_set;
    vector<bool> has_set;

    Node neutral_element = {0, INF, -INF, 0};

    void apply_set(int p, int L, int R, ll v) {
        ll len = (R - L + 1);
        tree[p].sum = len * v;
        tree[p].mn = v;
        tree[p].mx = v;
        tree[p].xr = (len % 2 == 1) ? v : 0;
        
        lazy_set[p] = v;
        lazy_add[p] = 0; // Assignment wipes out previous additions
        has_set[p] = true;
    }

    void apply_add(int p, int L, int R, ll v) {
        ll len = (R - L + 1);
        tree[p].sum += len * v;
        tree[p].mn += v;
        tree[p].mx += v;
        // Note: Range XOR under addition is non-trivial. 
        // This logic only works for Assignment + Addition if XOR isn't the primary goal.
        if (len % 2 == 1) tree[p].xr ^= v; 

        if (has_set[p]) lazy_set[p] += v;
        else lazy_add[p] += v;
    }

    void push(int p, int L, int R) {
        int m = (L + R) / 2;
        if (has_set[p]) {
            apply_set(2 * p, L, m, lazy_set[p]);
            apply_set(2 * p + 1, m + 1, R, lazy_set[p]);
            has_set[p] = false;
        }
        if (lazy_add[p] != 0) {
            apply_add(2 * p, L, m, lazy_add[p]);
            apply_add(2 * p + 1, m + 1, R, lazy_add[p]);
            lazy_add[p] = 0;
        }
    }

    // O(log N) Walk: Find first index i in [qL, qR] such that A[i] >= val
    int walk_first(int p, int L, int R, int qL, int qR, ll val) {
        // 1. Out of range or no element in this subtree is large enough
        if (L > qR || R < qL || tree[p].mx < val) return -1;
        
        // 2. Leaf node reached
        if (L == R) return L;

        push(p, L, R);
        int m = (L + R) / 2;
        
        // 3. Try left subtree first
        int res = walk_first(2 * p, L, m, qL, qR, val);
        
        // 4. If not in left, try right subtree
        if (res == -1) {
            res = walk_first(2 * p + 1, m + 1, R, qL, qR, val);
        }
        return res;
    }

    // O(log N) Walk: Find last index i in [qL, qR] such that A[i] >= val
    int walk_last(int p, int L, int R, int qL, int qR, ll val) {
        if (L > qR || R < qL || tree[p].mx < val) return -1;
        if (L == R) return L;
        push(p, L, R);
        int m = (L + R) / 2;
        int res = walk_last(2 * p + 1, m + 1, R, qL, qR, val); // Right first
        if (res == -1) res = walk_last(2 * p, L, m, qL, qR, val);
        return res;
    }

    void build(const vll& A, int p, int L, int R) {
        if (L == R) {
            tree[p] = {A[L], A[L], A[L], A[L]};
            return;
        }
        int m = (L + R) / 2;
        build(A, 2 * p, L, m);
        build(A, 2 * p + 1, m + 1, R);
        tree[p] = Node::merge(tree[2 * p], tree[2 * p + 1]);
    }

    void update_set(int p, int L, int R, int i, int j, ll val) {
        if (i > j || L > j || R < i) return;
        if (L >= i && R <= j) { apply_set(p, L, R, val); return; }
        push(p, L, R);
        int m = (L + R) / 2;
        update_set(2 * p, L, m, i, j, val);
        update_set(2 * p + 1, m + 1, R, i, j, val);
        tree[p] = Node::merge(tree[2 * p], tree[2 * p + 1]);
    }

    // Overload for set update
    void update_set_internal(int p, int L, int R, int i, int j, ll val) {
        if (i > j || L > j || R < i) return;
        if (L >= i && R <= j) { apply_set(p, L, R, val); return; }
        push(p, L, R);
        int m = (L + R) / 2;
        update_set_internal(2 * p, L, m, i, j, val);
        update_set_internal(2 * p + 1, m + 1, R, i, j, val);
        tree[p] = Node::merge(tree[2 * p], tree[2 * p + 1]);
    }

    void update_add_internal(int p, int L, int R, int i, int j, ll val) {
        if (i > j || L > j || R < i) return;
        if (L >= i && R <= j) { apply_add(p, L, R, val); return; }
        push(p, L, R);
        int m = (L + R) / 2;
        update_add_internal(2 * p, L, m, i, j, val);
        update_add_internal(2 * p + 1, m + 1, R, i, j, val);
        tree[p] = Node::merge(tree[2 * p], tree[2 * p + 1]);
    }

    Node query_internal(int p, int L, int R, int i, int j) {
        if (i > j || L > j || R < i) return neutral_element;
        if (L >= i && R <= j) return tree[p];
        push(p, L, R);
        int m = (L + R) / 2;
        return Node::merge(query_internal(2 * p, L, m, i, j),
                           query_internal(2 * p + 1, m + 1, R, i, j));
    }

    int find_prefix_sum(int p, int L, int R, ll target){
        if(L == R) return L;
    
        push(p,L,R);
        int m=(L+R)/2;
    
        if(tree[2*p].sum >= target)
            return find_prefix_sum(2*p, L, m, target);
        else
            return find_prefix_sum(2*p+1, m+1, R, target-tree[2*p].sum);
    }

public:
    SegmentTree(const vll& A) {
        n = A.size();
        tree.assign(4 * n, {0, 0, 0, 0});
        lazy_add.assign(4 * n, 0);
        lazy_set.assign(4 * n, 0);
        has_set.assign(4 * n, false);
        build(A, 1, 0, n - 1);
    }

    void range_set(int i, int j, ll val) { update_set_internal(1, 0, n - 1, i, j, val); }
    void range_add(int i, int j, ll val) { update_add_internal(1, 0, n - 1, i, j, val); }

    ll query_sum(int i, int j) { return query_internal(1, 0, n - 1, i, j).sum; }
    ll query_min(int i, int j) { return query_internal(1, 0, n - 1, i, j).mn; }
    ll query_max(int i, int j) { return query_internal(1, 0, n - 1, i, j).mx; }
    ll query_xor(int i, int j) { return query_internal(1, 0, n - 1, i, j).xr; }

    int find_first_geq(int i, int j, ll val) { return walk_first(1, 0, n - 1, i, j, val); }
    int find_last_geq(int i, int j, ll val) { return walk_last(1, 0, n - 1, i, j, val); }

    int find_prefix_sum(ll target){
        if(tree[1].sum < target) return -1;
        return find_prefix_sum(1,0,n-1,target);
    }
};

int main() {
  vll A = {18, 17, 13, 19, 15, 11, 20, 99};       // make n a power of 2
  SegmentTree st(A);

  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("              A is {18,17,13,19,15,11,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.query_min(1, 3));      // 13
  printf("RMQ(4, 7) = %d\n", st.query_min(4, 7));      // 11
  printf("RMQ(3, 4) = %d\n", st.query_min(3, 4));      // 15

  st.range_set(5, 5, 77);                           // update A[5] to 77
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {18,17,13,19,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.query_min(1, 3));      // remains 13
  printf("RMQ(4, 7) = %d\n", st.query_min(4, 7));      // now 15
  printf("RMQ(3, 4) = %d\n", st.query_min(3, 4));      // remains 15

  st.range_set(0, 3, 30);                           // update A[0..3] to 30
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30,30,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.query_min(1, 3));      // now 30
  printf("RMQ(4, 7) = %d\n", st.query_min(4, 7));      // remains 15
  printf("RMQ(3, 4) = %d\n", st.query_min(3, 4));      // remains 15

  st.range_set(3, 3, 7);                            // update A[3] to 7
  printf("              idx    0, 1, 2, 3, 4, 5, 6, 7\n");
  printf("Now, modify A into {30,30,30, 7,15,77,20,oo}\n");
  printf("RMQ(1, 3) = %d\n", st.query_min(1, 3));      // now 7
  printf("RMQ(4, 7) = %d\n", st.query_min(4, 7));      // remains 15
  printf("RMQ(3, 4) = %d\n", st.query_min(3, 4));      // now 7

  return 0;
}
