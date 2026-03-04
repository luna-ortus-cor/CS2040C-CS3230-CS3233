#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
#define LSOne(S) ((S) & -(S))

// 1. Unified 1D Fenwick Tree (PURQ + Binary Lifting)
class FenwickTree {
private:
    vll ft;
    int n;

public:
    // Create an empty FT
    FenwickTree(int m) : n(m) { ft.assign(m + 1, 0); }

    // O(m) build logic from a 0-indexed frequency vector
    void build(const vll &f) {
        int m = (int)f.size() - 1; // f[0] is ignored
        n = m;
        ft.assign(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            ft[i] += f[i];
            if (i + LSOne(i) <= m)
                ft[i + LSOne(i)] += ft[i];
        }
    }

    // Constructor from frequency array f
    FenwickTree(const vll &f) { build(f); }

    // Constructor from array of elements s (converts to frequency first)
    FenwickTree(int m, const vi &s) {
        vll f(m + 1, 0);
        for (int x : s) {
            if (x >= 1 && x <= m) ++f[x];
        }
        build(f);
    }

    void update(int i, ll v) {
        for (; i <= n; i += LSOne(i)) ft[i] += v;
    }

    ll query(int i) {
        ll sum = 0;
        for (; i > 0; i -= LSOne(i)) sum += ft[i];
        return sum;
    }

    ll query(int i, int j) { return query(j) - query(i - 1); }
    
    // Optimized select: Returns the smallest index i such that query(i) >= k
    // Uses Binary Lifting - O(log N)
    int select(ll k) {
        int idx = 0;
        // Start from the highest power of 2 <= n
        for (int i = 1 << (int)log2(n); i > 0; i >>= 1) {
            if (idx + i <= n && ft[idx + i] < k) {
                idx += i;
                k -= ft[idx];
            }
        }
        return idx + 1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    ll N,K;
    cin>>N>>K;
    FenwickTree ft(N);
    for(ll j=0;j<K;j++){
        char c;
        int l,r,i;
        cin>>c;
        if(c=='F'){
            cin>>i;
            ll curr=ft.query(i,i);
            ft.update(i,1-2*curr);
        }else{
            cin>>l>>r;
            cout<<ft.query(l,r)<<"\n";
        }
    }
    return 0;
}
