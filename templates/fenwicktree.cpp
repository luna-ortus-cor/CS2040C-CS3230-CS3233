#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
#define LSOne(S) ((S) & -(S))

// 1. Unified 1D Fenwick Tree (PURQ + Binary Lifting)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
#define LSOne(S) ((S) & -(S))

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

    // updates BY v, not TO v
    void update(int i, ll v) {
        for (; i <= n; i += LSOne(i)) ft[i] += v;
        //for (; i <= n; i += LSOne(i)) ft[i] ^= v; // modification for XOR
    }

    ll query(int i) {
        ll sum = 0;
        for (; i > 0; i -= LSOne(i)) sum += ft[i];
        //for (; i > 0; i -= LSOne(i)) sum ^= ft[i]; // modification for XOR
        return sum;
    }

    ll query(int i, int j) {
        return query(j) - query(i - 1);
        //return query(j) ^ query(i - 1); // modification for XOR
    }
    
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

// 2. Range Update Range Query (RURQ)
// Uses the formula: Sum(1, i) = (i+1)*Sum(D, i) - Sum(i*D, i)
class FenwickTreeRURQ {
private:
    FenwickTree ft1, ft2;
    int n;

public:
    FenwickTreeRURQ(int m) : ft1(m), ft2(m), n(m) {}

    void range_update(int l, int r, ll v) {
        ft1.update(l, v);
        ft1.update(r + 1, -v);
        ft2.update(l, v * (l - 1));
        ft2.update(r + 1, -v * r);
    }

    ll query(int i) {
        return ft1.query(i) * i - ft2.query(i);
    }

    ll query(int l, int r) { return query(r) - query(l - 1); }
};

// 3. 2D Fenwick Tree (PURQ for Grids)
class FenwickTree2D {
private:
    vector<vector<ll>> ft;
    int R, C;

public:
    FenwickTree2D(int r, int c) : R(r), C(c) {
        ft.assign(R + 1, vector<ll>(C + 1, 0));
    }

    void update(int r, int c, ll v) {
        for (int i = r; i <= R; i += LSOne(i))
            for (int j = c; j <= C; j += LSOne(j))
                ft[i][j] += v;
    }

    ll query(int r, int c) {
        ll sum = 0;
        for (int i = r; i > 0; i -= LSOne(i))
            for (int j = c; j > 0; j -= LSOne(j))
                sum += ft[i][j];
        return sum;
    }

    ll query(int r1, int c1, int r2, int c2) {
        return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
    }
};

class FenwickTree3D {
private:
    vector<vector<vector<ll>>> ft;
    int X, Y, Z;

public:
    FenwickTree3D(int x, int y, int z) : X(x), Y(y), Z(z) {
        ft.assign(X + 1, vector<vector<ll>>(Y + 1, vector<ll>(Z + 1, 0)));
    }

    void update(int x, int y, int z, ll v) {
        for (int i = x; i <= X; i += LSOne(i))
            for (int j = y; j <= Y; j += LSOne(j))
                for (int k = z; k <= Z; k += LSOne(k))
                    ft[i][j][k] += v;
    }

    ll query(int x, int y, int z) {
        ll sum = 0;
        for (int i = x; i > 0; i -= LSOne(i))
            for (int j = y; j > 0; j -= LSOne(j))
                for (int k = z; k > 0; k -= LSOne(k))
                    sum += ft[i][j][k];
        return sum;
    }

    ll query(int x1, int y1, int z1, int x2, int y2, int z2) {
        return query(x2, y2, z2) 
             - query(x1 - 1, y2, z2) - query(x2, y1 - 1, z2) - query(x2, y2, z1 - 1)
             + query(x1 - 1, y1 - 1, z2) + query(x1 - 1, y2, z1 - 1) + query(x2, y1 - 1, z1 - 1)
             - query(x1 - 1, y1 - 1, z1 - 1);
    }
};

ll count_inversions(vi &a) {
    int n = a.size();
    vi temp = a;
    
    // 1. Coordinate Compression
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    
    for (int &x : a) {
        // Map x to its 1-indexed rank
        x = lower_bound(temp.begin(), temp.end(), x) - temp.begin() + 1;
    }

    // 2. Count Inversions using BIT
    FenwickTree ft(temp.size());
    ll inv_count = 0;
    for (int i = n - 1; i >= 0; --i) {
        // Query how many elements already seen are smaller than current
        inv_count += ft.query(a[i] - 1);
        ft.update(a[i], 1);
    }
    return inv_count;
}

int main() {
  vll f = {0,0,1,0,1,2,3,2,1,1,0};               // index 0 is always 0
  FenwickTree ft(f);
  printf("%lld\n", ft.query(1, 6)); // 7 => ft[6]+ft[4] = 5+2 = 7
  printf("%d\n", ft.select(7)); // index 6, rsq(1, 6) == 7, which is >= 7
  ft.update(5, 1); // update demo
  printf("%lld\n", ft.query(1, 10)); // now 12
  printf("=====\n");
  FenwickTreeRURQ rupq(10);
  FenwickTreeRURQ rurq(10);
  rupq.range_update(2, 9, 7); // indices in [2, 3, .., 9] updated by +7
  rurq.range_update(2, 9, 7); // same as rupq above
  rupq.range_update(6, 7, 3); // indices 6&7 are further updated by +3 (10)
  rurq.range_update(6, 7, 3); // same as rupq above
  // idx = 0 (unused) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10
  // val = -          | 0 | 7 | 7 | 7 | 7 |10 |10 | 7 | 7 | 0
  for (int i = 1; i <= 10; i++)
    printf("%d -> %lld\n", i, rupq.query(i));
  printf("RSQ(1, 10) = %lld\n", rurq.query(1, 10)); // 62
  printf("RSQ(6, 7) = %lld\n", rurq.query(6, 7)); // 20
  return 0;
}
