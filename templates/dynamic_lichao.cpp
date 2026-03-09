#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 2e18;

struct Line {
    ll m, c;
    ll eval(ll x) { return m * x + c; }
};

struct Node {
    Line line;
    Node *l = nullptr, *r = nullptr;
    Node(Line _l) : line(_l) {}
};

class LiChaoSegment {
    Node* root;
    ll min_x, max_x;

    // Standard Li-Chao insertion into a node
    void insert_line(Node* &t, ll L, ll R, Line new_line) {
        if (!t) { t = new Node(new_line); return; }
        
        ll mid = L + (R - L) / 2;
        bool b_low = new_line.eval(L) < t->line.eval(L);
        bool b_mid = new_line.eval(mid) < t->line.eval(mid);

        if (b_mid) swap(t->line, new_line);
        if (L == R) return;

        if (b_low != b_mid) insert_line(t->l, L, mid, new_line);
        else insert_line(t->r, mid + 1, R, new_line);
    }

    // Segment Tree range decomposition: find nodes covering [ql, qr]
    void add_segment(Node* &t, ll L, ll R, ll ql, ll qr, Line new_line) {
        if (ql > R || qr < L) return;
        if (!t) t = new Node({0, INF}); // Initialize with dummy

        if (ql <= L && R <= qr) {
            insert_line(t, L, R, new_line);
            return;
        }

        ll mid = L + (R - L) / 2;
        add_segment(t->l, L, mid, ql, qr, new_line);
        add_segment(t->r, mid + 1, R, ql, qr, new_line);
    }

    ll query(Node* t, ll L, ll R, ll x) {
        if (!t) return INF;
        ll res = t->line.eval(x);
        if (L == R) return res;

        ll mid = L + (R - L) / 2;
        if (x <= mid) return min(res, query(t->l, L, mid, x));
        else return min(res, query(t->r, mid + 1, R, x));
    }

public:
    LiChaoSegment(ll _min_x = -1e9, ll _max_x = 1e9) 
        : root(nullptr), min_x(_min_x), max_x(_max_x) {}

    // Add a line segment y = mx + c for x in [ql, qr]
    void add_line_segment(ll m, ll c, ll ql, ll qr) {
        add_segment(root, min_x, max_x, ql, qr, {m, c});
    }

    // Add an infinite line (default behavior)
    void add_line(ll m, ll c) {
        add_line_segment(m, c, min_x, max_x);
    }

    ll get_min(ll x) {
        return query(root, min_x, max_x, x);
    }
};

int main() {
    // Range of X is from 0 to 100
    LiChaoSegment lct(0, 100);

    // Add a line segment y = -2x + 50, active only for x in [10, 50]
    lct.add_line_segment(-2, 50, 10, 50);

    // Add an infinite line y = -1x + 30
    lct.add_line(-1, 30);

    cout << "Value at x=5: " << lct.get_min(5) << endl;   // Should use infinite line (25)
    cout << "Value at x=20: " << lct.get_min(20) << endl; // Segment (-2*20 + 50 = 10) is better than infinite (10 vs 10)
    cout << "Value at x=60: " << lct.get_min(60) << endl; // Segment inactive, uses infinite (-30)
    
    return 0;
}
