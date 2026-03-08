#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1e9 + 7;

struct Node {
    int val, priority, sz;
    ll sum;
    int min_v, max_v;
    
    // Lazy tags
    ll lazy_add = 0;
    int lazy_set = -INF; // -INF means no set operation pending
    bool rev = false;

    Node *l = nullptr, *r = nullptr;

    Node(int v) : val(v), priority(rand()), sz(1), sum(v), min_v(v), max_v(v) {}
};

class ImplicitTreap {
private:
    Node *root = nullptr;

    int get_sz(Node *t) { return t ? t->sz : 0; }

    void push_up(Node *t) {
        if (!t) return;
        t->sz = 1 + get_sz(t->l) + get_sz(t->r);
        t->sum = t->val + (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0);
        t->min_v = t->val;
        t->max_v = t->val;
        if (t->l) {
            t->min_v = min(t->min_v, t->l->min_v);
            t->max_v = max(t->max_v, t->l->max_v);
        }
        if (t->r) {
            t->min_v = min(t->min_v, t->r->min_v);
            t->max_v = max(t->max_v, t->r->max_v);
        }
    }

    // Helper to apply lazy updates to a node
    void apply_set(Node *t, int v) {
        if (!t) return;
        t->val = v;
        t->sum = (ll)v * t->sz;
        t->min_v = t->max_v = v;
        t->lazy_set = v;
        t->lazy_add = 0; // Set overrides previous additions
    }

    void apply_add(Node *t, ll v) {
        if (!t) return;
        t->val += v;
        t->sum += v * t->sz;
        t->min_v += v;
        t->max_v += v;
        t->lazy_add += v;
    }

    void apply_rev(Node *t) {
        if (!t) return;
        t->rev = !t->rev;
        swap(t->l, t->r);
    }

    void push_down(Node *t) {
        if (!t) return;
        if (t->rev) {
            apply_rev(t->l);
            apply_rev(t->r);
            t->rev = false;
        }
        if (t->lazy_set != -INF) {
            apply_set(t->l, t->lazy_set);
            apply_set(t->r, t->lazy_set);
            t->lazy_set = -INF;
        }
        if (t->lazy_add != 0) {
            apply_add(t->l, t->lazy_add);
            apply_add(t->r, t->lazy_add);
            t->lazy_add = 0;
        }
    }

    void split(Node *t, int k, Node *&l, Node *&r) {
        if (!t) { l = r = nullptr; return; }
        push_down(t);
        int left_sz = get_sz(t->l);
        if (left_sz < k) {
            split(t->r, k - left_sz - 1, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }
        push_up(t);
    }

    Node* merge(Node *l, Node *r) {
        push_down(l);
        push_down(r);
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            l->r = merge(l->r, r);
            push_up(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            push_up(r);
            return r;
        }
    }

public:
    ImplicitTreap() { srand(time(0)); }

    // 1. Insert element at pos (0-indexed)
    void insert(int pos, int val) {
        Node *l, *r;
        split(root, pos, l, r);
        root = merge(merge(l, new Node(val)), r);
    }

    // 2. Removal of element at pos
    void erase(int pos) {
        Node *l, *mid, *r;
        split(root, pos, l, mid);
        split(mid, 1, mid, r);
        delete mid;
        root = merge(l, r);
    }

    // Generic function to extract range [L, R] and apply a lambda
    template<typename T>
    void process_range(int L, int R, T func) {
        Node *l, *mid, *r;
        split(root, L, l, mid);
        split(mid, R - L + 1, mid, r);
        func(mid);
        root = merge(l, merge(mid, r));
    }

    // 3. Range Queries (Sum, Min, Max)
    ll query_sum(int L, int R) {
        ll res;
        process_range(L, R, [&](Node *&mid) { res = mid->sum; });
        return res;
    }

    // 4. Addition and Painting
    void range_add(int L, int R, int val) {
        process_range(L, R, [&](Node *&mid) { apply_add(mid, val); });
    }

    void range_paint(int L, int R, int val) {
        process_range(L, R, [&](Node *&mid) { apply_set(mid, val); });
    }

    // 5. Reversing
    void range_reverse(int L, int R) {
        process_range(L, R, [&](Node *&mid) { apply_rev(mid); });
    }
};
