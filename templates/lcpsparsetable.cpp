#include <bits/stdc++.h>
using namespace std;

/**
 * Generic Sparse Table for Range Minimum Queries (RMQ).
 * Efficient O(1) query after O(N log N) preprocessing.
 */
template<typename T>
struct SparseTable {
    int n;
    vector<vector<T>> st;
    vector<int> lg;

    SparseTable() {}
    SparseTable(const vector<T>& v) {
        n = v.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = lg[n] + 1;
        st.assign(K, vector<T>(n));
        for (int i = 0; i < n; i++) st[0][i] = v[i];
        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int L, int R) {
        if (L > R) return numeric_limits<T>::max();
        int k = lg[R - L + 1];
        return min(st[k][L], st[k][R - (1 << k) + 1]);
    }
};

/**
 * LCP: Handles LCP queries for a sorted list of strings.
 */
struct LCP {
    int N;
    vector<string> sorted_docs;
    vector<int> lcp_array;
    SparseTable<int> rmq;

    LCP(const vector<string>& s) : sorted_docs(s) {
        N = s.size();
        lcp_array.assign(N, 0); // lcp_array[i] is LCP(s[i], s[i+1])
        for (int i = 0; i < N - 1; i++) {
            lcp_array[i] = compute_lcp(sorted_docs[i], sorted_docs[i+1]);
        }
        rmq = SparseTable<int>(lcp_array);
    }

    static int compute_lcp(const string& a, const string& b) {
        int len = 0;
        int min_len = min((int)a.size(), (int)b.size());
        while (len < min_len && a[len] == b[len]) len++;
        return len;
    }

    // Returns LCP between sorted_docs[i] and sorted_docs[j]
    int get_lcp(int i, int j) {
        if (i == j) return sorted_docs[i].size();
        if (i > j) swap(i, j);
        // The LCP of a range in a sorted list is the minimum of the LCPs between neighbors
        return rmq.query(i, j - 1);
    }

    /**
     * CP Technique: Lexicographical comparison of substrings in O(1)
     * If you have a Suffix Array, this lets you compare any two substrings 
     * S1[i...i+len1] and S2[j...j+len2] instantly.
     */
    int compare_substrings(int i, int len1, int j, int len2) {
        int common = get_lcp(i, j);
        if (common >= min(len1, len2)) {
            if (len1 == len2) return 0; // Identical
            return len1 < len2 ? -1 : 1; // Shorter string is smaller
        }
        return sorted_docs[i][common] < sorted_docs[j][common] ? -1 : 1;
    }
};
