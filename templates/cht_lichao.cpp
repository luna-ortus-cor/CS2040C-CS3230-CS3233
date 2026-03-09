#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

// Wrapper for Minimum CHT using the Maximum-based LineContainer
struct MinCHT {
    LineContainer lc;
    void addLine(ll m, ll c) { lc.add(-m, -c); }
    ll query(ll x) { return -lc.query(x); }
};

struct LCTNode {
    ll m, c;
    LCTNode *l = nullptr, *r = nullptr;
    LCTNode(ll _m, ll _c) : m(_m), c(_c) {}
    ll eval(ll x) { return m * x + c; }
};

class DynamicLiChao {
    LCTNode* root;
    ll L_bound, R_bound;

    void add_line(LCTNode* &t, ll L, ll R, ll nm, ll nc) {
        if (!t) { t = new LCTNode(nm, nc); return; }
        ll mid = L + (R - L) / 2;
        bool b_low = (nm * L + nc) < t->eval(L);
        bool b_mid = (nm * mid + nc) < t->eval(mid);
        if (b_mid) { swap(t->m, nm); swap(t->c, nc); }
        if (L == R) return;
        if (b_low != b_mid) add_line(t->l, L, mid, nm, nc);
        else add_line(t->r, mid + 1, R, nm, nc);
    }

    ll query(LCTNode* t, ll L, ll R, ll x) {
        if (!t) return 2e18; // Infinity
        ll res = t->eval(x);
        if (L == R) return res;
        ll mid = L + (R - L) / 2;
        if (x <= mid) return min(res, query(t->l, L, mid, x));
        else return min(res, query(t->r, mid + 1, R, x));
    }

public:
    DynamicLiChao(ll l, ll r) : root(nullptr), L_bound(l), R_bound(r) {}
    void add(ll m, ll c) { add_line(root, L_bound, R_bound, m, c); }
    ll get(ll x) { return query(root, L_bound, R_bound, x); }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<ll> dp(n);
    dp[0] = 0;

    // OPTION A: Using LineContainer
    MinCHT cht;
    cht.addLine(b[0], dp[0]);

    for (int i = 1; i < n; i++) {
        dp[i] = cht.query(a[i]);
        cht.addLine(b[i], dp[i]);
    }
    
    cout << "Result with LineContainer: " << dp[n - 1] << endl;

    // OPTION B: Using Dynamic LiChao (Range of a[i] up to 10^9)
    DynamicLiChao lct(0, 1000000000);
    lct.add(b[0], 0);
    
    ll lct_res = 0;
    for (int i = 1; i < n; i++) {
        lct_res = lct.get(a[i]);
        lct.add(b[i], lct_res);
    }

    cout << "Result with Li-Chao Tree: " << lct_res << endl;

    return 0;
}
