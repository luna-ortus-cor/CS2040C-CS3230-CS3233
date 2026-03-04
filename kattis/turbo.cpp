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
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    vector<int> a(N);
    vector<int> pos(N+1);

    for(int i=0;i<N;i++){
        cin>>a[i];
        pos[a[i]]=i;
    }

    vector<ll> init(N,1LL);
    SegmentTree seg(init);
    int lo=1,hi=N;
    vector<ll> ans;
    ans.reserve(N);
    for(int phase=1;phase<=N;phase++){
        if(phase%2==1){
            int idx=pos[lo++];
            ll swaps=seg.query_sum(0,idx-1);
            ans.push_back(swaps);
            seg.range_add(idx,idx,-1);
        } else {
            int idx=pos[hi--];
            ll swaps=seg.query_sum(idx+1,N-1);
            ans.push_back(swaps);
            seg.range_add(idx,idx,-1);
        }
    }
    for(ll x:ans)cout<<x<<"\n";
    return 0;
}
