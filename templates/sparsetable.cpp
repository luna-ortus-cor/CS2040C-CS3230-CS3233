#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

template <typename T>
class SparseTable {
private:
    int n, max_log;
    vector<vector<T>> st;
    vector<int> logs;
    
    // Idempotent operation: change this to max, gcd, &, | as needed
    T combine(T a, T b) {
        return min(a, b); 
    }

public:
    SparseTable() : n(0) {}
    
    SparseTable(const vector<T>& a) {
        n = a.size();
        max_log = floor(log2(n)) + 1;
        st.assign(max_log, vector<T>(n));
        logs.assign(n + 1, 0);

        // 1. Precompute logs for O(1) query
        for (int i = 2; i <= n; i++)
            logs[i] = logs[i / 2] + 1;

        // 2. Build Sparse Table - O(N log N)
        for (int i = 0; i < n; i++)
            st[0][i] = a[i];

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // O(1) Query
    T query(int L, int R) {
        if (L > R) return 2e18; // Or appropriate neutral element
        int j = logs[R - L + 1];
        return combine(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

// Specialized version for Index-based RMQ
class SparseTableIdx {
private:
    int n, max_log;
    vector<vector<int>> st;
    vector<int> logs, A;

    int combine_idx(int i, int j) {
        return (A[i] <= A[j]) ? i : j;
    }

public:
    SparseTableIdx(const vector<int>& initialA) : A(initialA) {
        n = A.size();
        max_log = 31 - __builtin_clz(n) + 1; // Faster log2 calculation
        st.assign(max_log, vector<int>(n));
        logs.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) logs[i] = logs[i / 2] + 1;

        for (int i = 0; i < n; i++) st[0][i] = i;
        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = combine_idx(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query_idx(int L, int R) {
        int j = logs[R - L + 1];
        return combine_idx(st[j][L], st[j][R - (1 << j) + 1]);
    }
};

struct Node {
    int val, left, right;
};

vector<Node> cartesianTree;
int buildCartesian(int L, int R, SparseTableIdx &st, const vector<int> &A) {
    if (L > R) return -1;
    
    // Find the minimum index in O(1)
    int rootIdx = st.query_idx(L, R);
    
    int nodeIdx = cartesianTree.size();
    cartesianTree.push_back({A[rootIdx], -1, -1});
    
    // Recursively build children
    int leftChild = buildCartesian(L, rootIdx - 1, st, A);
    int rightChild = buildCartesian(rootIdx + 1, R, st, A);
    
    cartesianTree[nodeIdx].left = leftChild;
    cartesianTree[nodeIdx].right = rightChild;
    
    return nodeIdx;
}

struct SuffixArray {
    string s;
    int n;
    vector<int> sa, rank, lcp;
    SparseTable<int> st;

    SuffixArray(string _s) : s(_s + "$") { // Append sentinel
        n = s.length();
        sa.resize(n);
        rank.resize(n);
        build_sa();
        build_lcp();
        st = SparseTable<int>(lcp);
    }

    void build_sa() {
        vector<int> tmp(n);
        for (int i = 0; i < n; i++) sa[i] = i, rank[i] = s[i];
        for (int k = 1; k < n; k <<= 1) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ri = i + k < n ? rank[i + k] : -1;
                int rj = j + k < n ? rank[j + k] : -1;
                return ri < rj;
            };
            sort(sa.begin(), sa.end(), cmp);
            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
            rank = tmp;
        }
    }

    void build_lcp() {
        lcp.assign(n, 0);
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pos = rank[i];
            int j = sa[pos - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pos] = k;
            if (k > 0) k--;
        }
    }

    // THE FIX: Querying the LCP between original indices i and j
    int get_lcp(int i, int j) {
        if (i == j) return n - 1 - i;
        int l = rank[i], r = rank[j];
        if (l > r) swap(l, r);
        // Range is [l+1, r] in the LCP array
        return st.query(l + 1, r);
    }
};


int main() {
  vi A = {18, 17, 13, 19, 15, 11, 20};
  SparseTable SpT(A);
  int n = (int)A.size();
  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j)
      printf("RMQ(%d, %d) = %d\n", i, j, SpT.query(i, j));
  return 0;
}
