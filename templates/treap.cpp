#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key, priority, sz;
    Node *l, *r;

    Node(int k) : key(k), priority(rand()), sz(1), l(NULL), r(NULL) {}
};

class Treap {
private:
    Node *root;

    int get_sz(Node *t) { return t ? t->sz : 0; }

    void update_sz(Node *t) {
        if (t) t->sz = 1 + get_sz(t->l) + get_sz(t->r);
    }

    // Splits treap t into two: l gets all keys < k, r gets all keys >= k
    void split(Node *t, int k, Node *&l, Node *&r) {
        if (!t) { l = r = NULL; return; }
        if (t->key < k) {
            split(t->r, k, t->r, r);
            l = t;
        } else {
            split(t->l, k, l, t->l);
            r = t;
        }
        update_sz(t);
    }

    // Merges l and r (assuming all keys in l < all keys in r)
    Node* merge(Node *l, Node *r) {
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            l->r = merge(l->r, r);
            update_sz(l);
            return l;
        } else {
            r->l = merge(l, r->l);
            update_sz(r);
            return r;
        }
    }

public:
    Treap() : root(NULL) { srand(time(0)); }

    void insert(int k) {
        Node *l, *r, *mid;
        split(root, k, l, r);
        // Optional: for unique set, check if k exists here
        mid = new Node(k);
        root = merge(merge(l, mid), r);
    }

    void erase(int k) {
        Node *l, *r, *mid, *mr;
        split(root, k, l, r);
        split(r, k + 1, mid, mr); // mid contains all nodes with key == k
        if (mid) {
            Node* temp = mid;
            mid = merge(mid->l, mid->r); // remove one instance
            delete temp;
        }
        root = merge(l, merge(mid, mr));
    }

    int rank(int k) { // Number of elements < k
        Node *l, *r;
        split(root, k, l, r);
        int res = get_sz(l);
        root = merge(l, r);
        return res;
    }

    int kth(int k) { // 1-indexed kth smallest
        Node *cur = root;
        while (cur) {
            int left_sz = get_sz(cur->l);
            if (left_sz + 1 == k) return cur->key;
            if (left_sz >= k) cur = cur->l;
            else {
                k -= (left_sz + 1);
                cur = cur->r;
            }
        }
        return -1;
    }
};
